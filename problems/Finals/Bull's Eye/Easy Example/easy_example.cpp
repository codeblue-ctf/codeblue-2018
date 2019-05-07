/*
 *  g++ easy_example.cpp -o easy_example -fstack-protector-all
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <vector>
#include <string>
#include <unistd.h>
#include <errno.h>
using namespace std;

__attribute__((constructor))
void set_timeout(void) {
  alarm(30);
  setbuf(stdout, NULL);
}

void myread(char *buf) {
  while (1) {
    int ret = read(STDIN_FILENO, buf, 1);
    if (ret == -1) {
      if (errno == EAGAIN || errno == EINTR) continue;
      return;
    }

    if (ret == 0) return;
    ++buf;
  }
}

int main(void) {
  puts("You know, buffer overflow is famous as a basic vulnerability.");
  puts("In CTFs, we often see problems covering it as their subject.");
  puts("So this time let's warm up with a really simple baby buffer overflow!");

  string buf;
  uint32_t sz; 
  printf("Size: ");
  scanf("%u", &sz);
  buf.resize(sz);

  printf("And here's a hint! cookie: %llx, buf: %p\n", *(unsigned long long int*)(((char*)(&sz))+44) & ~(1LL << 16), buf.c_str());
  
  printf("Input: ");
  myread((char*)buf.c_str());

  write(STDOUT_FILENO, "Output: ", 8);
  write(STDOUT_FILENO, buf.c_str(), strlen(buf.c_str()));
  write(STDOUT_FILENO, "\n", 1);
}
