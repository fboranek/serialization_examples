//
//	Author   : Frantisek Boranek
//	License  : Boost Software License (http://www.boost.org/users/license.html)
//

#include "utils.h"

int main(int argc, char* argv[])
{
    if (argc < 2) {
        return 1;
    }
    std::cout << "Using schema directory: " << argv[1] << std::endl;
    std::string schemaDirectory = argv[1];

    avro_v1::Person personV1;
    personV1.name = "Adam";
    personV1.id = 123;
    personV1.age.set_long(18); // optional

    // example writing with old schema and reading with new scheme
    try {
        avro::ValidSchema cpxSchemaV1 = readSchema(schemaDirectory + "/Person.v1.avsc");
        avro::ValidSchema cpxSchemaV2 = readSchema(schemaDirectory + "/Person.v2.avsc");

        const std::string output = serializeToString(personV1);
        printBinary(output);

        // test
        {
            avro_v1::Person person;
            std::unique_ptr<avro::InputStream> in = avro::memoryInputStream(
                reinterpret_cast<const uint8_t*>(output.data()), output.size());
            avro::DecoderPtr d = avro::binaryDecoder();
            d->init(*in);
            avro::decode(*d, person);

            print(person);
        }

        // consumer
        {
            avro_v2::Person personV2;
            std::unique_ptr<avro::InputStream> in = avro::memoryInputStream(
                reinterpret_cast<const uint8_t*>(output.data()), output.size());
            avro::DecoderPtr d = avro::resolvingDecoder(
                cpxSchemaV1 /*writer*/, cpxSchemaV2 /*reader*/, avro::binaryDecoder());

            d->init(*in);
            avro::decode(*d, personV2); // Don't work! Rise "EOF reached"

            print(personV2);
        }
    }
    catch (std::exception& ex) {
        std::cout << "Fails:  " << ex.what() << std::endl;
        return 2;
    }

    return 0;
}
