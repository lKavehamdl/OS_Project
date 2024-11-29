// Test that fork fails gracefully.
// Tiny executable so that the limit can be filling the proc table.

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define N  1000

void
print(const char *s)
{
  write(1, s, strlen(s));
}

void
forktest(void)
{
  for(int i= 0; i< 15; i++){
    int pid = fork();
    if(pid == 0){
      sleep(600);
    }
  }
}

int
main(void)
{
  forktest();
  exit(0);
}
