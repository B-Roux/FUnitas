#include "FUnitas.h"

int my_map_fn(int x) {
    return x*2;
}

int main() {
    
    //Basically, run bug tests here
    
    unitas::FInts x = {1, 2, 3, 4, 5};

    std::cout << x << std::endl;

    x.map(my_map_fn);

    std::cout << x << std::endl;
}