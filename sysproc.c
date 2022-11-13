#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

// ------------------
int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// lab 0
int
sys_hello(void)
{
  hello();
  return 0;
}

// lab 1
int
sys_exit2(void)
{
  int status;
  if(argint(0, &status) < 0)
  {
    return -1;
  }
  return exit2(status);
}

int
sys_waitpid(void)
{ 
  int pid;
  int options = 0;
  int* status;

  if(argint(0, &pid) < 0)
  {
    return -1;
  }
  if(argptr(1,(void*)&status, sizeof(status)) < 0)
  { 
    return -1; 
  }
  return waitpid(pid, status, options);
}

//updating wait 
/* 
The wait system call must prevent the current process from execution until any of its child
processes is terminated (if any exists) and return the terminated child exit status through
the status argument.

- Return the terminated child proc’s exit status through the status pointer argument;

*/
int
sys_wait2(void)
{
  int *status;
  argptr(0, (void*)&status, sizeof(status));
  return wait2(status);
}


int
sys_setpriority(void)
{
  int priority;
  
  if(argint(0,&priority) < 0)
  {
    return -1;
  }
  else
  {
    return setpriority(priority);
  }
}