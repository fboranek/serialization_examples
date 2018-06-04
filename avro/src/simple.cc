//
//	Author   : Frantisek Boranek
//	License  : Boost Software License (http://www.boost.org/users/license.html)
//

#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

#include "utils.h"

int main(int argc, char* argv[])
{
    avro_v1::Person personV1;
    personV1.name = "Adam";
    personV1.id = 123;
    personV1.age.set_long(18); // optional

    // using the same schema for writing/reading

    std::unique_ptr<avro::OutputStream> out = avro::memoryOutputStream();
    avro::EncoderPtr e = avro::binaryEncoder();
    e->init(*out);
    avro::encode(*e, personV1);

    avro_v1::Person person;
    std::unique_ptr<avro::InputStream> in = avro::memoryInputStream(*out);
    avro::DecoderPtr d = avro::binaryDecoder();
    d->init(*in);
    avro::decode(*d, person);

    print(person);

    return 0;
}
