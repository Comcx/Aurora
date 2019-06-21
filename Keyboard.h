#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "Types.h"
#include "Port.h"
#include "IDT.h"

const int keyboardId = 0x21;

struct Keyboard : public InterruptHandler {

 private:
  static const uint16_t dataPort = 0x60;
  static const uint16_t textPort = 0x64;

 public:
  Keyboard();
  ~Keyboard();

  uint32_t handle(uint32_t esp);

};





#endif
