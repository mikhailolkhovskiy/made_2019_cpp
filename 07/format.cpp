#include "format.h"
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>


std::string Formatter::final_format() {
    size_t i = 0;
    while (i < tpl.size()) {
        if (tpl[i] == '{') {
            size_t j = i + 1;
            while (j < tpl.size() && tpl[j] != '}' && std::isdigit(tpl[j])) {
                ++j;
            }
            if (j == tpl.size() || tpl[j] != '}') {
                throw std::runtime_error("Invalid placeholder");
            }
            size_t placeholder = 0;
            try {
                auto t = tpl.substr(i + 1, j - (i + 1));
                placeholder = std::stoul(t);
            } catch (std::logic_error& e) {
                throw std::runtime_error("Invalid placeholder");
            }
            if (placeholder < 0 || placeholder >= vec.size()) {
                throw std::runtime_error("Out of range placeholder");
            }
            buf << vec[placeholder];
            i = j + 1;
        } else if (tpl[i] == '}') {
            throw std::runtime_error("Unexpected }");
        } else {
            buf << tpl[i];
            ++i;
        }
    }

    return buf.str();
}
