#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H

#include <stdexcept>
#include <vector>
#include <iomanip>
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
        findInHeaderX(posY,findInX); //return false

        NodeElement<T>* temp = (*findInX);
        (*findInX) = newNode;
        newNode->down = temp;
    }

    bool findInHeaderY(unsigned int posX, NodeElement<T>**& pointer){
        while((*pointer) && (*pointer)->posX <= posX){
            if((*pointer)->posX == posX) return true;
            pointer = &((*pointer)->next);
        }
        return false;
    }

    bool findInHeaderX(unsigned int posY, NodeElement<T>**& pointer){
        while((*pointer) && (*pointer)->posY <= posY){
            if((*pointer)->posY == posY) return true;
            pointer = &((*pointer)->down);
        }
        return false;
    }

    void deleteElements(){
        NodeElement<T>** findInY= nullptr;
        NodeElement<T>** findInX = nullptr;

        NodeElement<T>* tempY = nullptr;
        NodeElement<T>* tempX = nullptr;

        for (int i = 0; i < rows; ++i) {
            findInY = &((*rootY)[i]->next);
            while((*findInY)){
                findInX = &((*rootX)[(*findInY)->posX]->next);
                findInHeaderX((*findInY)->posY,findInX);

                tempY = (*findInY)->next;
                tempX = (*findInX)->down;

                delete (*findInX);

                (*findInX) = tempX;
                (*findInY) = tempY;
            }
        }
    }

    void deleteVectorsOfHeaders(){
        for (int i = 0; i < rows; ++i) {
            delete (*rootY)[i];
            (*rootY)[i] = nullptr;
        }
        for (int i = 0; i < columns; ++i) {
            delete (*rootX)[i];
            (*rootX)[i] = nullptr;
        }

        (*rootY).clear();
        (*rootX).clear();

        delete rootY;
        delete rootX;

        rootY=nullptr;
        rootX= nullptr;
    }

    void newVectorsOfHeaders(){
        rootX = new vector<NodeHeader<T>*>(columns);
        rootY = new vector<NodeHeader<T>*>(rows);

        for(int i = 0; i < columns; ++i)
            (*rootX)[i] = new NodeHeader<T>();

        for(int i = 0; i < rows; ++i)
            (*rootY)[i] = new NodeHeader<T>();
    }

    void CopyElementsOfOtherMatrix(const Matrix<T>& matrixCopy){
        NodeElement<T>* temp = nullptr;
        for(int i = 0; i < rows; ++i){
            temp = matrixCopy[i].next;
            while (temp) {
                this->set(temp->posY,temp->posX,temp->data);
                temp = temp->next;
            }
        }
    }

    void printMatrix(unsigned int width) const{
        int i,j;
        for (i = 0; i < rows; ++i) {
            for (j = 0; j < columns - 1; ++j) {
                cout<<setw(width)<<(*this)[i][j]<<" ";
            }
            cout<<setw(width)<<(*this)[i][j]<<endl;
        }
    }

