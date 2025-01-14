#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void function(char* name, long long amount)
{
    long long i = 0;

    while (i < amount)
    {
        printf("%s:%lld\n", name, i);
        i++;
    }
    printf("%s Finished\n", name);
}


int main()
{
    int pid = fork_deadline(2);
    if (pid == 0) {
        function("Testing", 1000000000);
        exit(0);
    }

    printf("Parent is Waiting\n");
    wait(0);
    printf("Parent has Finished\n");
    return 0;
}
