#include <exception>
#include <string>

enum TokenType {MINUS, PLUS, MUL, DIV, NUMBER, END};
struct Token {
    TokenType type;
    int numberValue;
};

class CalcException: public std::exception {

public:
   CalcException(const std::string& error_msg, int error_code, int pos):
       msg {error_msg},
       code {error_code},
       position {pos}
       {};

   const char * what () const noexcept {
      return msg.c_str();
   }

   int getCode() {
       return code;
   }

   int getPosition() {
       return position;
   }

private:
   std::string msg;
   int code;
   int position;
};

class Calculator {
 public:
    Calculator() {};
    int calc(const char *);
 private:
    int prim(bool = false);
    int term();
    Token nextToken();
    Token curToken {END, 0};
    int curPosition = 0;
    const char *input = nullptr;
};
