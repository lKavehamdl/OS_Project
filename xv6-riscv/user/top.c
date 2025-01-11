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

int
main(void){
   int pid=fork();
   if(pid == 0){
      int pid2= fork();
      if(pid2 == 0){
         for(int i= 0; i< 1e8; i++){
            var++;
            var2++;
            var3++;
         }
      }
      else{
         for(int i= 0; i< 1e7; i++){
            var++;
            var2++;
         }
      }
   }
   else{
      for(int i= 0; i< 1e7; i++){
         var ++;
      }
   }
   struct top topstruct;  
   top(&topstruct);
   for(int i= topstruct.count -1; i>= 0; i--){
      printf("PID: %d PPID: %d STATE: %s NAME: %s START: %d USAGE: %d\n",topstruct.procs[i].pid, topstruct.procs[i].ppid, arr[topstruct.procs[i].state], topstruct.procs[i].name, topstruct.procs[i].usage.startTick, topstruct.procs[i].usage.sumOfTicks);
   }
}