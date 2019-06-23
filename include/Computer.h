#ifndef COMPUTER_H
#define COMPUTER_H

#include <Types.h>
#include <GDT.h>
#include <IDT.h>
#include <Hardware/Screen.h>
#include <Hardware/Keyboard.h>
#include <Hardware/Mouse.h>
#include <Shell/Shell.h>
#include <Time.h>

class Computer {

public:
  static GDT      gdt;
  static IDT      idt;
  static Screen   screen;
  static Keyboard keyboard;
  static Mouse    mouse;

  static Shell    shell;

};




#endif

