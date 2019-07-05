#ifndef SCREEN_H
#define SCREEN_H

#include <Types.h>
#include <Module.h>

class Screen : public Module {

private:
  uint8_t mode;
  uint16_t width;
  uint16_t height;

public:
  Screen();
  Screen(uint16_t width, uint16_t height);
  ~Screen();

  uint16_t getWidth()  {return width;}
  uint16_t getHeight() {return height;}
  void write(char *str);

  void enable();
  void unable();
};

void printf(char *str);
void printfHex(uint8_t key);
void printfHex16(uint16_t key);
extern "C" void printfHex32(uint32_t key);


#endif
