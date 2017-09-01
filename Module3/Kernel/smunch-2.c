/* Project #2 - System call - Smunch Super killer
   Team Members: Ashrit Shetty & Dipika Pandey */

#include <linux/linkage.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/wait.h>
#include <linux/sched.h>

#define SUCCESS  0
#define FAILURE -1
#define KILLSIG 256

SYSCALL_DEFINE2(smunch, int, pid, unsigned long, bit_pattern)
{
    struct task_struct *p;
    rcu_read_lock();
    p = pid_task(find_vpid(pid), PIDTYPE_PID);
    rcu_read_unlock();

    if(!p) return FAILURE;

    //Multi threaded process or process being traced are not handled
    if(!thread_group_empty(p) || task_is_traced(p))
        return FAILURE;

    if(p->exit_state == EXIT_ZOMBIE){
        //Removing Zombie entry if signal sent is KILL
        if((bit_pattern & KILLSIG) != 0){
            release_task(p);
        }
        return SUCCESS;
    }
    //Signal sent to other processes(uninterruptible/interruptible/running)
    spin_lock_irq(&p->sighand->siglock);
    p->pending.signal.sig[0] |= bit_pattern;
    spin_unlock_irq(&p->sighand->siglock);
    set_tsk_thread_flag(p, TIF_SIGPENDING);
    wake_up_process(p);
    return SUCCESS;
}
