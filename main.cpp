#include <iostream>

//#include "tester/tester.h"
#include "matrix.h"
int main() {
    //Tester::execute();
    Matrix<int> miMatriz(3,3);
    int cont = 0;
    for (int i = 0; i < miMatriz.getRows(); ++i) {
        for (int j = 0; j < miMatriz.getColumns(); ++j) {
            miMatriz.set(i,j,2*cont+1);
            ++cont;
        }
    }

    Matrix<int> matrixScalar = miMatriz*2;

    miMatriz.print();
    cout<<"\n\n";
    matrixScalar.print();

    return EXIT_SUCCESS;
}

