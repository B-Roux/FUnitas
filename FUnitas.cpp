#include "FUnitas.h"

double my_map_fn(int x) {
    return ((double)x)/2;
}

int main() {
    
    //Basically, run bug tests here
    
    unitas::FInts x = {1, 2, 3};

    std::cout << x << std::endl;

    unitas::FDoubles y = x.mutate(my_map_fn);

    unitas::FDoubles z = y;

    z[2] = 400;

    std::cout << y << std::endl;

    std::cout << z << std::endl;
}