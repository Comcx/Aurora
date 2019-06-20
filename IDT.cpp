#include "IDT.h"


void printf(char *s);

GateDesc IDT::idt[256];

GateDesc::GateDesc(uint16_t offset,
                   void (*handler)(),
                   uint8_t  privilege,
                   uint8_t type) {

  this->handlerAddressLowBits   = ((uint32_t) handler) & 0xFFFF;
  this->handlerAddressHighBits  = (((uint32_t) handler) >> 16) & 0xFFFF;
  this->gdt_codeSegmentSelector = offset;

  const uint8_t IDT_DESC_PRESENT = 0x80;
  this->access = IDT_DESC_PRESENT | ((privilege & 3) << 5) | type;
  this->reserved = 0;
}

IDT::IDT(GDT *gdt) {

  uint16_t codeSegment = gdt->codeSegment();
  const uint8_t IDT_INTERRUPT_GATE = 0xE;

  for(uint16_t i = 0; i < 256; ++i)
    idt[i] = GateDesc(codeSegment, &interruptNull, 0, IDT_INTERRUPT_GATE);

  idt[0x20] = GateDesc(codeSegment, &interrupt0x00, 0, IDT_INTERRUPT_GATE);
  idt[0x21] = GateDesc(codeSegment, &interrupt0x01, 0, IDT_INTERRUPT_GATE);

  IDTPointer p;
  p.size = 256 * sizeof(GateDesc);
  p.base = (uint32_t)idt;
  asm volatile("lidt %0" : : "m" (p));
}

IDT::~IDT() {}

void IDT::activate() {

  asm("sti");
}


extern "C" uint32_t interrupt(uint8_t n, uint32_t esp) {

  printf("Interrupt!\n");

  return esp;
}









