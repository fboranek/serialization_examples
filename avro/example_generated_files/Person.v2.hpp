/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef _VOLUMES_ENCUSERDATA_WORKSPACE_GITHUB_COM_SERIALIZATION_EXAMPLES_BUILD_AVRO_PERSON_V2_HPP_2521695476__H_
#define _VOLUMES_ENCUSERDATA_WORKSPACE_GITHUB_COM_SERIALIZATION_EXAMPLES_BUILD_AVRO_PERSON_V2_HPP_2521695476__H_


#include "avro/Decoder.hh"
#include "avro/Encoder.hh"
#include "avro/Specific.hh"
#include "boost/any.hpp"
#include <sstream>

namespace avro_v2 {
struct _Person_v2_avsc_Union__0__ {
private:
    size_t idx_;
    boost::any value_;

public:
    size_t idx() const { return idx_; }
    bool is_null() const { return (idx_ == 0); }
    void set_null()
    {
        idx_ = 0;
        value_ = boost::any();
    }
    int64_t get_long() const;
    void set_long(const int64_t& v);
    _Person_v2_avsc_Union__0__();
};

struct _Person_v2_avsc_Union__1__ {
private:
    size_t idx_;
    boost::any value_;

public:
    size_t idx() const { return idx_; }
    bool is_null() const { return (idx_ == 0); }
    void set_null()
    {
        idx_ = 0;
        value_ = boost::any();
    }
    int64_t get_long() const;
    void set_long(const int64_t& v);
    _Person_v2_avsc_Union__1__();
};

struct Person {
    typedef _Person_v2_avsc_Union__0__ weight_t;
    typedef _Person_v2_avsc_Union__1__ age_t;
    std::string name;
    int32_t id;
    weight_t weight;
    age_t age;
    Person()
        : name(std::string())
        , id(int32_t())
        , weight(weight_t())
        , age(age_t())
    {}
};

inline int64_t _Person_v2_avsc_Union__0__::get_long() const
{
    if (idx_ != 1) {
        throw avro::Exception("Invalid type for union");
    }
    return boost::any_cast<int64_t>(value_);
}

inline void _Person_v2_avsc_Union__0__::set_long(const int64_t& v)
{
    idx_ = 1;
    value_ = v;
}

inline int64_t _Person_v2_avsc_Union__1__::get_long() const
{
    if (idx_ != 1) {
        throw avro::Exception("Invalid type for union");
    }
    return boost::any_cast<int64_t>(value_);
}

inline void _Person_v2_avsc_Union__1__::set_long(const int64_t& v)
{
    idx_ = 1;
    value_ = v;
}

inline _Person_v2_avsc_Union__0__::_Person_v2_avsc_Union__0__()
    : idx_(0)
{}
inline _Person_v2_avsc_Union__1__::_Person_v2_avsc_Union__1__()
    : idx_(0)
{}
} // namespace avro_v2
namespace avro {
template<>
struct codec_traits<avro_v2::_Person_v2_avsc_Union__0__> {
    static void encode(Encoder& e, avro_v2::_Person_v2_avsc_Union__0__ v)
    {
        e.encodeUnionIndex(v.idx());
        switch (v.idx()) {
        case 0: e.encodeNull(); break;
        case 1: avro::encode(e, v.get_long()); break;
        }
    }
    static void decode(Decoder& d, avro_v2::_Person_v2_avsc_Union__0__& v)
    {
        size_t n = d.decodeUnionIndex();
        if (n >= 2) {
            throw avro::Exception("Union index too big");
        }
        switch (n) {
        case 0:
            d.decodeNull();
            v.set_null();
            break;
        case 1: {
            int64_t vv;
            avro::decode(d, vv);
            v.set_long(vv);
        } break;
        }
    }
};

template<>
struct codec_traits<avro_v2::_Person_v2_avsc_Union__1__> {
    static void encode(Encoder& e, avro_v2::_Person_v2_avsc_Union__1__ v)
    {
        e.encodeUnionIndex(v.idx());
        switch (v.idx()) {
        case 0: e.encodeNull(); break;
        case 1: avro::encode(e, v.get_long()); break;
        }
    }
    static void decode(Decoder& d, avro_v2::_Person_v2_avsc_Union__1__& v)
    {
        size_t n = d.decodeUnionIndex();
        if (n >= 2) {
            throw avro::Exception("Union index too big");
        }
        switch (n) {
        case 0:
            d.decodeNull();
            v.set_null();
            break;
        case 1: {
            int64_t vv;
            avro::decode(d, vv);
            v.set_long(vv);
        } break;
        }
    }
};

template<>
struct codec_traits<avro_v2::Person> {
    static void encode(Encoder& e, const avro_v2::Person& v)
    {
        avro::encode(e, v.name);
        avro::encode(e, v.id);
        avro::encode(e, v.weight);
        avro::encode(e, v.age);
    }
    static void decode(Decoder& d, avro_v2::Person& v)
    {
        if (avro::ResolvingDecoder* rd = dynamic_cast<avro::ResolvingDecoder*>(&d)) {
            const std::vector<size_t> fo = rd->fieldOrder();
            for (std::vector<size_t>::const_iterator it = fo.begin(); it != fo.end(); ++it) {
                switch (*it) {
                case 0: avro::decode(d, v.name); break;
                case 1: avro::decode(d, v.id); break;
                case 2: avro::decode(d, v.weight); break;
                case 3: avro::decode(d, v.age); break;
                default: break;
                }
            }
        } else {
            avro::decode(d, v.name);
            avro::decode(d, v.id);
            avro::decode(d, v.weight);
            avro::decode(d, v.age);
        }
    }
};

} // namespace avro
#endif
