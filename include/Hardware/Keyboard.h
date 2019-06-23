#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <Types.h>
#include <Hardware/IO.h>
#include <IDT.h>

const int keyboardId = 0x21;

struct Keyboard : public InterruptHandler {

  static const uint16_t dataPort = 0x60;
  static const uint16_t textPort = 0x64;

  Keyboard();
  ~Keyboard();

  uint32_t handle(uint32_t esp);

};


void enable(Keyboard *kb);


#endif
