//
//  quadratic.h
//  hash_t
//
//  Created by Isabel Vaca on 26/11/25.
//

#ifndef HASH_H_
#define HASH_H_

#include <string>
#include <sstream>


template <class Key, class Value>
class Quadratic {
private:
    unsigned int (*func) (const Key);
    unsigned int size;
    unsigned int count;

    Key *keys;
    Key initialValue;
    Value *values;

    long indexOf(const Key) const;

public:
    Quadratic(unsigned int, Key, unsigned int (*f) (const Key)) ;
    ~Quadratic();
    bool full() const;
    void put(Key, Value);
    Value get(const Key) ;
    void clear();
    std::string toString() const;
};

template <class Key, class Value>
Quadratic<Key, Value>::Quadratic(unsigned int sze, Key init, unsigned int (*f) (const Key))  {
    size = sze;
    keys = new Key[size];
    
    initialValue = init;
    
    for(int i = 0; i<sze ; i++){
        keys[i] = init;
        
    }
    values = new Value[size];
    
    for(int i = 0;i<sze;i++){
        values[i] = 0;
    }
    
    func = f;
    
    count = 0;

}



template <class Key, class Value>
Quadratic<Key, Value>::~Quadratic() {
    delete [] keys;
    keys = 0;
    delete [] values;
    values = 0;
    size = 0;
    func = 0;
    count = 0;
    

}

template <class Key, class Value>
bool Quadratic<Key, Value>::full() const {
    if(count < size){
        return false;
    }
    else{
        return true;
    }
    
}

template <class Key, class Value>
long Quadratic<Key, Value>::indexOf(const Key k) const {
    unsigned int i, start;
    unsigned int j=1;
    start = i = func(k) % size;
    do {
            if (keys[i] == k) {
                return i;
            }
            else{
                i = (start + j*j) % size;//prueba cuadratica, ref hasta abajo
                j++;
            }
        } while (start != i);
        return -1;
   
}

template <class Key, class Value>
void Quadratic<Key, Value>::put(Key k, Value v) {
    unsigned int i, start;
    long long pos;
    unsigned int j=1;
    pos = indexOf(k);
    if(pos!=-1){
        values[pos] = v;//actualiza val;
        return;
    }
    start = i = func(k) % size;
    do {
        if(keys[i] == initialValue){
            values[i] = v;
            keys[i]= k;
            count++;
            return;
        }
        else{
            i = (start + j*j) %size;//prueba cuadratica
            j++;
        }
    }while(start!=i);
    return;
}


template <class Key, class Value>
Value Quadratic<Key, Value>::get(const Key k)  {
    long long pos;
    pos = indexOf(k);
    Value v;
    v = values[pos];

    return v;
}


template <class Key, class Value>
std::string Quadratic<Key, Value>::toString() const {
    std::stringstream aux;
    for (int i = 0; i < size; i++){
            if (keys[i] != initialValue){
                aux << "(" << i << " ";
              aux << keys[i] << " : " << values[i] << ") ";
            }
    }
    return aux.str();
}
#endif /* HASH_H_ */

//Referencia: https://www.geeksforgeeks.org/dsa/quadratic-probing-in-hashing/

