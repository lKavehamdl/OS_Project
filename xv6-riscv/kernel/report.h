#define MAX_REPORT_BUFFER_SIZE 10

struct report {
    char pname[16];
    int pid;
    uint64 scause;
    uint64 sepc;
    uint64 stval;
};

struct report_traps {
    struct report reports[MAX_REPORT_BUFFER_SIZE];
    int count;
};

