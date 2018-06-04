//
//	Author   : Frantisek Boranek
//	License  : Boost Software License (http://www.boost.org/users/license.html)
//
#pragma once

#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

#include "avro/Compiler.hh"
#include "avro/ValidSchema.hh"

#include "Person.v1.hpp"
#include "Person.v2.hpp"

avro::ValidSchema readSchema(const std::string& filename);

// serialize to string
template<class P>
std::string serializeToString(const P& person)
{
    std::stringstream ss;
    std::unique_ptr<avro::OutputStream> out = avro::ostreamOutputStream(ss);
    avro::EncoderPtr e = avro::binaryEncoder();
    e->init(*out);
    avro::encode(*e, person);
    e->flush();
    return ss.str();
}

void print(const avro_v1::Person& person);
void print(const avro_v2::Person& person);

void printBinary(const std::string& data);
