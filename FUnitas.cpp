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

        FInts x = { 3 };
        x.print_structure();

        x[FRange(0, 1000, -50)].print_structure();
    }

    while (1) {}
}