#ifndef TIME_H
#define TIME_H

#include <Types.h>
#include <Hardware/IO.h>
#include <Hardware/Screen.h>

uint8_t CMOSRead(uint8_t addr);

namespace Time {

  uint8_t sec();
  uint8_t minute();
  uint8_t hour();
  uint8_t date();
  uint8_t month();
  uint8_t year();

  void show();
}



#endif



