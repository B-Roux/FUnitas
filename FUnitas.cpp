#include "FUnitas.hpp"

using namespace funitas;

int main() {
    
    /*
     * This space is for integration tests - 
     * all code should be unit-tested prior to 
     * being integration tested.
     */
    {
        //testing the defragmentation function

        FInts x = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

        x.print_structure();

        x[FRange(0, 7, 0)].print_structure();
    }

    while (1) {}
}