
#include <Types.h>
#include <Computer.h>
#include <Time.h>



void taskA() {

  while(true) printf(".");
}
void taskB() {

  while(true) printf("-");
}



typedef void (*constructor) ();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void
callConstructors() {

  for(constructor* i = &start_ctors; i != &end_ctors; ++i)
    (*i)();
}

extern "C" void
kernelMain(void* multiboot_structure, uint32_t macgic) {

  printf("=> Aurora link start...\n");

  //Initializing basic modules
  GDT      gdt;
  IDT      idt(&gdt);
  Screen   screen;
  Keyboard keyboard;
  Mouse    mouse;
  Shell    shell;

  //Pack basic modules
  Skele skele;
  skele.gdt      = &gdt;
  skele.idt      = &idt;
  skele.screen   = &screen;
  skele.keyboard = &keyboard;
  skele.mouse    = &mouse;
  skele.shell    = &shell;

  //Build our computer
  Computer aurora(skele);
  printf("\n=> Basic modules loaded");

  //Multitasking
  Task task1(&gdt, taskA);
  Task task2(&gdt, taskB);
  //IDT::tasks.add(&task1);
  //IDT::tasks.add(&task2);

  //Time
  Time::show();

  aurora.enable(); //Enable modules
  printf("\n=> Going to shell...\n");
  aurora.shell->start();

  while(true);//for GUI later
}
















