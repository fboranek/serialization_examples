//
//	Author   : Frantisek Boranek
//	License  : Boost Software License (http://www.boost.org/users/license.html)
//

#include "utils.h"

int main(int argc, char* argv[])
{
    v2::Person personV2;
    personV2.set_name("Adam");
    personV2.set_id(123);
    personV2.set_age(18);    // optional
    personV2.set_weight(70); // optional

    // example writing with old schema and reading with new scheme

    // producer (new schema)
    const std::string data = personV2.SerializeAsString();
    print(personV2);

    // consumer (old schema)
    {
        v1::Person personV1;
        personV1.ParseFromString(data);
        print(personV1);
    }

    // binary representation wasn't changed among versions Protocol Buffers
    {
        v1::Person personV1;
        personV1.set_name("Adam");
        personV1.set_id(123);
        personV1.set_age(18); // optional

        v2::Person personV2;
        personV2.set_name("Adam");
        personV2.set_id(123);
        personV2.set_age(18); // optional

        if (personV1.SerializeAsString() == personV2.SerializeAsString()) {
            std::cout << "Protobuf 2 and 3 are binary compatible." << std::endl;
        }
    }

    return 0;
}
