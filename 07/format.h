#pragma once
#include <string>
#include <sstream>
#include <vector>


class Formatter {
 private:
    Formatter(const std::string& tpl):tpl{std:move(tpl)}{};
    Formatter(std::string&& tpl):tpl{tpl}{};

    std::string final_format();

    void processArgs() {};

    template <class T>
    void processArgs(T&& val) {
        buf << val;
        vec.push_back(buf.str());
        buf.str("");
    }

    template <class T, class... Args>
    void processArgs(T&& val, Args&&... args) {
        processArgs(val);
        processArgs(std::forward<Args>(args)...);
    }

    template <class... Args>
    std::string format(Args&&... args) {
        processArgs(std::forward<Args>(args)...);
        return final_format();
    }

    template <class... Args>
    friend std::string format(std::string&& tpl, Args&&... args);

    template <class... Args>
    friend std::string format(std::string& tpl, Args&&... args);

    std::string tpl;
    std::vector<std::string> vec;
    std::stringstream buf;
};

template <class... Args>
std::string format(const std::string& tpl, Args&&... args) {
    Formatter formatter{tpl};
    return formatter.format(std::forward<Args>(args)...);
}

template <class... Args>
std::string format(std::string&& tpl, Args&&... args) {
    Formatter formatter{std::move(tpl)};
    return formatter.format(std::forward<Args>(args)...);
}
