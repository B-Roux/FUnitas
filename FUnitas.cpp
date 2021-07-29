#include "FUnitas.h"
#include <iostream>

int main() {
    
    //Basically, run bug tests here
    
    auto x = ftd::FList<int>();
    x.append(1);
    x.append(2);
    x.append(3);
    x.append(4);
    x.append(5);

    int y = x[2];

    std::cout << x << std::endl;
    std::cout << y << std::endl;
    y = 70;
    std::cout << x << std::endl;
    std::cout << y << std::endl;
}