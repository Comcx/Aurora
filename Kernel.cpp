
#include "Types.h"
#include "GDT.h"
#include "IDT.h"
#include "Keyboard.h"
#include "Mouse.h"

void printf(char* str) {

    static uint16_t* VideoMemory = (uint16_t*)0xb8000;

    static uint8_t x=0,y=0;

    for(int i = 0; str[i] != '\0'; ++i)
    {
        switch(str[i])
        {
            case '\n':
                x = 0;
                y++;
                break;
            default:
                VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
                x++;
                break;
        }

        if(x >= 80)
        {
            x = 0;
            y++;
        }

        if(y >= 25)
        {
            for(y = 0; y < 25; y++)
                for(x = 0; x < 80; x++)
                    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
            x = 0;
            y = 0;
        }
    }
}

void printfHex(uint8_t key) {

    char* foo = "00";
    char* hex = "0123456789ABCDEF";
    foo[0] = hex[(key >> 4) & 0xF];
    foo[1] = hex[key & 0xF];
    printf(foo);
}
void printfHex16(uint16_t key) {

    printfHex((key >> 8) & 0xFF);
    printfHex( key & 0xFF);
}
extern "C" void printfHex32(uint32_t key) {

    printfHex((key >> 24) & 0xFF);
    printfHex((key >> 16) & 0xFF);
    printfHex((key >> 8) & 0xFF);
    printfHex( key & 0xFF);
}


typedef void (*constructor) ();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void
callConstructors() {

  for(constructor* i = &start_ctors; i != &end_ctors; ++i)
    (*i)();
}

extern "C" void
kernelMain(void* multiboot_structure, uint32_t macgic) {

  printf("=> Aurora link start...\n");

  GDT gdt;
  printf("\n=> Global descriptor table loaded");

  IDT idt(&gdt);
  enable(&idt);
  printf("\n=> Interruption table loaded");

  Keyboard keyboard;
  enable(&keyboard);
  printf("\n=> Keyboard loaded");

  Mouse mouse;
  enable(&mouse);
  printf("\n=> Mouse loaded");

  while(true);
}
















