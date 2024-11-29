#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/spinlock.h"
#include "kernel/sleeplock.h"
#include "kernel/fs.h"
#include "kernel/file.h"
#include "kernel/fcntl.h"
#include "kernel/param.h"
#include "user.h"
#include "cp.h"


char* arr[] = {"UNUSED", "USED", "SLEEPING", "RUNNABLE", "RUNNING", "ZOMBIE"};

int
main(void){
    for(int i= 0; i< 15; i++){
        int pid = fork();
        if(pid == 0){
            sleep(600);
        }
    }
    struct child_processes cps;
    cp(&cps);
    printf("%d\n", cps.count);
    for(int i= 0; i< cps.count; i++){
        printf("%d, %s, %d, %s\n", cps.processes[i].pid, cps.processes[i].name, cps.processes[i].ppid, arr[cps.processes[i].state -1]);
    }
}