#include "param.h"

struct child_info {
  char name[16];
  int pid;
  int ppid;
  char state[16];
};

struct child_processes {
  int count;
  struct child_info processes[NPROC];
};