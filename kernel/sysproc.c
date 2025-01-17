#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  //Load exit msg from register 1
  char buf[32];
  argstr(1, buf, 32);    

  int n;
  argint(0, &n);
  exit(n, buf);
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
  uint64 maddr;
  argaddr(1, &maddr);
  return wait(p, maddr);
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

// returns the size of the running process' memory in bytes
uint64
sys_memsize(void)
{
  uint64 size = myproc()->sz;
  return size;
}

uint64
sys_set_ps_priority(void)
{
  int pr;
  argint(0, &pr);
  set_ps_priority(pr);
  return 0;
}

uint64
sys_set_cfs_priority(void)
{
  int pr;
  argint(0, &pr);
  if(pr>=0 && pr<=2){
    myproc()->cfs_priority = pr;
    return 0;
  }
  return -1;
}

uint64
sys_get_cfs_stats(void)
{
  int pid;
  argint(0, &pid);
  uint64 addr;
  argaddr(1,&addr);
  return get_cfs_stats(pid, addr);
}

uint64
sys_set_policy(void)
{
  int pl;
  argint(0, &pl);
  return set_policy(pl);
}
