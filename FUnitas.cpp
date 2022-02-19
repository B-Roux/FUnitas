#include "FUnitas.hpp"

using namespace funitas;
using namespace std;

int main() {
    
    /*
     * This space is for integration tests - 
     * all code should be unit-tested prior to 
     * being integration tested.
     */

    FInts x = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    FInts y = { 1, 2, 2, 4, 5, 6, 7, 8, 9, 10, 11 };
    FBools z = y <= x;

    cout << z << endl;

    if (z) {
        cout << "true" << endl;
    }
    else {
        cout << "false" << endl;
    }

    while (1) {}
}