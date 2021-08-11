#include "FUnitas.h"

using namespace unitas;
using namespace std;

int dti(double x) {
    return (int)x;
}

int main() {
    
    //Basically, run bug tests here
    
    FInts x = {1, 2, 3};

    x.append(1);
    x.append(1);
    x.append(1);
    x.append(1);
    x.append(1);

    x.print_structure();

    x.defragment();

    x.print_structure();

}