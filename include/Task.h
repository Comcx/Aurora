#ifndef _TASK_H
#define _TASK_H

#include <Types.h>
#include <GDT.h>

struct CPUState {

  uint32_t eax;
  uint32_t ebx;
  uint32_t ecx;
  uint32_t edx;

  uint32_t esi;
  uint32_t edi;
  uint32_t ebp;
  /*
  uint32_t gs;
  uint32_t fs;
  uint32_t es;
  uint32_t ds;
  */
  uint32_t error;

  uint32_t eip;
  uint32_t cs;
  uint32_t eflags;
  uint32_t esp;
  uint32_t ss;
} __attribute__((packed));


struct Task {

  uint8_t stack[4096]; // 4 KiB
  CPUState* cpustate;

  Task(GDT *gdt, void f());
  ~Task();
};

struct Tasks {

  Task* tasks[256];
  int num;
  int current;

  Tasks();
  ~Tasks();
  bool add(Task* task);
  CPUState* schedule(CPUState* cpustate);
};

//Tasks tasks;




#endif





