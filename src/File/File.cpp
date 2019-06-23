#include <File/File.h>


File::File() {}
File::~File() {}

StdOut::StdOut() : current(0) {}
StdOut::~StdOut() {}

StdIn::StdIn() : current(0), flushing(false) {}
StdIn::~StdIn() {}

StdIn Files::stdin;
StdOut Files::stdout;

void StdOut::write(char c) {

}

void StdIn::write(char c) {

  if(flushing) current = 0;
  buffer[current++] = c;
  if(c == '\n') flushing = true;
  else if(flushing) flushing = false;
  //buffer[current] = '\0';
}

char *StdIn::read(char *addr) {

  int i = 0;
  for(; i < current; ++i) {

    addr[i] = buffer[i];
  }
  addr[i] = '\0';
  //printf(addr[current]);
  //printfHex16(current);
  if(flushing) {

    printf(addr);
    current = 0;
    flushing = false;
  }
  return addr;
}






