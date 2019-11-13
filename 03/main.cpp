#include <iostream>
#include "parser.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
      std::cout << "Use: main  \"string\"";
      return 1;
  } else {
      Parser p;
      auto onStart =  [](){std::cout << "Start parsing" << std::endl;};
      auto onFinish =  [](){std::cout << "Finish parsing" << std::endl;};
      auto onNumber =  [](const int& n){std::cout << "Number: " << n << std::endl;};
      auto onString =  [](const std::string& s){std::cout << "String: " << s << std::endl;};
      p.setOnStart(onStart);
      p.setOnFinish(onFinish);
      p.setOnNumber(onNumber);
      p.setOnString(onString);
      try {
          p.parse(argv[1]);
      } catch (const ParseException &exc) {
          std::cerr << "Error: " << exc.what();
      }
  }
}
