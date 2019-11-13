#include "parser.h"
#include <cctype>
#include <iostream>


void Parser::parse(const std::string& str) {
    if (onStart != nullptr) {
        onStart();
    }

    int cur = 0;
    int len = str.size();
    std::string buff;
    while (cur < len) {
        while (std::isspace(str[cur]) && cur < len) {
            ++cur;
        }
        bool digitsOnly = true;
        while (!std::isspace(str[cur]) && cur < len) {
          if (!std::isdigit(str[cur])) {
              digitsOnly = false;
          }
          buff.push_back(str[cur]);
          ++cur;
        }
        if (!buff.empty()) {
          if (digitsOnly && onNumber != nullptr) {
            int v = 0;
            try {
                v = std::stoi(buff);
            } catch (std::out_of_range &e) {
                throw ParseException("Number \"" + buff + "\" is too large for int");
            }
            onNumber(v);
          } else if (onString != nullptr) {
            onString(buff);
          }
        }
        buff.clear();
    }

    if (onFinish != nullptr) {
        onFinish();
    }
}
