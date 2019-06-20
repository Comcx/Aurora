#ifndef GDT_H
#define GDT_H

#include "Types.h"

struct SegDesc {

private:
  uint16_t limit_lo;
  uint16_t base_lo;
  uint8_t base_hi;
  uint8_t type;
  uint8_t limit_hi;
  uint8_t base_vhi;

public:
  SegDesc(uint32_t base, uint32_t limit, uint8_t type);
  uint32_t base();
  uint32_t limit();

} __attribute__((packed));


struct GDT {

private:
  SegDesc nullSegSelector;
  SegDesc unusedSegSelector;

public:
  SegDesc codeSegSelector;
  SegDesc dataSegSelector;

  GDT();
  ~GDT();

  uint16_t dataSegment();
  uint16_t codeSegment();
}__attribute__((packed));










#endif

