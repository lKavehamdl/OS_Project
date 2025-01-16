#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int a = 0, b = 0, c = 0;

void *my_thread(void *arg) {
    int *number = arg;
    printf("entered thread\n");

    for (int i = 0; i < 100; i++)
    {
        (*number)++;
    }
        if (number == &a) {
            stop_thread(-1);
            printf("thread a: %d\n", *number);
        } else if (number == &b) {
            printf("thread b: %d\n", *number);
        } else {
            printf("thread c: %d\n", *number);
        }
    
    return 0;
}

int main(int argc, char const *argv[])
{
    void* stack = malloc(1024);
    int ta = create_thread(my_thread, &a, stack);
    printf("thread %d created\n", ta);
    stack = malloc(1024);
    int tb = create_thread(my_thread, &b, stack);
    printf("thread %d created\n", tb);
    stack = malloc(1024);
    int tc = create_thread(my_thread, &c, stack);
    printf("thread %d created\n", tc);
    
    join_thread(ta);
    join_thread(tb);
    join_thread(tc);
    

    printf("All threads are finished\n");
    exit(0);
}
