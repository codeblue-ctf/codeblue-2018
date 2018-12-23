/*
 *  gcc fliqpy.c -o fliqpy 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

__attribute__((constructor))
void set_timeout(void) {
  alarm(150);
}

int main(void) {
  unsigned char *addr;
  unsigned long long int ord;

  puts("You know, actually soft error is a common phenomenon.");
  puts("It occurs with non-negligible probability, not astronomical odds.");
  puts("So this time let's see if you can exploit this only with one bit flip!");

  printf("Enter the address you want to flip: ");
  scanf("%p", &addr);
  printf("Which bit do you want to flip?: ");
  scanf("%llu", &ord);
  if (ord >= 8) {
    puts("Idiot");
    exit(0);
  }
 
  *addr ^= 1 << ord;
  exit(0);
}
