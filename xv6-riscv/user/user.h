#include "kernel/child.h"
#include "kernel/report.h"
struct stat;

enum procstate { UNUSED, USED, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };

struct cpu_usage {
  uint sum_of_ticks;
  uint start_tick;
  uint quota;
  int has_deadline;
  uint deadline;
};

struct proc_info {
  char name[16];
  int pid;
  int ppid;
  enum procstate state;
  struct cpu_usage usage;
};

struct top {
  int count;
  struct proc_info processes[NPROC];
};


// system calls
int fork(void);
int exit(int) __attribute__((noreturn));
int wait(int*);
int pipe(int*);
int write(int, const void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(const char*, char**);
int open(const char*, int);
int mknod(const char*, short, short);
int unlink(const char*);
int fstat(int fd, struct stat*);
int link(const char*, const char*);
int mkdir(const char*);
int chdir(const char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
int childproc(struct child_processes*);
int rptraps(struct report_traps*);
int create_thread(void*, void*, void*);
int stop_thread(int tid);
int join_thread(int tid);

//
int cpu_usage(void);
int top(struct top*);
int set_cpu_quota(int pid, int quota);
int fork_deadline(int deadline);



// ulib.c
int stat(const char*, struct stat*);
char* strcpy(char*, const char*);
void *memmove(void*, const void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void fprintf(int, const char*, ...) __attribute__ ((format (printf, 2, 3)));
void printf(const char*, ...) __attribute__ ((format (printf, 1, 2)));
char* gets(char*, int max);
uint strlen(const char*);
void* memset(void*, int, uint);
int atoi(const char*);
int memcmp(const void *, const void *, uint);
void *memcpy(void *, const void *, uint);

// umalloc.c
void* malloc(uint);
void free(void*);
