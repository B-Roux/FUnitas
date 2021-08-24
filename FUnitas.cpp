#include "FUnitas.hpp"

using namespace uni;
using namespace std;

    int dti(int x, fuint i) {
        cout << i << ": " << x << endl;
        return 0;
    }

int main() {
    
    //Basically, run bug tests here
    
    FInts x {3, 2, 1};

    x.append(4);
    x.append(5);
    x.append(6);

    FList<FInts> matrix = { x, x, x };

    matrix[0].append(7);
    matrix[1].append(7);
    matrix[2].append(7);


    matrix.append(FInts({20, 20, 20}));

    matrix.print_structure();
    matrix[2].print_structure();

    matrix.defragment();

    matrix.print_structure();
    matrix[2].print_structure();
}