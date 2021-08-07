#include "FUnitas.h"

double my_map_fn(int x) {
    return ((double)x)/2;
}

int main() {
    
    //Basically, run bug tests here
    
    unitas::FInts x = {1, 2, 3, 4, 5};

    std::cout << x << std::endl;

    unitas::FDoubles y = x.mutate(my_map_fn);

    std::cout << y << std::endl;
}