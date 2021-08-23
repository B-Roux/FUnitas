#include "FUnitas.hpp"

using namespace uni;
using namespace std;

int dti(int x, fuint i) {
    cout << i << ": " << x << endl;
    return 0;
}

int main() {
    
    //Basically, run bug tests here
    
    FInts x {1, 2, 3};

    x.append(1);
    x.append(1);
    x.append(1);
    x.append(1);
    x.append(1);

    x.print_structure();

    x.for_each([](int rec, fuint idx)->int{
        cout << idx << ": " << rec << endl; 
        return 0;
    });

}