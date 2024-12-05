#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"


void * test_func(void *arg){
    printf("Testing Thread\n");
    return 0;
}

int main(int argc, char *argv){

    printf("Testing Main\n");

    uint thread_id;
    void *stack = malloc(400);

    uint thread_id_1;
    void *stack_1 = malloc(400);

    create_thread(&thread_id, test_func, 0, stack, 400);
    create_thread(&thread_id_1, test_func, 0, stack_1, 400);

}