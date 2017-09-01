/* Project #2 - System call - Smunch Super killer
   Team Members:
   Ashrit Shetty
   Dipika Pandey
*/ 

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
    int ret;
    struct task_struct *p;

    rcu_read_lock();
    p = pid_task(find_vpid(pid), PIDTYPE_PID);
    rcu_read_unlock();

    if(!p)
        return FAILURE;

    if(!thread_group_empty(p) || task_is_traced(p)){
        printk(KERN_ALERT "[KERNEL] Multi threaded or process being traced\n");
        return FAILURE;
    }

    if(p->exit_state == EXIT_ZOMBIE){
        if((bit_pattern & KILLSIG) != 0){
            release_task(p);
            printk(KERN_ALERT "[KERNEL] Killing zombie\n");
            return SUCCESS;
        }
        else{
            printk(KERN_ALERT "[KERNEL] Not killing zombie\n");
            return SUCCESS;
        }
    }

    spin_lock_irq(&p->sighand->siglock);
    p->pending.signal.sig[0] |= bit_pattern;
    spin_unlock_irq(&p->sighand->siglock);

    set_tsk_thread_flag(p, TIF_SIGPENDING);
    //ret = wake_up_state(p, p->state);
    ret = wake_up_process(p);
    printk(KERN_ALERT "[KERNEL] Handling deep sleep\n");
    return SUCCESS;

}
