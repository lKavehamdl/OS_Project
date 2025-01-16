#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

char states_names[6][16] = {"UNUSED", "USED", "SLEEPING", "RUNNABLE", "RUNNING", "ZOMBIE"};

void function(char* name, long long amount)
{
    long long i = 0;

    while (i < amount)
    {
        i++;
    }
    while (i > 0)
    {
        i--;
    }   
    printf("%s finished\n", name);
}

int main(int argc, char const *argv[])
{


    set_cpu_quota(getpid(), 100);
    int pid = fork();
    if (pid == 0)
    {
        function("child B", 1e9);
        exit(0);
    }


    set_cpu_quota(pid, 1000);
    pid = fork();
    if (pid == 0)
    {
        function("child C", 1e9);
        exit(0);
    }


    
    set_cpu_quota(pid, 1000);
    pid = fork();
    if (pid == 0)
    {
        function("child A", 1e6);
        exit(0);
    }



    
    set_cpu_quota(pid, 0);

    sleep(10);
    

    /*copy this part in other test files*/
   
   // top system call
   struct top top_procs;
   top(&top_procs);
   
   printf("Top processes:\n");
   printf("\tNAME \tPID \tPPID \tSTATE \t\tUSAGE\n");
   printf("\t---- \t--- \t---- \t----- \t-----\n");
   for (int i = 0; i < top_procs.count; i++)
   {
      struct proc_info *p = &top_procs.processes[i];
      printf("\t%s \t%d \t%d \t%s \t%d\n",p->name,p->pid, p->ppid, states_names[p->state], p->usage.sum_of_ticks);
   }


    wait(0);
    wait(0);
    wait(0);
    wait(0);
    wait(0);
    
    return 0;
}
