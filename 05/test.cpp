#include <iostream>
#include <sstream>
#include <string>
#include <assert.h>

#include "serialize.h"

std::string status(bool b) {
    return b ? "Passed": "Failed";
}

struct Data {
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer) {
        return serializer(a, b, c);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer) {
        return deserializer(a, b, c);
    }
};

int main() {

    Data x { 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Data y { 0, false, 0 };
    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);
    std::cout <<"Deserialized without errors " << status(err == Error::NoError) << std::endl;
    bool equals = x.a == y.a && x.b == y.b && x.c == y.c;
    std::cout <<"Original data == deserialized " << status(equals) << std::endl;

    const Error errEmpty = deserializer.load(y);
    std::cout <<"Error on empty stream " << status(errEmpty != Error::NoError) << std::endl;

    std::stringstream streamID;
    Deserializer deserializerID(streamID);
    streamID << "2222233333333333333333333333333322 true 4";
    const Error errIvalidData = deserializerID.load(y);
    std::cout <<"Error on invalid data " << status(errIvalidData != Error::NoError) << std::endl;

    std::cout <<"Tests completed" << std::endl;
}
