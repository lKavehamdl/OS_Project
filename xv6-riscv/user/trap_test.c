#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char const *argv[])
{
    if (fork() == 0) {
        int* p = (int *)0;
        *p = 1;
        exit(0);
    }
    sleep(5);

    struct report_traps rp_traps;
    rptraps(&rp_traps);

    printf("%d exceptions found: \n", rp_traps.count);
    printf("PID \t\t PROCCESS NAME \t\t SCAUSE \t SPEC \t\t STVAL \n");
    for (int i = 0; i < rp_traps.count; i++)
    {
        struct report curr = rp_traps.reports[i];
        printf("%d \t\t %s \t\t 0x%lx \t\t 0x%lx \t\t 0x%lx \n", curr.pid, curr.pname, curr.scause, curr.sepc, curr.stval);
    }
    
    return 0;
}
