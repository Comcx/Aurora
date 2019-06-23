#ifndef MOUSE_H
#define MOUSE_H

#include <Types.h>
#include <Hardware/IO.h>
#include <IDT.h>

const int mouseId = 0x21;

struct Mouse : public InterruptHandler {

  static const uint16_t dataPort = 0x60;
  static const uint16_t textPort = 0x64;

  int8_t x, y;
  uint8_t buffer[3];
  uint8_t offset;
  uint8_t buttons;

  Mouse();
  ~Mouse();

  uint32_t handle(uint32_t esp);
  void onMouseDown(uint8_t button);
  void onMouseUp(uint8_t button);
  void onMouseMove(int x, int y);

  void enable();
};





#endif






