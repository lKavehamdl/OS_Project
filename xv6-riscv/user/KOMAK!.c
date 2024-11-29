#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/spinlock.h"
#include "kernel/sleeplock.h"
#include "kernel/fs.h"
#include "kernel/file.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/rt.h"

int
main(void){
    int fd = open("out.txt", O_RDONLY | O_CREATE);
    struct report rp;
    roffset(fd, 4 * sizeof(rp));
    for(int i= 0; i< 4; i++){
        if(read(fd, &rp, sizeof(rp)) == 0){
            return 0;
        }
        else{
            printf("%d, %s\n", rp.pid, rp.pname);
        }
    }
    return 0;
}