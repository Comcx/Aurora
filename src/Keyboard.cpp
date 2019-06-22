#include <Keyboard.h>


void printf(char *str);
void printfHex(uint8_t);

static void onKeyDown(char c) {

  char s[2] = {c};
  printf(s);
}
static void onKeyUp(char c) {

}

Keyboard::Keyboard()
  : InterruptHandler(0x21) {


}

Keyboard::~Keyboard() {}

uint32_t keyboardHandler(uint32_t esp);
uint32_t Keyboard::handle(uint32_t esp) {

  return keyboardHandler(esp);
}


uint32_t keyboardHandler(uint32_t esp) {

  uint8_t key = in8(Keyboard::dataPort);

  if(key < 0x80) {

    switch(key) {

    case 0x02: onKeyDown('1'); break;
    case 0x03: onKeyDown('2'); break;
    case 0x04: onKeyDown('3'); break;
    case 0x05: onKeyDown('4'); break;
    case 0x06: onKeyDown('5'); break;
    case 0x07: onKeyDown('6'); break;
    case 0x08: onKeyDown('7'); break;
    case 0x09: onKeyDown('8'); break;
    case 0x0A: onKeyDown('9'); break;
    case 0x0B: onKeyDown('0'); break;

    case 0x10: onKeyDown('q'); break;
    case 0x11: onKeyDown('w'); break;
    case 0x12: onKeyDown('e'); break;
    case 0x13: onKeyDown('r'); break;
    case 0x14: onKeyDown('t'); break;
    case 0x15: onKeyDown('z'); break;
    case 0x16: onKeyDown('u'); break;
    case 0x17: onKeyDown('i'); break;
    case 0x18: onKeyDown('o'); break;
    case 0x19: onKeyDown('p'); break;

    case 0x1E: onKeyDown('a'); break;
    case 0x1F: onKeyDown('s'); break;
    case 0x20: onKeyDown('d'); break;
    case 0x21: onKeyDown('f'); break;
    case 0x22: onKeyDown('g'); break;
    case 0x23: onKeyDown('h'); break;
    case 0x24: onKeyDown('j'); break;
    case 0x25: onKeyDown('k'); break;
    case 0x26: onKeyDown('l'); break;

    case 0x2C: onKeyDown('y'); break;
    case 0x2D: onKeyDown('x'); break;
    case 0x2E: onKeyDown('c'); break;
    case 0x2F: onKeyDown('v'); break;
    case 0x30: onKeyDown('b'); break;
    case 0x31: onKeyDown('n'); break;
    case 0x32: onKeyDown('m'); break;
    case 0x33: onKeyDown(','); break;
    case 0x34: onKeyDown('.'); break;
    case 0x35: onKeyDown('-'); break;

    case 0x1C: onKeyDown('\n'); break;
    case 0x39: onKeyDown(' '); break;

    default: {
        printf("KEY 0x");
        printfHex(key);
        break;
      }
    }
  }

  return esp;
}




void enable(Keyboard *kb) {

  //uint32_t(Keyboard::*)(uint32_t) fp = &Keyboard::handle;
  if(kb->acted) return;
  IDT::handlers[0x21] = kb;

  uint16_t textPort = kb->textPort;
  uint16_t dataPort = kb->dataPort;

  while(in8(textPort) & 0x1)
    in8(dataPort);
  out8(textPort, 0xae); // activate interrupts
  out8(textPort, 0x20); // command 0x20 = read controller command byte
  uint8_t status = (in8(dataPort) | 1) & ~0x10;
  out8(textPort, 0x60); // command 0x60 = set controller command byte
  out8(dataPort, status);
  out8(dataPort, 0xf4);

  kb->acted = true;
}






