#include <Time.h>



uint8_t CMOSRead(uint8_t addr) {

  out8Slow(0x70, 0x80|addr);
  return in8(0x71);
}

namespace Time {


  uint8_t sec() {

    return CMOSRead(0);
  }

  uint8_t minute() {

    return CMOSRead(2);
  }

  uint8_t hour() {

    return CMOSRead(4);
  }

  uint8_t month() {

    return CMOSRead(8);
  }

  uint8_t date() {

    return CMOSRead(7);
  }

  uint8_t year() {

    return CMOSRead(9);
  }

}

