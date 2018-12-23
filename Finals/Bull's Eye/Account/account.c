// clang -Xclang -load -Xclang ./pass/libSSPPass.so -Wl,-z,now,-z,relro -pie -fPIE account.c -o account
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include <time.h>

#include <signal.h>
#include <sys/socket.h>
#include <arpa/inet.h>


#define PORT 4296
#define BUF_SIZE 32

struct account {
	unsigned int try;
	char *name;
	char pass[0x18];
};

static int service_main(void);
static void set_sighandler(int signum,void *func);

__attribute__((constructor))
void init(void){
	srand(time(NULL));

	setbuf(stdin, NULL);
	setbuf(stdout, NULL);
	set_sighandler(SIGCHLD, SIG_IGN);
}

int main(int argc, char *argv[]){
	struct sockaddr_in saddr;
	int sfd;
	const int on = 1;

	if ((sfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("socket");
		return -1;
	}

	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family		= AF_INET;
	saddr.sin_port			= htons(argc > 1 ? atoi(argv[1]) : PORT);
	saddr.sin_addr.s_addr	= htonl(INADDR_ANY);

	setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	if(bind(sfd, (struct sockaddr*)&saddr, sizeof(saddr))) {
		perror("bind");
		return -1;
	}

	if(listen(sfd, 5)) {
		perror("listen");
		return -1;
	}

	for(int i = 0; ; i++) {
		struct sockaddr_in caddr;
		int cfd;
		socklen_t len = 0;

		if((cfd = accept(sfd, (struct sockaddr*)&caddr, &len)) < 0) {
			perror("accept");
			exit(1);
		}

		if(i/2 && (0x10 * (i>3 ? 1.0/2 : 2.0/3) < rand() % 0x10)){
			close(cfd);
			break;
		}

		switch(fork()){
			case 0:
				{
				int ret;

				alarm(60);
				dup2(cfd, STDIN_FILENO);
				dup2(cfd, STDOUT_FILENO);
				dup2(cfd, STDERR_FILENO);
				close(cfd);
				close(sfd);

				ret	= service_main();
				exit(ret);
				}
			case -1:
				perror("child process");
				break;
			default:
				close(cfd);
		}
	}

	shutdown(sfd, SHUT_RDWR);
	close(sfd);
	return 0;
}

static void set_sighandler(int signum,void *func){
	struct sigaction act;

	memset(&act, 0, sizeof(act));

	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_NOCLDSTOP | SA_RESTART;

	sigaction(signum, &act, NULL);
}

static void create_account(struct account **list, int size);
static int login(struct account **list, int size);
static void member_menu(struct account **list, int no);
static int getnline(char *buf, unsigned size);
static int getint(void);

static int service_main(void){
	struct account *ac_list[9] = {};

	puts("Welcome to simple account management service");
	for(;;){
		printf(	"\n"
				"1. Create Account\n"
				"2. Login\n"
				"0. Exit\n"
				">> ");

		switch(getint()){
			case 1:
				create_account(ac_list, sizeof(ac_list)/sizeof(struct account*));
				break;
			case 2:
				{
				int n;
				if((n = login(ac_list, sizeof(ac_list)/sizeof(struct account*))) >= 0)
					member_menu(ac_list, n);
				break;
				}
			case 0:
				goto end;
			default:
				puts("Wrong input.");
		}
	}
end:
	
	return 0;
}

static void create_account(struct account **list, int size){
	int i, len;
	char buf[0x180]={}, *name;
	struct account *p;

	if(!list)
		return;

	for(i = 0; i<size; i++)
		if(!list[i])
			break;
	if(i == size){
		puts("Can not create account anymore.");
		return;
	}

	printf("Tell me your name length : ");
	len = getint();
	if(len >= (int)sizeof(buf)){
		puts("Name length too long");
		return;
	}

	printf("Input name : ");
	getnline(buf, len);		// stack overflow
	if(!(name = strdup(buf))){
		puts("Can not allocate name field");
		return;
	}

	if(!(p = (struct account*)calloc(1, sizeof(struct account)))){
		puts("Can not allocate account");
		return;
	}

	printf("Input password : ");
	getnline(p->pass, sizeof(p->pass));

	list[i] = p;			// overwritten list/i
	p->name = name;

	puts("Success!");
}

static int login(struct account **list, int size){
	int no;
	char buf1[0x181] = {}, buf2[0x19] = {};
	struct account *p;

	if(!list)
		return -1;

	printf("Input name : ");
	getnline(buf1, sizeof(buf1)-1);
	for(no = 0; no < size; no++)
		if((p = list[no]) && p->name && !strcmp(buf1, p->name))
			break;

	if(no == size){
		puts("USER NOT FOUND");
		return -1;
	}

	if(p->try > 3){
		puts("This account is LOCKED");
		return -1;
	}

	printf("Input password : ");
	getnline(buf2, sizeof(p->pass));

	if(strcmp(buf2, p->pass)){
		puts("WRONG PASSWORD");
		p->try++;
		return -1;
	}

	puts("Success!");
	return no;
}

static void member_menu(struct account **list, int no){
	struct account *p;

	if(!list || !(p = list[no]) || !p->name)
		return;

	puts("\n\n******** Member's Memu ********");
	for(;;){
		printf(	"\n"
				"1. Update Name\n"
				"2. Update Password\n"
				"3. Show Information\n"
				"4. Edit Information\n"
				"5. Delete Account\n"
				"0. Logout\n"
				">> ");

		switch(getint()){
			case 1:
				{
				unsigned len, size;

				printf("Tell me your NEW name length : ");
				len = getint();
				size = malloc_usable_size(p->name);
				if(len >= size){
					puts("NEW name length too long");
					break;
				}

				printf("Input NEW name : ");
				getnline(p->name, len);
				break;
				}
			case 2:
				printf("Input NEW password : ");
				getnline(p->pass, sizeof(p->pass));
				break;
			case 3:
			case 4:
				puts("not implemented...");
				break;
			case 5:
				free(p->name);
				free(p);
				list[no] = NULL;
			case 0:
				puts("Bye");
				return;
			default:
				puts("Wrong input.");
		}
	}
}

static int getnline(char *buf, unsigned size){
	int i, len;

	if(!buf || size < 1)
		return 0;

	len = read(0, buf, size);
	for(i=0; i<len && buf[i]; i++)
		if(!(buf[i]^'\n')){
			buf[i]='\0';
			break;
		}

	if(i == len)				// non NULL terminate
		buf[size] = '\0';		// overflow

	return len;
}

static int getint(void){
	char buf[BUF_SIZE+1];

	getnline(buf, sizeof(buf)-1);
	return atoi(buf);
}
