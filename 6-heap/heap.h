//
//  heap.h
//  HeapTarea
//
//  Created by Isabel Vaca on 29/10/25.
//

#ifndef HEAP_H_
#define HEAP_H_

#include <string>
#include <sstream>
#include <iostream>

template <class T>
class Heap {
private:
    T *data;
    unsigned int capacity;
    unsigned int count;
    unsigned int parent(unsigned int) const;
    unsigned int left(unsigned int) const;
    unsigned int right(unsigned int) const;
    void heapify(unsigned int);
    void swap(unsigned int, unsigned int);

public:
    Heap(unsigned int) ;
    ~Heap();
    bool empty() const;
    void  push(T) ;
    T pop() ;
    T top() const;
    void clear();
    std::string toString() const;
    int size();
};

template <class T>
Heap<T>::Heap(unsigned int sze)  {
    capacity = sze;
    data = new T[capacity +1]; //empieza de 1 y no de 0
    count = 0;
}

template <class T>
Heap<T>::~Heap() {
    delete [] data;
    data = 0;
    capacity = 0;
    count = 0;
}


template <class T>
bool Heap<T>::empty() const {
    return (count == 0);
}

template <class T>
unsigned int Heap<T>::parent(unsigned int pos) const {
    return pos  / 2; // empieza de 1, mas sncillo
}

template <class T>
unsigned int Heap<T>::left(unsigned int pos) const {
    return 2 * pos ;
}

template <class T>
unsigned int Heap<T>::right(unsigned int pos) const {
    return ((2 * pos) + 1);
}

template <class T>
void Heap<T>::swap(unsigned int i, unsigned int j) {
    T aux = data[i];
    data[i] = data[j];
    data[j] = aux;
}
template <class T>
void Heap<T>::heapify(unsigned int pos) {
    unsigned int le = left(pos);
    unsigned int ri = right(pos);
    unsigned int min = pos;
    if (le <= count && data[le] < data[min]) {
        min = le;
    }
    if (ri <= count && data[ri] < data[min]) {
        min = ri;
    }
    if (min != pos) {
        swap(pos, min);
        heapify(min);
    }
}



template <class T>
T Heap<T>::pop()  {
    T aux = data[1];

    data[1] = data[count];
    count --;
    heapify(1);
    return aux;
}

template <class T>
void Heap<T>::clear() {
    count = 0;
}

template <class T>
std::string Heap<T>::toString() const {
    std::stringstream aux;
    aux << "[";    for (unsigned int i = 1; i <= count; i++) {
        if (i != 1) {
            aux << " ";
        } aux << data[i];
    } aux << "]";
    return aux.str();
}

template <class T>
void Heap<T>::push(T val){
    unsigned int pos;
    count++;
    pos = count;
    while (pos > 1 && val < data[parent(pos)]) {
        data[pos] = data[parent(pos)];
        pos = parent(pos);
    }
    data[pos] = val;
}

template <class T>
T Heap<T>::top() const{
    
    return data[1];
    
}
template <class T>
int Heap<T>::size() {
    return count;
    
}

#endif /* HASH_H_ */
