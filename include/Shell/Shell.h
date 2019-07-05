#ifndef SHELL_H
#define SHELL_H

#include <Types.h>
#include <Module.h>
#include <Hardware/Screen.h>
#include <File/File.h>

class Shell : public Module {

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


