#include "FUnitas/FList.h"
#include <iostream>

int main() {
    
    //Basically, run bug tests here
    
    auto x = FList<int>();
    x.append(1);
    x.append(2);
    x.append(3);
    x.append(4);
    x.append(5);

    x.append(x);

    std::cout << x << std::endl;
}