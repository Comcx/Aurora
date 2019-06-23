#include <Computer.h>


GDT      Computer::gdt;
IDT      Computer::idt(&Computer::gdt);
Keyboard Computer::keyboard;
Mouse    Computer::mouse;
Screen   Computer::screen;
Shell    Computer::shell;

