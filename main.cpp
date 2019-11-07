#include <iostream>

//#include "tester/tester.h"
#include "matrix.h"
int main() {
    //Tester::execute();
    Matrix<int> miMatriz(10,10);
    miMatriz.print();
    miMatriz.set(4,0,1);
    miMatriz.set(3,1,12);
    miMatriz.set(5,2,25);
    miMatriz.set(7,6,34);
    miMatriz.set(9,8,17);
    miMatriz.set(11,11,999);
    cout<<"\n\n\n";
    miMatriz.print();
    return EXIT_SUCCESS;
}

