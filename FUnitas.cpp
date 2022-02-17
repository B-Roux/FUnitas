#include "FUnitas.hpp"

using namespace funitas;
using namespace std;

int main() {
    
    /*
     * This space is for integration tests - 
     * all code should be unit-tested prior to 
     * being integration tested.
     */
    
    FInts x = {3, 2, 1};
    x.print_structure();

    cout << x[FRange(1,100)] << endl;

    while (1) {}
}