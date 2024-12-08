#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void* test(void* arg){
    printf("test 2\n");
    return 0;
}


void* test_func(void *arg){
    printf("Testing Thread\n");
    return 0;
}

int main(int argc, char *argv){

    printf("Testing Main\n");
    
    uint thread_id;
    void *stack = malloc(820);

    uint thread_id_1;
    void *stack_1 = malloc(820);

 create_thread(&thread_id_1, test, 0, stack_1, 820);
    create_thread(&thread_id, test_func, 0, stack, 820);

    int a = 0;
    while (a < 100000000)
    {
        a++;
    }
    
}