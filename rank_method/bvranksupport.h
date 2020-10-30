//
// Created by Madan, Sanna (NIH/NCI) [F] on 10/27/20.
//
#ifndef INC_858D_BVRANKSUPPORT_H
#define INC_858D_BVRANKSUPPORT_H
#include <cstdint>
#include <string>
#include <sdsl/bit_vectors.hpp>
#include <sdsl/int_vector.hpp>
#include <math.h>
#include <list>

using namespace std;
using namespace sdsl;

class bvranksupport {
public:

    sdsl::bit_vector *bv;
    uint64_t  block_count{0};
    uint64_t  superblock_count{0};


    bvranksupport (sdsl::bit_vector *bit) {
        bv = bit;

        bit_vector bv_tmp = *bv;
        uint64_t n = bv_tmp.size();
        uint64_t superblock_size = pow(log(n),2) / 2;
        uint64_t superblock_count = n / superblock_size;
        uint64_t block_size = log(n)/2;
        uint64_t block_count = n / block_size;

        sdsl::int_vector<64> R_superblocks(n/superblock_size);
        sdsl::int_vector<64> R_blocks;
        sdsl::int_vector<64> R_p;

        for (int j = 0; j < n/superblock_size; j++) {
            if (j == 0) {
                R_superblocks[j] = 0;
            }
            else {
                int count = 0;
                for (int k = (j-1) * superblock_size; k < (j) * superblock_size; k++) {
                    if (bv_tmp[k] == 1) {
                        count += 1;
                    }
                }
                R_superblocks[j] = count + R_superblocks[j-1];
            }
        }


        /* commented out due to errors
        int count = 0;
        R_blocks[0] = 0;
        int block_flag = 0;
        for (int ix = 0; ix < n; ix++) {
            count = count + bv_tmp[ix];
            if (ix % block_size == 0) {
                R_blocks[ix/block_size] = count;
            }
            if (ix % superblock_size == 0) {
                R_blocks[ix/block_size] = 0;
                count = 0;
            }
        }
         */
        cout << superblock_size << endl;
    }

    uint64_t rank1 (uint64_t i) {

        // would first calculate the superblock 'i' falls in, and add it to rank value.
        // would then find the relative rank of i in the R_blocks table and add it to rank value.
        // would then use lookup table to find what type of sub-block i falls in and add it to rank value.
        // would return the final rank value.

    }

    uint64_t rank0(uint64_t i) {

        // would return i - rank1(i)

    }

    uint64_t overhead() {
        // would return the sum of Rs, Rb, and Rp in bits
    }

    void save(string& fname) {
        // would save the Rs, Rb, and Rp tables along with bitvector in a file
    }

    void load(string& fname) {
        // would load the bitvector from a file, and Rs, Rb, Rp
    }



};


#endif //INC_858D_BVRANKSUPPORT_H
