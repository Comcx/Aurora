#include <Util/Type.h>
#include <IO/Screen.h>

namespace Lex {

  struct Token {

    char value[128];
  };

  
  bool hasNext();
  bool isSpace(char c);
  void skip();
  Token next();

  void test();

}



