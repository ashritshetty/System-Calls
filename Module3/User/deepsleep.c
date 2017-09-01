#include <stdio.h>
#include <errno.h>
#include <sys/syscall.h>
#include <sys/signal.h>
#include <sys/types.h>

#define deepsleep() syscall(329)

void happy1()
{
  printf("I am happy1\n");
}

void happy2()
{
  printf("I am happy2\n");
}

int main()
{
  signal(SIGUSR1, happy1);
  signal(SIGUSR2, happy2);
  printf("[USER] Goodnight, Irene\n");
  deepsleep();
  printf("[USER] Oops ... woke up !\n");
  return 0;
}
