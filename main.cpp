#include <iostream>

//#include "tester/tester.h"
#include "matrix.h"
int main() {
    //Tester::execute();
    Matrix<int> miMatriz(3,3);
    int cont = 1;
    for (int i = 0; i < miMatriz.getRows(); ++i) {
        for (int j = 0; j < miMatriz.getColumns(); ++j) {
            miMatriz.set(j,i,0);
            ++cont;
        }
    }
    miMatriz.print();

    cout<<"\n\n\n";
    for (int i = 0; i < miMatriz.getRows(); ++i) {
        for (int j = 0; j < miMatriz.getColumns(); ++j) {
            miMatriz.set(j,i,0);
            ++cont;
        }
    }

    miMatriz.print();
    return EXIT_SUCCESS;
}

