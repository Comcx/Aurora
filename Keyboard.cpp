#include "Keyboard.h"


Keyboard::Keyboard()
  : InterruptHandler(0x21) {


}

Keyboard::~Keyboard() {}

uint32_t Keyboard::handle(uint32_t esp) {

  return esp;
}












