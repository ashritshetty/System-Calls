#include <stdio.h>
#include <unistd.h>
#include <sys/signal.h>
#include <sys/types.h>

#define init_count(arg) syscall(327, arg)
#define get_count(arg1, arg2) syscall(328, arg1, arg2)

void happy1()
{
  int id = (int) getpid();
  int count = get_count(SIGUSR1, id);
  printf("[CHILD] Count of signal %d is %d \n", SIGUSR1, count);
}

void happy2()
{
int id = (int) getpid();
int count = get_count(SIGCONT, id);
printf("[CHILD] Count of signal %d is %d \n", SIGCONT, count);
}

main()
{
<<<<<<< HEAD
int pid, cid, ret;
switch(pid=fork()){
	case 0:
		cid = (int) getpid();
		init_count(cid);
		signal(SIGUSR1,happy1);
		signal(SIGCONT,happy2);
		while(1){
			printf("child is playing\n");
			sleep(1);
			}
		break;
	default:
		while(1){
			printf("parent is going to sleep\n");
			sleep(5);
			printf("parent wakes up ... checks on child\n");
			ret = kill(pid,SIGUSR1);
			printf("kill returned %d\n");
			printf("parent is going to sleep\n");
			sleep(5);
			printf("parent wakes up ... checks on child\n");
			ret = kill(pid,SIGCONT);
			printf("kill returned %d\n");
			}
	}
=======
  int pid, cid, ret;
  switch(pid=fork()){
    case 0:
      cid = (int) getpid();
      init_count(cid);
      signal(SIGUSR1,happy);
      while(1){
        printf("[CHILD] Child is playing\n");
        sleep(1);
      }
      break;
    default:
      while(1){
        printf("[PARENT] Parent is going to sleep\n");
        sleep(10);
        printf("[PARENT] Parent wakes up ... checks on child\n");
        ret = kill(pid,SIGUSR1);
        printf("[PARENT] Kill returned %d\n");
      }
   }
>>>>>>> d16e7e6f4bc9e86ace00096f1963fc707bef1329
}
