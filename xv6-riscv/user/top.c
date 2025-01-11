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
      for(int i= 0; i< 1e8; i++){
         var++;
         var2++;
         var3++;
      }
      // sleep(60000);
   }
   else{
      // for(int i= 0; i< 1e6; i++){
      //    var2++;
      //    var3++;
      // }
      sleep(5000);
   }
   struct top topstruct;  
   top(&topstruct);
   int maxUsage = -1;
   int index = 0;
   for(int j= 0; j< topstruct.count; j++){
      for(int i= 0; i< topstruct.count; i++){
         if(topstruct.procs[i].usage.sumOfTicks > maxUsage){
            maxUsage = topstruct.procs[i].usage.sumOfTicks;
            index = i;
         }
      }
      printf("PID: %d PPID: %d STATE: %d NAME: %s START: %d USAGE: %d\n", topstruct.procs[index].pid, topstruct.procs[index].ppid, topstruct.procs[index].state, topstruct.procs[index].name, topstruct.procs[index].usage.startTick, topstruct.procs[index].usage.sumOfTicks);
      topstruct.procs[index].usage.sumOfTicks = -1;
      index = 0;
      maxUsage = -1;
   }
   
}