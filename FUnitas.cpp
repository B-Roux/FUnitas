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

        FInts x = { 3, 2, 1, 5, 4, 3, 2, 1, 0 };
        x.print_structure();

        x.append(0);
        x.print_structure();

        x.defragment();
        x.print_structure();

        x.append(x);
        x.print_structure();

        x.defragment();
        x.print_structure();

        x.defragment();
        x.print_structure();
    }

    while (1) {}
}