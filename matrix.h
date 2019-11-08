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

    void setRootX(unsigned int posX, unsigned int posY, NodeElement<T>* newNode){
        NodeElement<T>** findInX = &((*rootX)[posX]->next);
        if(!findInHeaderX(posX,posY,newNode->data,findInX)){
            NodeElement<T>* temp = (*findInX);
            (*findInX) = newNode;
            newNode->down = temp;
        }
    }

    bool findInHeaderY(unsigned int posX, unsigned int posY, T data, NodeElement<T>**& pointer){
        while((*pointer) && (*pointer)->posX <= posX){
            if((*pointer)->posX == posX) return true;
            pointer = &((*pointer)->next);
        }
        return false;
    }

    bool findInHeaderX(unsigned int posX, unsigned int posY, T data, NodeElement<T>**& pointer){
        while((*pointer) && (*pointer)->posY <= posY){
            if((*pointer)->posY == posY) return true;
            pointer = &((*pointer)->down);
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
            NodeElement<T>** findInY = &((*rootY)[posY]->next);

            if(findInHeaderY(posX,posY,data,findInY)) {
                if(data != 0) (*findInY)->data = data;
                else{
                    NodeElement<T>** findInX = &((*rootX)[posX]->next);
                    findInHeaderX(posX,posY,data,findInX);

                    NodeElement<T>* tempY = (*findInY)->next;
                    NodeElement<T>* tempX = (*findInX)->down;

                    delete (*findInX);

                    (*findInX) = tempX;
                    (*findInY) = tempY;
                }
            }

            else{
                if(data != 0) {
                    NodeElement<T> *newNode = new NodeElement<T>(posX, posY, data);
                    NodeElement<T> *temp = (*findInY);
                    (*findInY) = newNode;
                    newNode->next = temp;
                    setRootX(posX, posY, newNode);
                }
            }
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