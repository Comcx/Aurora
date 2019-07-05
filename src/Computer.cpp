#include <Computer.h>

/*
GDT      Computer::gdt;
IDT      Computer::idt(&Computer::gdt);
Keyboard Computer::keyboard;
Mouse    Computer::mouse;
Screen   Computer::screen;
Shell    Computer::shell;
*/

Computer::Computer() : index(0) {}
Computer::Computer(Skele &s) : index(0) {

  //module[index++] = this->gdt      = s.gdt;
  module[index++] = this->screen   = s.screen;
  module[index++] = this->keyboard = s.keyboard;
  module[index++] = this->mouse    = s.mouse;
  module[index++] = this->idt      = s.idt;
  //module[index++] = this->shell    = s.shell;

}
Computer::~Computer() {}

Computer& Computer::operator+=(Module *m) {

  module[index++] = m;
  return *this;
}

void Computer::enable() {

  for(int i(1); i < index; ++i) {
    if(module[i]) module[i]->enable();
  }
}
void Computer::unable() {

  for(int i(1); i < index; ++i)
    module[i]->unable();
}


