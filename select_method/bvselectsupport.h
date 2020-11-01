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
#include "../rank_method/bvranksupport.h"


using namespace std;
using namespace sdsl;

class bvselectsupport {
public:

    sdsl::bit_vector bv;

    bvselectsupport(bit_vector *bit) {
        bv = *bit;
    }

    uint64_t select1(uint64_t i) {
        bvranksupport r(&bv);
        int n = bv.size();
        for (int x = n; x >= 0; x--) {
            if (r.rank1(x) == i) {
                return x;
            }
        }
    }

    uint64_t select0(uint64_t i) {
        bvranksupport r(&bv);
        int n = bv.size();
        for (int x = n; x >= 0; x--) {
            if (r.rank0(x) == i) {
                return x;
            }
        }
    }

    uint64_t  overhead() {
        bvranksupport r(&bv);
        return r.overhead();
    }

    void save(string& fname) {

    }

    void load(string& fname) {

    }
};


#endif //SELECT_METHOD_SELECT_SUPPORT_H
