/*
 *  gcc smth_revenge.c -o smth_revenge -lpthread -lseccomp -Wl,-z,relro,-z,now -fno-stack-protector -pie -fPIC -Wl,-s 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/prctl.h> 
#include <sys/ptrace.h>
#include <sys/syscall.h>
#include <linux/audit.h>
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
  BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ERRNO)

#define FLAG_PATH "/home/smth_revenge/flag"

struct thdata {
  sem_t sync;
  sem_t start;
  char *input;
};

int g_fd;
int g_num;
char *g_flag_map;

void myprintf(char *frmt, ...) {
  char *format = frmt;
  int i;
  int n;
  int out;
  va_list ap;
  va_start(ap, frmt);

  n = strlen(format);
  out = 0;
  for (i=0; i<n; ) {
    if (format[i] != '%') {
      write(STDOUT_FILENO, format+i, 1);
      ++i;
      ++out;
      continue;
    }

    ++i;
    if (i >= n) break;

    char c = format[i++];

    int val;
    int *ref;
    char cval;
    char digits[10];
    char *p = digits;
    switch (c) {
    case 'c': 
      cval = (char)va_arg(ap, int);
      write(STDOUT_FILENO, &cval, 1);
      ++out;
      break;

    case 'd':
      val = va_arg(ap, int);
      if (val == 0) {
        write(STDOUT_FILENO, "0", 1);
        ++out;
        break;
      }

      if (val < 0) {
        write(STDOUT_FILENO, "-", 1);
        ++out;
        val = ((unsigned int)val) ^ 0x80000000u;
      }

      while (val > 0) {
        *p = '0' + (val%10);
        val /= 10;
        ++p;
      }

      --p;
      while (1) {
        write(1, p, 1);
        ++out;
        if (p == digits) break;
        --p;
      }
      break;

    case 'n':
      ref = ap->overflow_arg_area;
      *ref = out;
      val = va_arg(ap, int);
      break;
    }
  }
}

void banner(void) {
  myprintf("\n");
  myprintf("  /$$$$$$                                            /$$$$$$$                                                              /$$$$ \n");
  myprintf(" /$$__  $$  /$$/$$   /$$/$$   /$$/$$   /$$/$$       | $$__  $$                                                            /$$  $$\n");
  myprintf("| $$  \\__/ |  $$$/  |  $$$/  |  $$$/  |  $$$/       | $$  \\ $$  /$$$$$$  /$$    /$$ /$$$$$$  /$$$$$$$   /$$$$$$   /$$$$$$|__/\\ $$\n");
  myprintf("| $$ /$$$$ /$$$$$$$ /$$$$$$$ /$$$$$$$ /$$$$$$$      | $$$$$$$/ /$$__  $$|  $$  /$$//$$__  $$| $$__  $$ /$$__  $$ /$$__  $$   /$$/\n");
  myprintf("| $$|_  $$|__ $$$_/|__ $$$_/|__ $$$_/|__ $$$_/      | $$__  $$| $$$$$$$$ \\  $$/$$/| $$$$$$$$| $$  \\ $$| $$  \\ $$| $$$$$$$$  /$$/ \n");
  myprintf("| $$  \\ $$  /$$ $$   /$$ $$   /$$ $$   /$$ $$       | $$  \\ $$| $$_____/  \\  $$$/ | $$_____/| $$  | $$| $$  | $$| $$_____/ |__/  \n");
  myprintf("|  $$$$$$/ |__/__/  |__/__/  |__/__/  |__/__/       | $$  | $$|  $$$$$$$   \\  $/  |  $$$$$$$| $$  | $$|  $$$$$$$|  $$$$$$$  /$$  \n");
  myprintf(" \\______/                                           |__/  |__/ \\_______/    \\_/    \\_______/|__/  |__/ \\____  $$ \\_______/ |__/  \n");
  myprintf("                                                                                                       /$$  \\ $$                 \n");
  myprintf("                                                                                                      |  $$$$$$/                 \n");
  myprintf("                                                                                                       \\______/                  \n");
  myprintf("\n");
}

void open_flag(void) {
  struct stat st;

  if (stat(FLAG_PATH, &st) < 0) {
    perror("stat()");
    exit(-1);
  }

  g_fd = open(FLAG_PATH, 0, 0);
  if (g_fd < 0) {
    perror("open()");
    exit(-1);
  }

  g_flag_map = mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_PRIVATE , g_fd, 0LL);
  if (g_flag_map == MAP_FAILED) {
    perror("mmap()");
    exit(-1);
  }
}

void setup(void) {
  banner();

  open_flag();

  if (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0)) {
    perror("prctl(NO_NEW_PRIVS)");
    exit(-1);
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
    ALLOW_SYSCALL(read),
    ALLOW_SYSCALL(write),
    ALLOW_SYSCALL(close),
    ALLOW_SYSCALL(mmap),
    //ALLOW_SYSCALL(mmap2),
    ALLOW_SYSCALL(munmap),
    ALLOW_SYSCALL(futex),
    ALLOW_SYSCALL(clone),
    ALLOW_SYSCALL(brk),
    RETURN_ERROR,
  };

  struct sock_fprog prog = {
    .len = (unsigned short)(sizeof(filter)/sizeof(filter[0])),
    .filter = filter,
  };

  //*
  if (prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog)) {
    perror("prctl(SECCOMP)");
    exit(-1);
  }
  //*/
}

