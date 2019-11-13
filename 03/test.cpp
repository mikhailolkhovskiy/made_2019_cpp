#include <iostream>
#include <string>
#include "parser.h"

std::string status(bool b) {
    return b ? "Passed": "Failed";
}


int main() {

    Parser p;
    bool success = true;
    try {
        p.parse("123 aaa");
    } catch (const ParseException &e) {
        success = false;
    }
    std::cout <<"Check without callbacks " << status(success) << std::endl;

    bool onStartCalled = false;
    bool onFinishCalled = false;
    bool onNumberCalled = false;
    bool onStringCalled = false;
    std::string onStringResult = "";
    int onNumberResult = 0;

    auto onStart = [&](){onStartCalled = true;};
    auto onFinish =  [&](){onFinishCalled = true;};
    auto onNumber =  [&](const int& n){onNumberCalled = true; onNumberResult = n;};
    auto onString =  [&](const std::string& s){onStringCalled = true; onStringResult = s;};
    p.setOnStart(onStart);
    p.setOnFinish(onFinish);
    p.setOnNumber(onNumber);
    p.setOnString(onString);
    p.parse("123 bbb");
    std::cout <<"OnStart called " << status(onStartCalled) << std::endl;
    std::cout <<"OnFinish called " << status(onFinishCalled) << std::endl;
    std::cout <<"OnNumber called " << status(onNumberCalled && onNumberResult == 123) << std::endl;
    std::cout <<"OnString called " << status(onStringCalled && onStringResult == "bbb") << std::endl;

    std::cout <<"Tests completed" << std::endl;
}
