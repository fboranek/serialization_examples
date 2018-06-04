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

    avro_v2::Person personV2;
    personV2.name = "Adam";
    personV2.id = 123;
    personV2.age.set_long(18);    // optional
    personV2.weight.set_long(70); // optional

    // example writing with old schema and reading with new scheme
    try {
        avro::ValidSchema cpxSchemaV1 = readSchema(schemaDirectory + "/Person.v1.avsc");
        avro::ValidSchema cpxSchemaV2 = readSchema(schemaDirectory + "/Person.v2.avsc");

        const std::string output = serializeToString(personV2);
        printBinary(output);

        // test
        {
            avro_v2::Person person;
            std::unique_ptr<avro::InputStream> in = avro::memoryInputStream(
                reinterpret_cast<const uint8_t*>(output.data()), output.size());
            avro::DecoderPtr d = avro::binaryDecoder();
            d->init(*in);
            avro::decode(*d, person);

            print(person);
        }

        // consumer
        {
            avro_v1::Person personV1;
            std::unique_ptr<avro::InputStream> in = avro::memoryInputStream(
                reinterpret_cast<const uint8_t*>(output.data()), output.size());
            avro::DecoderPtr d = avro::resolvingDecoder(
                cpxSchemaV2 /*writer*/, cpxSchemaV1 /*reader*/, avro::binaryDecoder());

            d->init(*in);
            avro::decode(*d, personV1);

            print(personV1);
        }
    }
    catch (std::exception& ex) {
        std::cout << "Fails:  " << ex.what() << std::endl;
        return 2;
    }

    return 0;
}
