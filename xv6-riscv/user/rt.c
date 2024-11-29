#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/spinlock.h"
#include "kernel/sleeplock.h"
#include "kernel/fs.h"
#include "kernel/file.h"
#include "user.h"
#include "kernel/fcntl.h"
#include "kernel/param.h"
#include "cp.h"


int
main(void){
    int pid = fork();
    if(pid == 0) {
        int* x =(int*)355630;
        printf("%d\n", *x);
    }
    else{
        wait(0);
    }
    struct report_traps rts;
    rt(&rts);
    for(int i= 0; i < rts.count; i++){
        printf("%d, %s, %lx, %lx, %lx\n", rts.reports[i].pid,rts.reports[i].pname, rts.reports[i].scause, rts.reports[i].sepc,rts.reports[i].stval);
    }
    printf("DONE!\n");
    return 0;
}