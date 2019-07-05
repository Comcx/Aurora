#ifndef COMPUTER_H
#define COMPUTER_H

#include <Util/Type.h>
#include <Module.h>
#include <GDT.h>
#include <IDT.h>
#include <Hardware/Screen.h>
#include <Hardware/Keyboard.h>
#include <Hardware/Mouse.h>
#include <Shell/Shell.h>
#include <Shell/Lex.h>
#include <Time.h>

struct Skele {

  GDT      *gdt;
  IDT      *idt;
  Screen   *screen;
  Keyboard *keyboard;
  Mouse    *mouse;

  //  Shell    *shell;
};


class Computer : Module {

public:
  GDT      *gdt;
  IDT      *idt;
  Screen   *screen;
  Keyboard *keyboard;
  Mouse    *mouse;

  //Shell    *shell;

  uint8_t index;
  Module *module[256]; //256 max here

  Computer();
  Computer(Skele &skele);
  ~Computer();
  Computer& operator+=(Module *m);

  void enable();
  void unable();

};




#endif

