#include <Task.h>


Task::Task(GDT *gdt, void f(), uint8_t priority) {

    cpustate = (CPUState*)(stack + 4096 - sizeof(CPUState));

    cpustate -> eax = 0;
    cpustate -> ebx = 0;
    cpustate -> ecx = 0;
    cpustate -> edx = 0;

    cpustate -> esi = 0;
    cpustate -> edi = 0;
    cpustate -> ebp = 0;

    /*
    cpustate -> gs = 0;
    cpustate -> fs = 0;
    cpustate -> es = 0;
    cpustate -> ds = 0;
    */

    // cpustate -> error = 0;

    // cpustate -> esp = ;
    cpustate -> eip = (uint32_t)f;
    cpustate -> cs = gdt->codeSegment();
    // cpustate -> ss = ;
    cpustate -> eflags = 0x202;
    this->state    = TASK_READY;
    this->priority = priority;
}

Task::~Task() {}


Tasks::Tasks() {

  num = 0;
  current = -1;
}

Tasks::~Tasks() {}

bool Tasks::add(Task* task) {

  if(num >= 256)
    return false;
  tasks[num++] = task;
  return true;
}

CPUState* Tasks::schedule(CPUState* cpustate) {

  uint8_t prior = tasks[current]->priority;
  int next = current;
  if(num <= 0)
    return cpustate;

  if(current >= 0) {
    tasks[current]->cpustate = cpustate;
    tasks[current]->state = TASK_READY;
  }

  if(++next >= num) {
    next %= num;
  }
  /*
  for(int i(next); i < num; ++i) {

    if(tasks[i]->state == TASK_SLEEP) {
      continue;
    }

    if(tasks[i]->state == TASK_READY && tasks[i]->priority > prior) {
      next = i;
      prior = tasks[i]->priority;
    }
  }*/
  current = next;
  tasks[next]->state = TASK_RUNNING;
  if(tasks[next]->priority == 4) tasks[next]->state = TASK_SLEEP;
  //show();
  return tasks[next]->cpustate;
}

void Tasks::show() {

  printf("\nTasks:\n");
  for(int i(0); i < num; ++i) {

    printfHex(i);
    printf(" ");
    switch(tasks[i]->state) {
    case TASK_RUNNING:
      printf("RUNNING"); break;
    case TASK_READY:
      printf("READY"); break;
    case TASK_BLOCK:
      printf("BLOCK"); break;
    case TASK_SLEEP:
      printf("SLEEP"); break;
    case TASK_ZOMIE:
      printf("ZOMIE"); break;
    case TASK_ERROR:
      printf("ERROR"); break;
    }
    printf(" ");
    printfHex(tasks[i]->priority);
    printf("\n");
  }
}



