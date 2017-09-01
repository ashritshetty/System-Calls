#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/sched.h>

SYSCALL_DEFINE2(get_sigcounter, int, signumber, int, pid)
{
  int ctr;
  unsigned long flags;
  struct task_struct *p;

  if(signumber < 1 || signumber > 64)
  {
    printk(KERN_ALERT "[KERNEL] Signal number must be between 1 and 64 (both included) \n");
    return 0;
  }
  
  p = pid_task(find_vpid(pid),PIDTYPE_PID);
  if(p){
    lock_task_sighand(p, &flags);
    ctr = p->sighand->sigcounter[signumber-1];
    unlock_task_sighand(p, &flags);
    return ctr;
  } 

  return 0;
}
