#include <stdio.h>
#include <errno.h>
#include <sys/syscall.h>

#define smunch(arg1, arg2) syscall(330, arg1, arg2)

int main(int argc, char *argv[])
{
  int ret;

  if(argc != 3)
  {
    printf("[USAGE] ./smunch <pid> <bit pattern>\n");
    return 0;
  }

  int pid = atoi(argv[1]);
  unsigned long bit_pattern = (unsigned long) atoi(argv[2]);

  printf("PID %d Bit Pattern %lu \n", pid, bit_pattern);
  ret = smunch(pid, bit_pattern);  
  printf("Return %d\n", ret);

  return 0;
  
}
