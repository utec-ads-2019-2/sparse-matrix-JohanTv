#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H

#include <stdexcept>
#include <vector>
#include "node.h"
using namespace std;

template <typename T>
class Matrix {
private:
    vector<NodeHeader<T>*>* rootX;
    vector<NodeHeader<T>*>* rootY;

    unsigned int rows, columns;

    bool emptyHeaderInY(unsigned int posY){
        return !((*rootY)[posY]->next);
    }
    bool emptyHeaderInX(unsigned int posX){
        return !((*rootX)[posX]->next);
    }

    void setRootY(unsigned int posX, unsigned int posY, NodeElement<T>* newNode){
        if(emptyHeaderInY(posY)){
            (*rootY)[posY]->next = newNode;
        }
        else{
            //pass
        }
    }
    void setRootX(unsigned int posX, unsigned int posY, NodeElement<T>* newNode){
        if(emptyHeaderInX(posX)){
            (*rootX)[posX]->next = newNode;
        }
        else{
            //pass
        }
    }

    bool findInMatrix(unsigned int posX, unsigned int posY, T data, NodeElement<T>**& pointer){
        while((*pointer)->next){

        }
        return false;
    }
public:
    Matrix(unsigned int rows, unsigned int columns):rows(rows),columns(columns){

        rootX = new vector<NodeHeader<T>*>(columns);
        rootY = new vector<NodeHeader<T>*>(rows);

        for(int i = 0; i < columns; ++i)
            (*rootX)[i] = new NodeHeader<T>();

        for(int i = 0; i < rows; ++i)
            (*rootY)[i] = new NodeHeader<T>();
    }

    bool set(unsigned int posX, unsigned int posY, T data){
        if(columns > posX && rows > posY){
            NodeElement<T>* newNode = new NodeElement<T>(posX,posY,data);
            setRootY(posX,posY,newNode);
            setRootX(posX,posY,newNode);
            return true;
        }
        return false;
    }
    /*
    T operator()(unsigned, unsigned) const;
    Matrix<T> operator*(T scalar) const;
    Matrix<T> operator*(Matrix<T> other) const;
    Matrix<T> operator+(Matrix<T> other) const;
    Matrix<T> operator-(Matrix<T> other) const;
    Matrix<T> transpose() const;*/

    void print() const{
        NodeElement<T>* temp = nullptr;
        int aux = 0;
        for(auto it = rootY->cbegin(); it != rootY->cend(); ++it){
            temp = (*it)->next;

            while(temp){
                while (aux++ < temp->posX)
                    cout << "0 ";
                cout << temp->data << " ";
                temp = temp->next;
            }

            while (aux++ < columns)
                    cout << "0 ";

            aux = 0;
            putchar('\n');
        }
    }

    //void setRows(unsigned int rows){ Matrix::rows = rows; }
    //void setcolumns(unsigned int columns){ Matrix::columns = columns; }

    unsigned int getRows() const { return rows; }
    unsigned int getColumns() const { return columns; }

    ~Matrix(){

    }
};

#endif //SPARSE_MATRIX_MATRIX_H