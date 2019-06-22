#include <Mouse.h>


void printf(char *s);
void printfHex(uint8_t);

void Mouse::onMouseDown(uint8_t button) {

  printf("Mouse down ");
}

void Mouse::onMouseUp(uint8_t button) {

  printf("Mouse up ");
}

void Mouse::onMouseMove(int xoffset, int yoffset) {

  static uint16_t* VideoMemory = (uint16_t*)0xb8000;
  VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                      | (VideoMemory[80*y+x] & 0xF000) >> 4
                      | (VideoMemory[80*y+x] & 0x00FF);

  //xoffset = x == 79 ? -79 : 1;
  //yoffset = 1;
  x += xoffset;
  if(x >= 80) x = 79;
  if(x < 0) x = 0;
  y += yoffset;
  if(y >= 25) y = 24;
  if(y < 0) y = 0;
  /*
  printf("X: ");
  printfHex(xoffset);
  printf(", y: ");
  printfHex(yoffset);
  printf("\n");
  */

  VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                      | (VideoMemory[80*y+x] & 0xF000) >> 4
                      | (VideoMemory[80*y+x] & 0x00FF);
}


Mouse::Mouse(): InterruptHandler(0x2C) {

  uint16_t* VideoMemory = (uint16_t*)0xb8000;
  x = 40;
  y = 12;
  VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0x0F00) << 4
                      | (VideoMemory[80*y+x] & 0xF000) >> 4
                      | (VideoMemory[80*y+x] & 0x00FF);
}

Mouse::~Mouse() {}

void enable(Mouse *ms) {

  if(ms->acted) return;
  IDT::handlers[0x2C] = ms;
  ms->offset = 0;
  ms->buttons = 0;

  uint16_t textPort = Mouse::textPort;
  uint16_t dataPort = Mouse::dataPort;

  out8(textPort, 0xA8);
  out8(textPort, 0x20); // command 0x60 = read controller command byte
  uint8_t status = in8(dataPort) | 2;
  out8(textPort, 0x60); // command 0x60 = set controller command byte
  out8(dataPort, status);

  out8(textPort, 0xD4);
  out8(dataPort, 0xF4);
  in8(dataPort);
}

uint32_t Mouse::handle(uint32_t esp) {

  uint8_t status = in8(textPort);
  if (!(status & 0x20))
    return esp;

  buffer[offset] = in8(dataPort);
  offset = (offset + 1) % 3;

  if(offset == 0) {

    if(buffer[2] != 0 || buffer[0] != 0) {

      onMouseMove((int8_t)buffer[2], -((int8_t)buffer[0]));
    }

    for(uint8_t i = 0; i < 3; i++) {

      if((buffer[1] & (0x1<<i)) != (buttons & (0x1<<i))) {

        if(buttons & (0x1<<i))
          onMouseUp(i+1);
        else
          onMouseDown(i+1);
      }
    }
    buttons = buffer[1];
  }

  return esp;
}









