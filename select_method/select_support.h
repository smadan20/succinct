//
// Created by Madan, Sanna (NIH/NCI) [F] on 10/29/20.
//

#ifndef SELECT_METHOD_SELECT_SUPPORT_H
#define SELECT_METHOD_SELECT_SUPPORT_H
#include <cstdint>
#include <string>
#include <sdsl/bit_vectors.hpp>
#include <sdsl/int_vector.hpp>
#include <math.h>
#include <list>
#include <string>
#include <sdsl/int_vector.hpp>
#include <sdsl/bit_vectors.hpp>

using namespace std;
using namespace sdsl;

class select_support {
public:

    bit_vector *bv;

    select_support(bit_vector *bit) {
        bv = bit;
    }

    uint64_t select1(uint64_t i) {

        // ran out of time as didn't finish implementation of rank1
        // but would recursively call rank1 to compute select1

    }

    uint64_t select0(uint64_t i) {


    }

    uint64_t  overhead() {


    }

    void save(string& fname) {

    }

    void load(string& fname) {

    }
};


#endif //SELECT_METHOD_SELECT_SUPPORT_H
