#include "IDT.h"
#include "Port.h"

void printf(char *s);
void printfHex(uint8_t k);

GateDesc IDT::idt[256];
bool isHandled[256];
static bool acted = false;

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

  for(uint16_t i = 0; i < 256; ++i) {

    isHandled[i] = false;
    idt[i] = GateDesc(codeSegment, &interruptNull, 0, IDT_INTERRUPT_GATE);
  }
  idt[0x20] = GateDesc(codeSegment, &interrupt0x00, 0, IDT_INTERRUPT_GATE);
  idt[0x21] = GateDesc(codeSegment, &interrupt0x01, 0, IDT_INTERRUPT_GATE);

  isHandled[0x20] = true;
  isHandled[0x21] = true;

  out8Slow(0x20, 0x11);
  out8Slow(0xA0, 0x11);

  out8Slow(0x21, 0x20);
  out8Slow(0xA1, 0x28);

  out8Slow(0x21, 0x04);
  out8Slow(0xA1, 0x02);

  out8Slow(0x21, 0x01);
  out8Slow(0xA1, 0x01);

  out8Slow(0x21, 0x00);
  out8Slow(0xA1, 0x00);

  IDTPointer p;
  p.size = 256 * sizeof(GateDesc);
  p.base = (uint32_t)idt;
  asm volatile("lidt %0" : : "m" (p));
}

IDT::~IDT() {}

void IDT::activate() {

  if(!acted) {
    asm("sti");
    acted = true;
  }
}
void IDT::close() {

  if(acted) {
    asm("cli");
    acted = false;
  }
}


uint32_t handleInterrupt(uint8_t n, uint32_t esp) {

  //if(isHandled[n]) {

    //esp = handlers[interrupt]->HandleInterrupt(esp);
  //}
  //else
  if(n != 0x20) {

    printf("Interrupt 0x");
    printfHex(n);
    printf("\n");
  }

  if(0x20 <= n && n < 0x30) {

    out8Slow(0x20, 0x20);
    if(0x28 <= n)
      out8Slow(0xA0, 0x20);
  }

  return esp;
}
extern "C" uint32_t interrupt(uint8_t n, uint32_t esp) {

  if(acted)
    return handleInterrupt(n, esp);

  return esp;
}









