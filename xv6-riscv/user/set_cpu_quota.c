#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/spinlock.h"
#include "kernel/sleeplock.h"
#include "kernel/fs.h"
#include "kernel/file.h"
#include "kernel/fcntl.h"
#include "kernel/param.h"
#include "user.h"


char* arr[] = {"UNUSED", "USED", "SLEEPING", "RUNNABLE", "RUNNING", "ZOMBIE"};

int var= 0;
int var2= 0;
int var3= 0;

char* sol(char *str)
{
    int str_len = strlen(str);
    for (int i = str_len; i < 15; i++)
    {
        str[i] = ' ';
    }
    str[15] = '\0';
    return str;
}

void print_top(struct top *top_procs)
{
    char* states[6] = {"UNUSED", "USED", "SLEEPING", "RUNNABLE", "RUNNING", "ZOMBIE"};
    printf("Top processes:\n");
    printf("\tNAME \t\t\tPID \tPPID \tSTATE \t\tUSAGE\n");
    printf("\t---- \t\t\t--- \t---- \t----- \t\t-----\n");
    for (int i = 0; i < top_procs->count; i++)
    {
        struct proc_usage_info *p = &top_procs->procs[i];
        printf("\t%s \t%d \t%d \t%s \t%d\n",
            sol(p->name),
            p->pid, 
            p->ppid, 
            states[p->state], 
            p->usage.sumOfTicks
        );
    }
}

int
main(void){
   set_cpu_quota(getpid(), 100);
   int pid = fork();
   if(!pid){
      for(int i= 0; i< 1e7; i++){
         var++;
         var2++;
      }
      printf("first child done!\n");
      exit(0);
   }
   set_cpu_quota(pid, 1000);
   pid = fork();
   if(!pid){
      for(int i= 0; i< 1e7; i++){
         var++;
         var2++;
         var3++;
      }
      printf("second child done!\n");
      exit(0);
   }
   set_cpu_quota(pid, 1000);
   pid = fork();
   if(!pid){
      for(int i= 0; i< 1e7; i++){
         var++;
      }
      printf("third child done!\n");
      exit(0);
   }
   set_cpu_quota(pid, 1000);
   pid = fork();
   if(!pid){
      for(int i= 0; i< 1e5; i++){
         var ++;
      }
      printf("forth child done!\n");
      exit(0);
   }
   set_cpu_quota(pid, 0);
   sleep(10);
   struct top tmptop;
   top(&tmptop);
   print_top(&tmptop);
   wait(0);
   wait(0);
   wait(0);
   wait(0);
   wait(0);
   wait(0);
   return 0;
}