void finalize(void) {
  if (g_flag_map != NULL) munmap(g_flag_map, 0x1000);
  if (g_fd != -1) close(g_fd);
  g_fd = -1;
  g_flag_map = NULL;
}

int g_sz;

void *do_read(void *arg) {
  struct thdata *th_ref = (struct thdata *)arg;

  while (1) {
    int i;

    sem_post(&th_ref->sync);
    sem_wait(&th_ref->start);

    myprintf("flag (%d/3): ", g_num);
    for (i=0; i<g_sz; i++) {
      if (read(STDIN_FILENO, &th_ref->input[i], 1) != 1) break;
      if (th_ref->input[i] == '\n') break;
    }
    if (th_ref->input[i] == '\n') th_ref->input[i] = '\0';
    
    sem_post(&th_ref->sync);
  }

  return NULL;
}

struct thdata g_data;
pthread_t g_thread;
pthread_attr_t g_attr;

int one_try(int *bufsz_ref, int *num_retry_ref) {
  int n;
  int m;

  if (sem_wait(&g_data.sync) != 0) {
    perror("sem_wait()");
    exit(-1);
  }

  g_sz = *bufsz_ref;
  
  if (sem_post(&g_data.start) != 0) {
    perror("sem_post()");
    exit(-1);
  }

  if (sem_wait(&g_data.sync) != 0) {
    perror("sem_wait()");
    exit(-1);
  }

  n = strlen(g_data.input);
  m = strlen(g_flag_map);
  if (n > 0) {
    int j;
    for (j=0; j<m; j++) {
      if (g_data.input[j] != g_flag_map[j]) {
        myprintf(g_data.input);
        myprintf(" is not right.\n");
        return 0;
      }
    }

    myprintf(":)\n");
    return n;
  } else {
    ++*num_retry_ref;
    myprintf("try again.\n");
  }
  return 0;
}

int main(void) {
  unsigned short num_retry = 0;
  short bufsz = 139;
  char input[140];
  long res = 0;
  long i = 0;

  setup();

  myprintf(
    "If there is one thing I've learned about CTFs it is that people love guessing challenges.\n"
    "So we thought, why not skip the middleman and just have players guess the flag directly.\n"
    "I hope you have fun ;)\n"
    "\n"
  );

  g_data.input = input;

  if (sem_init(&g_data.sync, 0, 0) < 0) {
    perror("sem_init()");
    exit(-1);
  }

  if (sem_init(&g_data.start, 0, 0) < 0) {
    perror("sem_init()");
    exit(-1);
  }

  if (pthread_attr_init(&g_attr) != 0) {
    perror("pthread_attr_init()");
    exit(-1);
  }

  if (pthread_attr_setstacksize(&g_attr, 16384) != 0) {
    perror("pthread_attr_setstacksize()");
    exit(-1);
  }

  if (pthread_create(&g_thread, &g_attr, do_read, (void *)&g_data) != 0) {
    perror("pthread_create()");
    exit(-1);
  }

  memset(input, '\0', 139);
  for (i=1; i <= num_retry+3; i++) {
    g_num = i-num_retry;
    res = one_try((int*)&bufsz, (int*)&num_retry);
    if (res > 0) break;
  }
  finalize();

  pthread_detach(g_thread);
  sem_destroy(&g_data.sync);
  sem_destroy(&g_data.start);

  return 0;
}
