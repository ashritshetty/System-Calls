#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/sched.h>

SYSCALL_DEFINE1(init_sigcounter, int, pid)
{
  int i;
  unsigned long flags;
  struct task_struct *p;

  if(pid <= 0)
    return 0;

  p = pid_task(find_vpid(pid),PIDTYPE_PID);
  if(p)
  {
    lock_task_sighand(p, &flags);
    for(i = 0; i < 64; ++i)
    {
      p->sighand->sigcounter[i] = 0;
    }
    unlock_task_sighand(p, &flags);
  }
  return 0;
}

