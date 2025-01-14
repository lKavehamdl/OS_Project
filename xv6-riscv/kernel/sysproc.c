#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "child.h"
#include "report.h"

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

uint64
sys_childproc(void) 
{
  uint64 staddr;
  argaddr(0, &staddr);

  struct child_processes children;
  int res = child_processes(&children);

  copyout(myproc()->pagetable, staddr, (char *)&children, sizeof(children));
  return res;
}

uint64
sys_rptraps(void)
{
  uint64 staddr;
  argaddr(0, &staddr);

  struct report_traps rp_traps;
  int res = report_traps(&rp_traps);

  copyout(myproc()->pagetable, staddr, (char *)&rp_traps, sizeof(rp_traps));
  return res;
}

uint64
sys_create_thread(void) {
  uint64 funcaddr;
  uint64 argsaddr;
  uint64 stackaddr;

  argaddr(0, &funcaddr);
  argaddr(1, &argsaddr);
  argaddr(2, &stackaddr);

  return create_thread(funcaddr, argsaddr, stackaddr);
}

uint64
sys_stop_thread(void) {
  int tid;

  argint(0, &tid);

  return stop_thread(tid);
}

uint64
sys_join_thread(void) {
  int tid;
  argint(0, &tid);
  return join_thread(tid);
}

uint64
sys_cpu_usage(void) {
  return get_cpu_usage();
}

uint64
sys_top(void) {
  uint64 temp;
  argaddr(0, &temp);

  struct top top;
  int res = top_processes(&top);

  copyout(myproc()->pagetable, temp, (char *)&top, sizeof(top));
  return res;
}

uint64
sys_set_cpu_quota(void) {
  int pid;
  int quota;

  argint(0, &pid);
  argint(1, &quota);

  return set_cpu_quota(pid, quota);
}

uint64
sys_fork_deadline(void) {
  int deadline;
  argint(0, &deadline);

  return fork_deadline(deadline);
}