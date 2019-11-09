#include <iostream>
#include <ctime>
//#include "tester/tester.h"
#include "matrix.h"
int main() {
    //Tester::execute();
    Matrix<int> impares(5,5);
    int cont = 0;
    for (int i = 0; i < impares.getRows(); ++i) {
        for (int j = 0; j < impares.getColumns(); ++j) {
            impares.set(i,j,2*cont+1);
            ++cont;
        }
    }

    Matrix<int> pares(5,5);
    cont = 0;
    for (int i = 0; i < pares.getRows(); ++i) {
        for (int j = 0; j < pares.getColumns(); ++j) {
            pares.set(i,j,2*cont);
            ++cont;
        }
    }

    Matrix<int> sum = pares + impares;
    sum.print();
    cout<<endl;

    sum = pares;
    sum.print();
    cout<<endl;
    
    return 0;
}

