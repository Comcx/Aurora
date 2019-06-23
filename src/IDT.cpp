#include <IDT.h>
#include <Hardware/IO.h>

void printf(char *s);
void printfHex(uint8_t k);
//extern Tasks tasks;

GateDesc IDT::idt[256];
InterruptHandler *IDT::handlers[256];
Tasks IDT::tasks;
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


uint32_t InterruptHandler::handle(uint32_t esp)  {

  return esp;
}
void InterruptHandler::enable() {}
void InterruptHandler::unable() {}


IDT::IDT(GDT *gdt) {

  //  this->tasks = tasks;
  uint16_t codeSegment = gdt->codeSegment();
  const uint8_t IDT_INTERRUPT_GATE = 0xE;

  for(uint16_t i = 0; i < 256; ++i) {

    handlers[i] = 0;
    idt[i] = GateDesc(codeSegment, &interruptNull, 0, IDT_INTERRUPT_GATE);
  }

  idt[0x20] = GateDesc(codeSegment, &interrupt0x00, 0, IDT_INTERRUPT_GATE);
  idt[0x21] = GateDesc(codeSegment, &interrupt0x01, 0, IDT_INTERRUPT_GATE);
  idt[0x2C] = GateDesc(codeSegment, &interrupt0x0C, 0, IDT_INTERRUPT_GATE);

  //remap
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

void IDT::enable() {

  if(!acted) {
    asm("sti");
    acted = true;
  }
}
void IDT::unable() {

  if(acted) {
    asm("cli");
    acted = false;
  }
}


uint32_t handleInterrupt(uint8_t n, uint32_t esp) {

  if(IDT::handlers[n]) {

    esp = IDT::handlers[n]->handle(esp);
  }
  else if(n != 0x20) {

    printf("Interrupt 0x");
    printfHex(n);
    printf("\n");
  }


  if(n == 0x20) {

    esp = (uint32_t)IDT::tasks.schedule((CPUState*)esp);
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









