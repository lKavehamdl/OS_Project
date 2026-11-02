# xv6 Kernel Extensions

Extensions to [xv6-riscv](https://github.com/mit-pdos/xv6-riscv), MIT's teaching operating system, built over three phases for the Operating Systems course (Fall 2024) at Amirkabir University of Technology. The project adds process introspection, kernel-level threads and a CPU-usage-aware scheduler with quotas and deadlines.

All changes are in C (kernel) and RISC-V assembly, inside [`xv6-riscv/`](xv6-riscv). The original assignment descriptions (in Persian) are in `OS-Fall2024-Project-Phase{1,2,3}.pdf`.

## Phase 1: System Calls and Trap Reporting

| System call | Description |
| --- | --- |
| `int childproc(struct child_processes*)` | Returns the descendants of the calling process (name, PID, parent PID, state). |
| `int rptraps(struct report_traps*)` | Returns a log of traps (exceptions) raised by the process's descendants, with `scause`, `sepc` and `stval`. The kernel records every unexpected trap in `usertrap()` through `add_trap_report()`. |

Test programs: `child_test`, `trap_test`.

## Phase 2: Kernel-Level Threads

Each process can run up to `MAX_THREAD` (4) threads that share its address space. Every thread has its own trapframe and state (`FREE`, `RUNNABLE`, `RUNNING`, `JOINED`).

| System call | Description |
| --- | --- |
| `int create_thread(void *func, void *arg, void *stack)` | Starts a new thread that runs `func(arg)` on the user-supplied stack. Returns the thread ID. |
| `int stop_thread(int tid)` | Terminates a thread. |
| `int join_thread(int tid)` | Blocks until the given thread finishes. |

- **Scheduling:** for a threaded process, the scheduler cycles through its runnable threads, swapping each thread's trapframe into the process before `swtch()` and saving it back afterwards.
- **Thread exit:** a thread returning from its function traps on a sentinel return address. `usertrap()` recognizes it and cleans up the thread instead of killing the process.

Test program: `thread_test`.

## Phase 3: CPU-Usage-Aware Scheduler

The default round-robin scheduler is replaced by `scheduler_priority()`, which uses the CPU time (in ticks) each process has consumed:

1. Runnable processes are split into a **high-priority** queue (usage below their CPU quota) and a **low-priority** queue (quota used up).
2. From the high-priority queue, the process with the **least CPU usage** runs first. Ties go to the process with the **earliest deadline**.
3. Low-priority processes only run when no high-priority process is runnable.
4. After each scheduling round, `deadlines_check()` kills any process whose deadline has passed (waking it first if it is sleeping).

| System call | Description |
| --- | --- |
| `int cpu_usage(void)` | Returns the number of ticks the calling process has used. |
| `int top(struct top*)` | Returns name, PID, parent PID, state and CPU usage for every process, like the Unix `top` command. |
| `int set_cpu_quota(int pid, int quota)` | Sets a process's CPU quota in ticks. |
| `int fork_deadline(int deadline)` | Like `fork()`, but the child is given a deadline in ticks after which it is terminated. |

Test programs: `cpu_usage`, `top`, `quota`, `deadline`.

## Build and Run

Requirements: a RISC-V GNU toolchain and QEMU (`qemu-system-riscv64`). See the [MIT 6.1810 tools page](https://pdos.csail.mit.edu/6.1810/2024/tools.html) for setup.

```bash
cd xv6-riscv
make qemu
```

Then run any of the test programs from the xv6 shell:

```
$ thread_test
$ top
$ deadline
```

Press `Ctrl-a x` to quit QEMU.

## Team

- Kaveh Ahmadi ([@lKavehamdl](https://github.com/lKavehamdl))
- Arian Mohseni ([@ArianArsenal](https://github.com/ArianArsenal))
