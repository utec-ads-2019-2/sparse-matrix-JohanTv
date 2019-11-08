#ifndef SPARSE_MATRIX_NODE_H
#define SPARSE_MATRIX_NODE_H

template <typename T>
class Matrix;

template <typename T>
struct NodeElement{
    NodeElement<T> *next, *down;
    int posX;
    int posY;
    T data;

    explicit NodeElement(): next(nullptr), down(nullptr){};
    explicit NodeElement(int posX, int posY, T data):posX(posX),posY(posY),data(data){
        next = nullptr;
        down = nullptr;
    };
    friend class Matrix<T>;
};

template <typename T>
struct NodeHeader{
    NodeElement<T>* next;
    explicit NodeHeader(){
        next = nullptr;
    }

    T operator[](unsigned int posX){
        NodeElement<T>* temp = next;
        while(temp != nullptr && temp->posX <= posX){
            if(temp->posX == posX) return temp->data;
            temp = temp->next;
        }
        return 0;
    }

};
#endif //SPARSE_MATRIX_NODE_H
