#ifndef CP_H
#define CP_H

#define NPROC 64  


struct proc_info {
    char name[16];    
    int pid;          
    int ppid;         
    int state;        
};

struct child_processes {
    int count;                      
    struct proc_info processes[NPROC];  
};

#endif 
