#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


void* test_func(void *arg){
    printf("Testing Thread\n");
    // exit(0);
    return 0;
}

int main(int argc, char *argv){

    printf("Testing Main\n");
    
    uint thread_id;
    void *stack = malloc(16);

    // uint thread_id_1;
    // void *stack_1 = malloc(16);

    create_thread(&thread_id, test_func, 0, stack, 16);
    // create_thread(&thread_id_1, test_func, 0, stack_1, 16);

    while (1);
}