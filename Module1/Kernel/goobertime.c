#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/time.h>

SYSCALL_DEFINE1(goobertime,long *,myarg)
{
  struct timespec time = current_kernel_time();
  
  printk(KERN_ALERT "[KERNEL] Fetching time from kernel\n");
  copy_to_user(myarg, &(time.tv_sec), sizeof(time.tv_sec));

  return 1;
}


