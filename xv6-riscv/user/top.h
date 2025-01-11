#include "kernel/types.h"


#ifndef TOP_H
#define TOP_H

#define NPROC 64

struct cpu_usage{
  uint sumOfTicks;
  uint startTick;
  uint quota;
};

struct proc_usage_info{
  char name[16];
  int pid;
  int ppid;
  int procstate;
  struct cpu_usage usage;
};

struct top{
  int count;
  struct proc_usage_info procs[NPROC];
};


#endif