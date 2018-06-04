//
//	Author   : Frantisek Boranek
//	License  : Boost Software License (http://www.boost.org/users/license.html)
//
#include "utils.h"

#include <iomanip>

avro::ValidSchema readSchema(const std::string& filename)
{
    avro::ValidSchema cpxSchema;
    std::ifstream in(filename);
    if (!in) {
        throw std::runtime_error("Failed to read: " + filename);
    }
    avro::compileJsonSchema(in, cpxSchema);
    return cpxSchema;
};

template<class P>
void printBase(const P& person)
{
    std::cout << "name: " << person.name << ", id: " << person.id << ", age: ";

    if (person.age.is_null())
        std::cout << "null";
    else
        std::cout << person.age.get_long();
}


void print(const avro_v1::Person& person)
{
    std::cout << "{";
    printBase(person);
    std::cout << "}" << std::endl;
}

void print(const avro_v2::Person& person)
{
    std::cout << "{";
    printBase(person);

    std::cout << ", weight: ";
    if (person.weight.is_null())
        std::cout << "null";
    else
        std::cout << person.weight.get_long();

    std::cout << "}" << std::endl;
}

void printBinary(const std::string& data)
{
    std::cout << "[";
    std::stringstream ss;
    for (unsigned char c : data) {
        ss << std::hex << std::setfill('0') << std::setw(2) << static_cast<unsigned>(c) << ' ';
    }
    std::cout << ss.str() << "]" << std::endl;
}
