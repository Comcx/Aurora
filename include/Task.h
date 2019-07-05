#ifndef _TASK_H
#define _TASK_H

#include <Util/Type.h>
#include <GDT.h>
#include <Hardware/Screen.h>

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


enum TaskState
  { TASK_RUNNING = 0
  , TASK_READY   = 1
  , TASK_BLOCK   = 2
  , TASK_SLEEP   = 3
  , TASK_ZOMIE   = 4
  , TASK_ERROR   = 5
  } ;
struct Task {

  uint8_t stack[4096]; // 4 KiB
  CPUState* cpustate;
  TaskState state;
  uint8_t priority;
  uint8_t alarm;
  uint8_t signal;

  Task(GDT *gdt, void f(), uint8_t priority);
  ~Task();
};

#define MAX_TASK 128
struct Tasks {

  Task* tasks[MAX_TASK];
  int num;
  int current;

  Tasks();
  ~Tasks();
  bool add(Task* task);
  CPUState* schedule(CPUState* cpustate);

  void show();
};
//Tasks tasks;




#endif





