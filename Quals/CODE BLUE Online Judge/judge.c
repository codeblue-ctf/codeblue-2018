/*
 * gcc judge.c -o judge -m32 -lseccomp -Wl,-s -Wl,-z,relro,-z,now -fstack-protector-all 
 */

#define _GNU_SOURCE  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include <unistd.h>
#include <signal.h>
#include <malloc.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/prctl.h> 
#include <sys/ptrace.h>
#include <sys/syscall.h>
#include <linux/audit.h>
#include <linux/limits.h>
#include <linux/filter.h>
#include <linux/seccomp.h>

#define SYSCALL_NR (offsetof(struct seccomp_data, nr))
#define ARCH_NR (offsetof(struct seccomp_data, arch))

#if defined(__i386__)
# define AUDIT  AUDIT_ARCH_I386
#elif defined(__x86_64__)
# define AUDIT  AUDIT_ARCH_X86_64
#endif

#define VALIDATE_ARCHITECTURE \
  BPF_STMT(BPF_LD+BPF_W+BPF_ABS, ARCH_NR), \
  BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, AUDIT, 1, 0), \
  BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_KILL)

#define EXAMINE_SYSCALL \
  BPF_STMT(BPF_LD+BPF_W+BPF_ABS, SYSCALL_NR)

#define ALLOW_SYSCALL(name) \
  BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, __NR_##name, 0, 1), \
BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ALLOW)

#define RETURN_ERROR \
  BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ERRNO|1)

#define UID_SANDBOX_USER 65534 
#define GID_SANDBOX_USER 65534

#define LIM_N 8000
#define LIM_M 8000

struct io {
  FILE *rfp;
  FILE *wfp;
};

void handler(int sig) {
  kill(0, SIGKILL);
  exit(-2);
}

void init_parent_seccomp() {
  if (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0)) {
    perror("prctl(NO_NEW_PRIVS)");
    exit(-4);
  }

  struct sock_filter filter[] = {
    VALIDATE_ARCHITECTURE,
    EXAMINE_SYSCALL,
    ALLOW_SYSCALL(rt_sigreturn),
#ifdef __NR_sigreturn
    ALLOW_SYSCALL(sigreturn),
#endif
    ALLOW_SYSCALL(exit_group),
    ALLOW_SYSCALL(exit),
    ALLOW_SYSCALL(open),
    ALLOW_SYSCALL(read),
    ALLOW_SYSCALL(write),
    ALLOW_SYSCALL(close),
    ALLOW_SYSCALL(mmap),
    ALLOW_SYSCALL(brk),
    ALLOW_SYSCALL(fcntl64),
    ALLOW_SYSCALL(fstat64),
    ALLOW_SYSCALL(_llseek),
    RETURN_ERROR,
  };

  struct sock_fprog prog = {
    .len = (unsigned short)(sizeof(filter)/sizeof(filter[0])),
    .filter = filter,
  };

  if (prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog)) {
    perror("prctl(SECCOMP)");
    exit(-4);
  }
}

int cmp(const void *ap, const void *bp, void *fp) {
  int r;
  short a = *(short *)ap;
  short b = *(short *)bp;
  struct io *iop = (struct io *)fp;

  fprintf(iop->wfp, "%hd %hd\n", a, b);
  fscanf(iop->rfp, "%d", &r);
  if (r != -1 && r != 1) exit(-1);
  
  return r;
}

short N;
short M;
short *A;
short *B;
short *U;
short *V;
struct io fs;

int do_check(char *path, int rfd, int wfd) {
  short i;
  FILE *fp;

  fp = fopen(path, "r");
  if (!fp) {
    exit(-1);
  }

  if (fscanf(fp, "%hd%hd", &N, &M) != 2) {
    exit(-1);
  }

  if (N > LIM_N || M > LIM_M) {
    exit(-1);
  }

  A = (short*)calloc(N, sizeof(short));
  if (!A) {
    exit(-1);
  }

  B = (short*)calloc(N, sizeof(short));
  if (!B) {
    exit(-1);
  }

  U = (short*)calloc(M, sizeof(short));
  if (!U) {
    exit(-1);
  }

  V = (short*)calloc(M, sizeof(short));
  if (!V) {
    exit(-1);
  }

  for (i=0; i<M; i++) {
    if (fscanf(fp, "%hd%hd", &U[i], &V[i]) != 2) exit(-1);
    if (U[i] < 0 || N <= U[i]) exit(-1);
    if (V[i] < 0 || N <= V[i]) exit(-1);
  }

  fs.rfp = fdopen(rfd, "r");
  if (!fs.rfp) {
    exit(-1);
  }

  fs.wfp = fdopen(wfd, "w");
  if (!fs.wfp) {
    exit(-1);
  }

  setbuf(fs.wfp, NULL);

  fprintf(fs.wfp, "%hd %hd\n", N, M);
  for (i=0; i<M; i++) {
    fprintf(fs.wfp, "%hd %hd\n", U[i], V[i]);
  }

  for (i=0; i<N; i++) A[i] = i;
  qsort_r(A, N, sizeof(short), cmp, &fs);
  for (i=0; i<N; i++) B[A[i]] = i;

  int res = 1;
  for (i=0; i<M; i++) {
    if (B[U[i]] >= B[V[i]]) {
      res = 0;
      break;
    }
  }
  
  fclose(fp);
  fclose(fs.rfp);
  fclose(fs.wfp);
  free(A);
  free(B);
  free(U);
  free(V);

  return res;
}

int main(int argc, char *argv[]) {
  int i;

  if (argc < 3) exit(-4);

  char *bin = argv[1];
  char *input = argv[2];

  setbuf(stdout, NULL);
  signal(SIGALRM, handler);
  alarm(4);

  int j;
  int fds[2][2];

  for (j=0; j<2; j++) {
    if (pipe(fds[j]) == -1) exit(-4);
  }

  pid_t pid = fork();
  if (pid == -1) {
    kill(0, SIGKILL);
    exit(-4);
  }

  // child 
  if (pid == 0) {
    char *args[] = {bin, NULL};

    for (j=0; j<2; j++) {
      close(fds[j][j]);
    }
    dup2(fds[0][1], STDOUT_FILENO);
    dup2(fds[1][0], STDIN_FILENO);

    if (setreuid(UID_SANDBOX_USER, UID_SANDBOX_USER) == -1) {
      exit(-4);
    }

    if (setregid(GID_SANDBOX_USER, GID_SANDBOX_USER) == -1) {
      exit(-4);
    }

    execve(bin, args, NULL);
    exit(-4); // noreturn
  }

  pid = fork();
  if (pid == -1) {
    kill(0, SIGKILL);
    exit(-4);
  }
  
  if (pid == 0) {
    for (j=0; j<2; j++) {
      close(fds[j][j^1]);
    }

    init_parent_seccomp();
    exit(do_check(input, fds[0][0], fds[1][1])); // noreturn
  }

  for (j=0; j<2; j++) {
    int k;
    for (k=0; k<2; k++) {
      close(fds[j][k]);
    }
  }

  int status;
  waitpid(pid, &status, WUNTRACED);
  if (!WIFEXITED(status)) {
    exit(-3);
  }
  
  if (WEXITSTATUS(status) != 1) {
    exit(-1);
  }

  exit(0);
}
