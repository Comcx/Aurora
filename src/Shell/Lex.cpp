#include <Shell/Lex.h>


namespace Lex {


  //char *src;
  char src[1024] = {'(', '1', ' ', '+', ' ', '2', ')', '\0'};
  uint8_t current = 0;

  bool hasNext() {

    return current < 1024 && src[current] != '\0';
  }
  bool isSpace(char c) {

    return
      c == '\0' ||
      c == ' '  ||
      c == '\n' ||
      c == '\t' ;
  }
  void skip() {

    while(isSpace(src[current]) && src[current] != '\0')
      current++;
  }
  Token next() {

    Token ans;
    uint8_t i(0);
    skip();
    if(hasNext()) {

      char cur = src[current];
      if(cur == '(' || cur == ')') {
        ans.value[i++] = cur;
        current++;
      }
      else while(src[current] != '\0' && !isSpace(src[current])) {

          if(src[current] == '(' || src[current] == ')') {

            break;
          }
          ans.value[i++] = src[current];
          current++;
        }
    }
    return ans;
  }

  void test() {

    Token token;
    skip();
    printf("\n");
    printf(src);
    printf("\n");
    //printfHex(current);
    while(hasNext()) {

      token = next();
      printf(token.value);
      printf("\n");
      skip();
    }
  }

}






