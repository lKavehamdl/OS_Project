#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/spinlock.h"
#include "kernel/sleeplock.h"
#include "kernel/fs.h"
#include "kernel/file.h"
#include "kernel/fcntl.h"
#include "kernel/param.h"
#include "user.h"


char* states[6] = {"UNUSED", "USED", "SLEEPING", "RUNNABLE", "RUNNING", "ZOMBIE"};

int var= 0;
int var2= 0;
int var3= 0;

int
main(void){

   int pid=fork();
   if(pid == 0){
      for(int i= 0; i< 5e8; i++){
         var++;
         var2++;
         var3++;
      }
   }
   else{
      for(int i= 0; i< 5e8; i++){
         var2++;
         var3++;
      }
      sleep(10);
      exit(0);
   }

   
   
   /*copy this part in other test files*/
   struct top top_procs;
   top(&top_procs);
   
   printf("Top processes:\n");
   printf("\tNAME \tPID \tPPID \tSTATE \t\tUSAGE\n");
   printf("\t---- \t--- \t---- \t----- \t\t-----\n");
   for (int i = 0; i < top_procs.count; i++)
   {
      struct proc_info *p = &top_procs.processes[i];
      printf("\t%s \t%d \t%d \t%s \t%d\n",p->name,p->pid, p->ppid, states[p->state], p->usage.sum_of_ticks);
   }

   exit(0);
   return 0;

}