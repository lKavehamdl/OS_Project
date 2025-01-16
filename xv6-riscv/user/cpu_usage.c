#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int var = 0;

int main()
{
    
    int pid = fork();
    if (pid == 0)
    {
        for(int i= 0; i< 1e9; i++){
            var ++;
        }
        printf("Child Process Finished - CPU Usage :%d\n",cpu_usage());
        exit(0);
    }

    else
        for(int i=0; i < 5e8; i ++)
            var++;    

    printf("Parent Process Finished - CPU Usage :%d\n", cpu_usage());
    return 0;
}
