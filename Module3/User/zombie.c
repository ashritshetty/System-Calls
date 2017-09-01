#include <stdio.h>
#include <stdlib.h>

int main()
{
  int pid;

  switch(pid=fork())
  {
    case 0:
      printf("[USER] Try to kill pid %d\n", getpid());
      exit(0);
    default:
      printf("[USER] Without killing pid %d\n", getpid());
      while(1)
      {
        sleep(20);
      }
  }

  return 0;
}
