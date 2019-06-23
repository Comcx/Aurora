#include <Shell/Shell.h>


Shell::Shell() {}
Shell::~Shell() {}

void Shell::start() {//just for basic test!!

  bool loop = true;
  char tmp[256];
  while(loop) {
    printf("\n> ");
    while(true) {
      if(Files::stdin.isFlushing()) {
        printf("You typed ");
        Files::stdin.read(tmp);
        break;
      }

    }

  }
}

void Shell::enable() {}
void Shell::unable() {}










