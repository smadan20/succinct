//
// Created by Madan, Sanna (NIH/NCI) [F] on 10/27/20.
//
#ifndef INC_858D_BVRANKSUPPORT_H
#define INC_858D_BVRANKSUPPORT_H
#include <cstdint>
#include <string>
#include <sdsl/bit_vectors.hpp>
#include <sdsl/int_vector.hpp>
#include <bitset>
#include <vector>
#include <math.h>
#include <list>
#include <sstream>
#include <numeric>
#include <fstream>

using namespace std;
using namespace sdsl;

class bvranksupport {
public:

    sdsl::bit_vector bv;
    uint64_t  block_count{0};
    uint64_t  superblock_count{0};
    int_vector<64> R_superblocks;
    int_vector<64> R_blocks;
    const char *R_lookup;

    bvranksupport (sdsl::bit_vector *bit) {
        bv = *bit;
    }

    uint64_t rank1 (uint64_t i) {

        bit_vector bv_tmp = bv;
        uint64_t n = bv_tmp.size();
        uint64_t superblock_size = pow(log2(n),2) / 2;
        superblock_count = n / superblock_size;
        uint64_t block_size = log2(n)/2;
        block_count = n / block_size;
        R_superblocks.resize(superblock_count);
        R_blocks.resize(block_count);

        // Rs table (superblocks)
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

        // Rb table (blocks)
        int count = 0;
        //int block_flag = 0;
        for (int ix = 0; ix < n; ix++) {
            if (ix % block_size == 0) {
                R_blocks[ix/block_size] = count;
            }
            if (ix % superblock_size == 0) {
                R_blocks[ix/block_size] = 0;
                count = 0;
            }
            count = count + bv_tmp[ix];
        }

        // Rp table (lookup table)
        // lookup table will have b = logn/2 columns and 2^b rows

        vector<string> tmp_str_vec;
        tmp_str_vec = generateGrayarr(block_size);
        vector<vector<int>> x_bit_vecs;

        // convert bit strings to int VECTORS, to create map
        for (int x = 0; x < tmp_str_vec.size(); x ++) {
            string tmp = tmp_str_vec[x];
            vector<int> my_vec;
            // CITATION: https://stackoverflow.com/questions/40985484/convert-string-to-a-vector-of-integers
            for (int y = 0; y < tmp.length(); y ++) {
                my_vec.push_back(tmp[y]-'0');
            }
            x_bit_vecs.push_back(my_vec);
        }

        for (int x = 0; x < x_bit_vecs.size(); x ++) {
            // cout << x_bit_vecs[x] << endl;
            vector<int> curr_vec = x_bit_vecs[x];
            R_lookup[curr_vec] = accumulate(curr_vec.begin(), curr_vec.end(), 0);
            //cout << curr_vec << endl;
            //cout << R_lookup[curr_vec] << endl;
        }


        // FINAL COMPUTATION OF RANK1:
        uint64_t rank1 = 0;

        //  first calculate the superblock 'i' falls in, and add it to rank value.
        int which_superblock = floor(i/superblock_size);
        rank1 += R_superblocks[which_superblock];
        //cout << "SUPERBLOCK VALUE: " << rank1 << endl;
        // then find the relative rank of i in the R_blocks table and add it to rank value.
        int which_block = floor(i/block_size);
        rank1 += R_blocks[which_block];
        //cout << "BLOCK VALUE: " << R_blocks[which_block] << endl;
        // then use lookup table to find what type of sub-block i falls in and add it to rank value.
        // would return the final rank value.
        int start_index = block_size * which_block; // find where in bit vector we start lookup
        vector<int> lookup_vec;
        for (int x = start_index; x < start_index + block_size; x ++) {
            lookup_vec.push_back(bv_tmp[x]);
        }
        //cout << "LOOKUP TABLE RESULT: " << R_lookup[lookup_vec] << endl;
        //cout << "LOOKUP QUERY: " << lookup_vec << endl;
        rank1 += R_lookup[lookup_vec];
        return rank1;
    }

    uint64_t rank0(uint64_t i) {
        return i - rank1(i);
    }

    uint64_t overhead() {
        return (sizeof(R_superblocks) + sizeof(R_blocks) + sizeof(R_lookup)) * 8;
    }

    void save(string& fname) {
        ofstream writeFile;
        writeFile.open(fname, ios::out | ios::binary);
        writeFile.write(reinterpret_cast<const char *>(R_superblocks.data()), R_superblocks.size() * sizeof(int64_t));
        writeFile.write(reinterpret_cast<const char *>(R_blocks.data()), R_blocks.size() * sizeof(int64_t));
        writeFile.write(R_lookup, R_lookup.size() * sizeof(vector<int>));
        //bv.save(fname="bitvector");

        // would save the Rs, Rb, and Rp tables along with bitvector in a file
    }

    void load(string& fname) {
        // would load the bitvector from a file, and Rs, Rb, Rp
    }

    // helper function to generate Gray Codes (all n-bit strings)
    // CITATION: https://www.geeksforgeeks.org/generate-n-bit-gray-codes/
    vector<string> generateGrayarr(int z)
    {

        // 'arr' will store all generated codes
        vector<string> arr;

        // start with one-bit pattern
        arr.push_back("0");
        arr.push_back("1");

        // Every iteration of this loop generates 2*i codes from previously
        // generated i codes.
        int i, j;
        for (i = 2; i < (1<<z); i = i<<1)
        {
            // Enter the prviously generated codes again in arr[] in reverse
            // order. Nor arr[] has double number of codes.
            for (j = i-1 ; j >= 0 ; j--)
                arr.push_back(arr[j]);

            // append 0 to the first half
            for (j = 0 ; j < i ; j++)
                arr[j] = "0" + arr[j];

            // append 1 to the second half
            for (j = i ; j < 2*i ; j++)
                arr[j] = "1" + arr[j];
        }

        // print contents of arr[]
        //for (i = 0 ; i < arr.size() ; i++ )
        //cout << arr[i] << endl;

        return arr;
    }


};


#endif //INC_858D_BVRANKSUPPORT_H
