#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

char* states[6] = {"UNUSED", "USED", "SLEEPING", "RUNNABLE", "RUNNING", "ZOMBIE"};
int var = 0;


int main(int argc, char const *argv[])
{


    set_cpu_quota(getpid(), 3);
    int pid = fork();
    if (pid == 0)
    {
        for(int i= 0; i< 6e8; i++){
           var++; 
        }
        printf("First child finished, usage: %d\n", cpu_usage());
        exit(0);
    }


    set_cpu_quota(pid, 4);
    pid = fork();
    if (pid == 0)
    {
        for(int i= 0; i< 7e8; i++){
            var ++;
        }
        printf("Second chiled finished!, usage: %d\n", cpu_usage());
        exit(0);
    }


    
    set_cpu_quota(pid, 2);
    pid = fork();
    if (pid == 0)
    {
        for(int i= 0; i< 1e9; i++){
            var ++;
        }
        printf("Third child finished!, usage: %d\n", cpu_usage());
        exit(0);
    }

    
    set_cpu_quota(pid, 0);
    sleep(2);
    

    /*copy this part in other test files*/
   
   // top system call
   struct top top_procs;
   top(&top_procs);
   
   printf("Top processes:\n");
   printf("\tNAME \tPID \tPPID \tSTATE \t\tUSAGE\tQUOTA\n");
   printf("\t---- \t--- \t---- \t----- \t\t-----\t-----\n");
   for (int i = 0; i < top_procs.count; i++)
   {
      struct proc_info *p = &top_procs.processes[i];
      printf("\t%s \t%d \t%d \t%s \t%d\t%d\n",p->name,p->pid, p->ppid, states[p->state], p->usage.sum_of_ticks, p->usage.quota);
   }

    printf("\n================== \n");
    sleep(2);

    top(&top_procs);
   
   printf("Top processes:\n");
   printf("\tNAME \tPID \tPPID \tSTATE \t\tUSAGE\tQUOTA\n");
   printf("\t---- \t--- \t---- \t----- \t\t-----\t-----\n");
   for (int i = 0; i < top_procs.count; i++)
   {
      struct proc_info *p = &top_procs.processes[i];
      printf("\t%s \t%d \t%d \t%s \t%d\t%d\n",p->name,p->pid, p->ppid, states[p->state], p->usage.sum_of_ticks, p->usage.quota);
   }

    wait(0);
    wait(0);
    wait(0);
    wait(0);
    wait(0);
    
    return 0;
}
