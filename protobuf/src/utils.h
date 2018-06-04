//
//	Author   : Frantisek Boranek
//	License  : Boost Software License (http://www.boost.org/users/license.html)
//

#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

#include "Person.v1.pb.h"
#include "Person.v2.pb.h"

template<class P>
void printBase(const P& person)
{
    std::cout << "name: " << person.name() << ", id: " << person.id();
}

inline void print(const v1::Person& person)
{
    std::cout << "{";
    printBase(person);

    std::cout << ", age: ";
    if (person.has_age())
        std::cout << person.age();
    else
        std::cout << "null";

    std::cout << "}" << std::endl;
}

inline void print(const v2::Person& person)
{
    std::cout << "{";
    printBase(person);

    // in proto 3 was function 'has_field' removed for primitives
    std::cout << ", age: " << person.age() << ", weight: " << person.weight();
    std::cout << "}" << std::endl;
}
