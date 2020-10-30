#include <iostream>
#include <sdsl/int_vector.hpp>
#include <sdsl/bit_vectors.hpp>
#include "bvranksupport.h"

using namespace std;
using namespace sdsl;
#include <chrono>
using namespace std::chrono;

// Use auto keyword to avoid typing long
// type definitions to get the timepoint
// at this instant use function now()


int main() {

/*    std::cout << "Hello, World!" << std::endl;
    return 0;*/
    // failed SDSL test
    //bit_vector b = {1,0,0,1,0,0,0,1,1,0,0,1,0,0,0,1};
    //bit_vector b = {1,1,1,1,1,1,1,1};
    bit_vector b = {1,0,1,0};
    bvranksupport r(&b);

    // CITATION for timer: https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
    auto start = high_resolution_clock::now();
    auto x = r.rank1(1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << duration.count() << endl;

    auto y = r.overhead();
    cout << "RANK1: " << x << endl;
    cout << "overhead: " << y << endl;


}
