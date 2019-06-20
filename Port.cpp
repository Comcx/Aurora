#include "Port.h"


uint8_t in8(uint16_t port) {

  uint8_t result;
  __asm__ volatile("inb %1, %0" : "=a" (result) : "Nd" (port));
  return result;
}

void out8(uint16_t port, uint8_t data) {

  __asm__ volatile("outb %0, %1" : : "a" (data), "Nd" (port));
}

void out8Slow(uint16_t port, uint8_t data) {

  __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:"
                   : : "a" (data), "Nd" (port));
}



uint16_t in16(uint16_t port) {

  uint16_t result;
  __asm__ volatile("inw %1, %0" : "=a" (result) : "Nd" (port));
  return result;
}

void out16(uint16_t port, uint16_t data) {

  __asm__ volatile("outw %0, %1" : : "a" (data), "Nd" (port));
}


uint32_t in32(uint16_t port) {

  uint32_t result;
  __asm__ volatile("inl %1, %0" : "=a" (result) : "Nd" (port));
  return result;
}

void out32(uint16_t port, uint32_t data) {

  __asm__ volatile("outl %0, %1" : : "a"(data), "Nd" (port));
}