public:
    Matrix():rows(0),columns(0){
        newVectorsOfHeaders();
    }

    Matrix(unsigned int rows, unsigned int columns):rows(rows),columns(columns){
        newVectorsOfHeaders();
    }

    Matrix(const Matrix<T>& constructCopy):rows(constructCopy.getRows()),columns(constructCopy.getColumns()){
        newVectorsOfHeaders();
        CopyElementsOfOtherMatrix(constructCopy);
    }

    void set(unsigned int posY, unsigned int posX, T data){
        if( (0<=posX && posX < columns) && (0<=posY && posY < rows) ){
            NodeElement<T>** findInY = &((*rootY)[posY]->next);

            if(findInHeaderY(posX,findInY)) {
                if(data != 0) (*findInY)->data = data;
                else{
                    NodeElement<T>** findInX = &((*rootX)[posX]->next);
                    findInHeaderX(posY,findInX);

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
        }
        else throw new out_of_range("No es posible");
    }

    Matrix<T> operator=(const Matrix<T>& other){
        if(this != &other) {
            deleteElements();
            deleteVectorsOfHeaders();

            this->rows = other.getRows();
            this->columns = other.getColumns();

            newVectorsOfHeaders();
            CopyElementsOfOtherMatrix(other);
        }
        return *this;
    }

    T operator()(unsigned int posY, unsigned int posX){
        NodeElement<T>** findInY = &((*rootY)[posY]->next);
        if(findInHeaderY(posX,findInY))
            return (*findInY)->data;
        return 0;
    }

    NodeHeader<T> operator[](unsigned int posY) const{
        return *((*rootY)[posY]);
    }
    bool operator!=(Matrix<T>& other){
        if(this->rows == other.getRows() && this->columns == other.getColumns()){
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < columns; ++j) {
                    if((*this)[i][j] != other[i][j]) return true;
                }
            }
            return false;
        }
        return true;
    }
    bool operator==(Matrix<T>& other){
        if(this->rows == other.getRows() && this->columns == other.getColumns()){
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < columns; ++j) {
                    if((*this)[i][j] != other[i][j]) return false;
                }
            }
            return true;
        }
        return false;
    }
    Matrix<T> operator*(T scalar) const{
        Matrix<T> newMatrix = *this;

        NodeElement<T>* temp = nullptr;
        for (int i = 0; i < newMatrix.getRows(); ++i) {
            temp = newMatrix[i].next;
            while(temp){
                temp->data*= scalar;
                temp = temp->next;
            }
        }
        return newMatrix;
    }
    Matrix<T> operator*(Matrix<T>& other) const{
        if(this->columns != other.getRows()) throw new out_of_range("No son compatibles");
        else{
            Matrix<T> multiplicationMatrix(this->getRows(),other.getColumns());
            T result = 0;
            auto n = this->columns;
            for (int i = 0; i < multiplicationMatrix.getRows(); ++i) {
                for (int j = 0; j < multiplicationMatrix.getColumns(); ++j) {
                    for (int k = 0; k < n; ++k) {
                        result+=(*this)[i][k]*other[k][j];
                    }
                    multiplicationMatrix.set(i,j,result);
                    result = 0;
                }
            }
            return multiplicationMatrix;
        }
    }
    Matrix<T> operator+(Matrix<T>& other) const{

        if(this->rows != other.getRows()) throw new out_of_range("No son las mismas filas");
        else if(this->columns != other.getColumns()) throw new out_of_range("No son las mismas columnas");
        else{
            Matrix<T> sumMatrix(this->rows,this->columns);
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < columns; ++j) {
                    sumMatrix.set(i,j,(*this)[i][j] + other[i][j]);
                }
            }
            return sumMatrix;
        }
    }
    Matrix<T> operator-(Matrix<T>& other) const{
        if(this->rows != other.getRows()) throw new out_of_range("No son las mismas filas");
        else if(this->columns != other.getColumns()) throw new out_of_range("No son las mismas columnas");
        else{
            Matrix<T> sumMatrix(this->rows,this->columns);
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < columns; ++j) {
                    sumMatrix.set(i,j,(*this)[i][j] - other[i][j]);
                }
            }
            return sumMatrix;
        }
    }
    Matrix<T> transpose() const{
        Matrix<int> matrixTransporse(this->columns,this->rows);
        for (int i = 0; i < matrixTransporse.getRows(); ++i) {
            for (int j = 0; j < matrixTransporse.getColumns(); ++j) {
                matrixTransporse.set(i,j,(*this)[j][i]);
            }
        }
        return matrixTransporse;
    }

    void print() const{
        printMatrix(0);
    }

    void print(int width) const{
        if(width >= 0) printMatrix(width);
        else throw new invalid_argument("width invalid");
    }

    unsigned int getRows() const { return rows; }
    unsigned int getColumns() const { return columns; }

    ~Matrix(){
        deleteElements();
        deleteVectorsOfHeaders();
    }
};

#endif //SPARSE_MATRIX_MATRIX_H
