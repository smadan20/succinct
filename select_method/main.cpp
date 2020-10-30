#include <iostream>
#include <sdsl/int_vector.hpp>
#include <sdsl/bit_vectors.hpp>
#include "../rank_method/bvranksupport.h"

using namespace std;
using namespace sdsl;

int main() {
/*    std::cout << "Hello, World!" << std::endl;
    return 0;*/
    // failed SDSL test
    bit_vector b = {1,0,0,1,0,0,0,1};
    select_support r(&b);
    auto x = r.rank1(2);
    //cout << x << endl;


}