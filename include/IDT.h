#ifndef IDT_H
#define IDT_H

#include <Util/Type.h>
#include <Module.h>
#include <IO/Screen.h>
#include <IO/IO.h>
#include <GDT.h>
#include <Task.h>


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

struct InterruptHandler : public Module {

  uint8_t n;
  bool acted;

  InterruptHandler() {}
  InterruptHandler(uint8_t num): n(num), acted(false) {}
  virtual uint32_t handle(uint32_t esp);

  virtual void enable();
  virtual void unable();
};

struct IDT : public Module {

  static GateDesc idt[256];
  static InterruptHandler *handlers[256];
  static Tasks tasks;

  IDT() {}
  IDT(GDT *gdt);
  ~IDT();

  void enable();
  void unable();
};

//void enable(IDT *idt);
//void unable(IDT *idt);

extern "C" uint32_t interrupt(uint8_t n, uint32_t esp);

extern "C" void interruptNull();
extern "C" void interrupt0x00();
extern "C" void interrupt0x01();
extern "C" void interrupt0x0C();



#endif
