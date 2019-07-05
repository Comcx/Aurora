
#include <Computer.h>
#include <Time.h>


int i = 0;

void taskA() {

  while(true) {

    if(i%1000000000 == 0) {
      printf("\ntask0");
      printf(".");
    }
    i++;
  }
}
void taskB() {

  while(true) {

    if(i%1000000001 == 0) {

      printf("\ntask1");
      printf("#");
    }
    i++;
  }
}

void shell() {

  Shell sh;
  sh.start();
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

  //Pack basic modules
  Skele skele;
  skele.gdt      = &gdt;
  skele.idt      = &idt;
  skele.screen   = &screen;
  skele.keyboard = &keyboard;
  skele.mouse    = &mouse;

  //Build our computer
  Computer aurora(skele);
  printf("\n=> Basic modules loaded");

  //Multitasking
  Task task0(&gdt, taskA, 4);
  Task task1(&gdt, taskB, 5);
  Task init(&gdt, shell, 6);
  //IDT::tasks.add(&init);
  //IDT::tasks.add(&task0);
  //IDT::tasks.add(&task1);

  //Time
  Time::show();

  //Lex::src = "1 + 2";
  Lex::test();

  aurora.enable(); //Enable modules
  printf("\n=> Going to shell...\n");
  //aurora.shell->start();

  while(true);//for GUI later
}
















