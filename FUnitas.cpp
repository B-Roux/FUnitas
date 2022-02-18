#include "FUnitas.hpp"

using namespace funitas;

int main() {
    
    /*
     * This space is for integration tests - 
     * all code should be unit-tested prior to 
     * being integration tested.
     */
    {
        FInts x = { 3, 2, 1, 5, 4, 3, 2, 1, 0 };
        FInts y = { 4, 2, 2, 5, 5, 3, 3, 1, 1 };

        auto z = x<y;

        z.print_structure();
    }

    while (1) {}
}