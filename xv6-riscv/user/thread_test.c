#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int ans =0;

void* test_func(void *arg){
    printf("Thread Test\n");
    for(int i= 0; i< 1e6; i++){
        ans++;
    }
    return 0;
}

void* func2(void* arg){
    int* val= arg;
    printf("KOMAK! %d\n", *val);
    return 0;
}

int main(int argc, char *argv){

    printf("Testing Main\n");
    
    uint thread_id;
    void *stack = malloc(820);
    int arg= 23;

    uint thread_id_1;
    void *stack_1 = malloc(820);
    int arg2= 45;

    uint thread_id_2;
    void *stack_2 = malloc(820);

    uint thread_id_3;
    void *stack_3 = malloc(820);

    // uint thread_id_4;
    // void *stack_4 = malloc(820);

    create_thread(&thread_id, func2, (void* )&arg, stack, 820);
    create_thread(&thread_id_1, func2, (void*)&arg2, stack_1, 820);
    create_thread(&thread_id_2, test_func, 0, stack_2, 820);
    create_thread(&thread_id_3, test_func, 0, stack_3, 820);
    //create_thread(&thread_id_4, test_func, 0, stack_4, 820);

    join_thread(thread_id);
    join_thread(thread_id_1);
    join_thread(thread_id_2);
    join_thread(thread_id_3);

    
    printf("%d \n", ans);
    
}