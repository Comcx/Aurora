#include <Task.h>


Task::Task(GDT *gdt, void f()) {

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
}

Task::~Task() {}


Tasks::Tasks() {

    num = 0;
    current = -1;
}

Tasks::~Tasks() {}

bool Tasks::add(Task* task)
{
    if(num >= 256)
        return false;
    tasks[num++] = task;
    return true;
}

CPUState* Tasks::schedule(CPUState* cpustate)
{
    if(num <= 0)
        return cpustate;

    if(current >= 0)
        tasks[current]->cpustate = cpustate;

    if(++current >= num)
        current %= num;
    return tasks[current]->cpustate;
}





