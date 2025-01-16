#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char const *argv[])
{
    if (fork() == 0)
    {
        if (fork() == 0)
        {
            sleep(50);
            exit(0);
        }
        if (fork() == 0)
        {
            sleep(50);
            exit(0);
        }
        if (fork() == 0)
        {
            sleep(50);
            exit(0);
        }
        if (fork() == 0)
        {
            sleep(50);
            exit(0);
        }

        wait(0);
        wait(0);
        wait(0);
        wait(0);

        exit(0);
    }

    sleep(5);
    struct child_processes children;
    childproc(&children); // syscall
    printf("Number of children: %d\n", children.count);
    printf("PID\tPPID\tSTATE\tNAME\n");
    for (int i = 0; i < children.count; i++)
    {
        printf("%d\t%d\t%s\t%s\n",
               children.processes[i].pid,
               children.processes[i].ppid,
               children.processes[i].state,
               children.processes[i].name);
    }
    wait(0);
    exit(0);
}
