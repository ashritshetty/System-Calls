#include <stdio.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/syscall.h>

#define the_goob(arg) syscall(325, arg)
#define the_goob_time(arg) syscall(326, arg)

int main()
{
  int ret;
  long tsec;
  
  ret = the_goob(5);
  ret = the_goob_time(&tsec);
  
  printf("[USER] Kernel time returned is %ld\n", tsec);
  return 0;
}
