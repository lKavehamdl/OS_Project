#include "types.h"

#ifndef RT_H
#define RT_H

#define MRBS 10  

struct report{
    char pname[16];
    int pid;
    uint64 scause;
    uint64 sepc;
    uint64 stval;
};

struct report_traps {
    struct report reports[MRBS];
    int count;
};


#endif