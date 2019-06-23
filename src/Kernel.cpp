
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

  GDT&      gdt      = Computer::gdt;
  IDT&      idt      = Computer::idt;
  Keyboard& keyboard = Computer::keyboard;
  Mouse&    mouse    = Computer::mouse;
  Shell&    shell    = Computer::shell;

  keyboard.enable();
  mouse   .enable();
  printf("\n=> Hardware loaded");

  //Multitasking
  Task task1(&Computer::gdt, taskA);
  Task task2(&Computer::gdt, taskB);
  //IDT::tasks.add(&task1);
  //IDT::tasks.add(&task2);

  //Time
  uint8_t date   = Time::date();
  uint8_t hour   = Time::hour();
  uint8_t year   = Time::year();
  uint8_t month  = Time::month();
  uint8_t minute = Time::minute();
  printf("\n=> Time: ");
  printfHex(year);
  printf(":");
  printfHex(month);
  printf(":");
  printfHex(date);
  printf(":");
  printfHex(hour);
  printf(":");
  printfHex(minute);


  //Enable interruptions!
  idt.enable();
  printf("\n=> Interruptions loaded");

  printf("\n=> Going to shell...\n");
  shell.start();

  while(true);//for GUI later
}
















