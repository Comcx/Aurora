#ifndef SHELL_H
#define SHELL_H

#include <Types.h>
#include <Hardware/Hardware.h>
#include <Hardware/Screen.h>
#include <File/File.h>

class Shell : public Hardware {

private:
  int n;

public:
  Shell();
  ~Shell();

  void start();

  void enable();
  void unable();

};





#endif


