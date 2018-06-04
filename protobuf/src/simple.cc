//
//	Author   : Frantisek Boranek
//	License  : Boost Software License (http://www.boost.org/users/license.html)
//

#include "utils.h"

int main(int argc, char* argv[])
{
    v1::Person personV1;
    personV1.set_name("Adam");
    personV1.set_id(123);
    personV1.set_age(18); // optional

    // using the same schema for writing/reading

    std::string data = personV1.SerializeAsString();

    v2::Person personV2;
    personV2.ParseFromString(data);

    print(personV1);
    print(personV2);

    return 0;
}
