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




int
main(void){
    long long sum1 = 0;
    long long sum2 = 0;
    long long sum3 = 0;
    long long sum4 = 0;
    int temp;

    int pid = fork();

    if(pid == 0){
        for (int i = 0; i < 1e8; i++)
        {
            sum1 += i;
            sum2 += i;
            sum3 += i;
            sum4 += i;
        }
        temp = cpu_usage();
        printf("Child %d\n",temp);
        exit(0);
    }
    else{
        wait(0);
        temp = cpu_usage();
        printf("Parent %d\n",temp);
    }

    // temp = cpu_usage();
    // printf("%d\n",temp);

    return 0;
}