#include <cctype>
#include <stdexcept>
#include <string>
#include "serialize.h"


Error Deserializer::process(uint64_t& value) {
    std::string text;
    in >> text;
    try {
        value = std::stoull(text);
    } catch (const std::out_of_range& e) {
        return Error::CorruptedArchive;
    } catch (const std::invalid_argument& e) {
        return Error::CorruptedArchive;
    }
    return Error::NoError;
}

Error Deserializer::process(bool& value) {
    std::string text;
    in >> text;
    if (text == "true")
        value = true;
    else if (text == "false")
        value = false;
    else
        return Error::CorruptedArchive;

    return Error::NoError;
}
