#ifndef IDT_H
#define IDT_H

#include "Types.h"
#include "Port.h"
#include "GDT.h"


struct GateDesc {

  uint16_t handlerAddressLowBits;
  uint16_t gdt_codeSegmentSelector;
  uint8_t  reserved;
  uint8_t  access;
  uint16_t handlerAddressHighBits;

  GateDesc() {}
  GateDesc(uint16_t offset, void (*handler)(),
           uint8_t  privilege, uint8_t type);


} __attribute__((packed));

struct IDTPointer {

  uint16_t size;
  uint32_t base;
} __attribute__((packed));



struct IDT {

  static GateDesc idt[256];

  IDT() {}
  IDT(GDT *gdt);
  ~IDT();

  void activate();
  void close();
};


extern "C" uint32_t interrupt(uint8_t n, uint32_t esp);

extern "C" void interruptNull();
extern "C" void interrupt0x00();
extern "C" void interrupt0x01();




#endif
