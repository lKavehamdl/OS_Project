#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int var =0;

int main()
{
    int pid = fork_deadline(20);
    if (pid == 0) {
        for(int i= 0; i< 1e9; i++){
            printf("child process %d\n", i);
        }
        exit(0);
    }

    printf("Parent is Waiting\n");
    wait(0);
    printf("Parent has Finished\n");
    return 0;
}
