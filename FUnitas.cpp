#include "FUnitas.hpp"

using namespace funitas;
using namespace std;

float convert_to_double(int ab, fuint i) {
    return ((float)ab) + 0.5f;
}

int main() {
    
    /*
     * This space is for integration tests - 
     * all code should be unit-tested prior to 
     * being integration tested.
     */
    
    FInts x = {3, 2, 1};
    x.print_structure();

    FFloats y = x.for_each(convert_to_double);
    y.print_structure();

    while (1) {}
}