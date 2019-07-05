#ifndef TIME_H
#define TIME_H

#include <Util/Type.h>
#include <Hardware/IO.h>
#include <Hardware/Screen.h>

uint8_t CMOSRead(uint8_t addr);

namespace Time {
  /*
  class Timer {

  private:
    sec
  public:

  };*/
  uint8_t sec();
  uint8_t minute();
  uint8_t hour();
  uint8_t date();
  uint8_t month();
  uint8_t year();

  void show();
}



#endif



