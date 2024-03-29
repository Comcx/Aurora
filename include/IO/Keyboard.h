#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <Util/Type.h>
#include <IO/Screen.h>
#include <IO/IO.h>
#include <IDT.h>
#include <File/File.h>

const int keyboardId = 0x21;

struct Keyboard : public InterruptHandler {

  static const uint16_t dataPort = 0x60;
  static const uint16_t textPort = 0x64;

  Keyboard();
  ~Keyboard();

  uint32_t handle(uint32_t esp);
  void enable();
  void unable();
};





#endif
