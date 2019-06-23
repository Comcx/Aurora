#ifndef FILE_H
#define FILE_H

#include <Types.h>
#include <Hardware/Screen.h>

class File {

protected:
  uint32_t id;

public:
  File();
  ~File();
};

class StdOut : public File {

private:
  char buffer[512];
  uint16_t current;

public:
  StdOut();
  ~StdOut();
  void write(char c);
};

class StdIn : public File {

 private:
  char buffer[512];
  uint16_t current;
  bool flushing;

 public:
  StdIn();
  ~StdIn();
  bool isFlushing() {return flushing;}
  char* read(char *addr);
  void write(char c);
};


class Files {

private:
  File files[256];

public:
  static StdIn stdin;
  static StdOut stdout;

  Files() {}
  ~Files() {}
};





#endif


