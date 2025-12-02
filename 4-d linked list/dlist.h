//
//  list.h
//  lista_doblemente_ligada
//
//  Created by Isabel Vaca on 30/09/25.
//

// Incluye estas funciones en tu dlist.h para poder imprimir tus respuestas
// en formatos compatibles con el main

using namespace std;
template <class T> class DList;
template <class T> class DLink;


template <class T>
//Elemento
class DLink{
private:
    //Crea elemento
    
    DLink(T val);
    //Crea elemento y su apuntador
    DLink(T val, DLink<T>*, DLink<T>*);
    //Crea copia
    DLink(const DLink<T>&);
    
    //elemento tipo T
    T value;
    //Apuntador tipo Link
    DLink<T> *next;
    
    DLink<T> *previous;
    
    //esta clase puede acceder a atributos privados de Link
    friend class DList<T>;

    
};

template <class T>
DLink<T>::DLink(T val)
: value(val), previous(0), next(0){}

template <class T>
DLink<T>::DLink(T val,DLink<T>* prev, DLink<T>* nxt)
: value(val), previous(prev), next(nxt){}

template <class T>
DLink<T>::DLink(const DLink<T>&source)
: value(source.value), previous(source.previous), next(source.next)
{}


//clase list
template <class T>
class DList{
private:
    //atributos privados
    DLink<T> *head;
    DLink<T> *tail;
    int size;
public:
    //constructores
    DList();
    DList(const DList<T>& );
    //destructor
    ~DList();
    
    //metodos
    void insertion(T val);
    int search( T val) const;
    void update(int pos, T val);
    T deleteAt(int pos);
    
    void clear();
    string toString() const;
    string toStringForward() const;
    string toStringBackward() const;
    
};
//constructores
template <class T>
DList<T>::DList()
: size(0), head(0), tail(0){}

template <class T>
DList<T>::~DList()
 {
    clear();
}

//metodo insertion que ingresa valor
template <class T>
void DList<T>::insertion(T val){
    
    //puntero del nuevo elemento
    DLink<T> *newDLink;
    //se crea
    newDLink = new DLink<T>(val);
    newDLink -> previous = 0;
    newDLink -> next = 0;
    //en caso de que este vacia
    if(head == 0){
        head =  newDLink;
        tail = newDLink;
        size ++;
        return;
    }
    
    //al final
    newDLink -> previous = tail;
    tail -> next = newDLink;
    tail = newDLink;
    size++;
        
    }
    
    
//busca el valor y regresa su indice
template <class T>
int DList<T>::search(T val) const{
    //puntero
    DLink<T> *ptr;
    ptr = head;
    //itera hasta que encuentre val o ptr apunte a null
    for(int i =0; ptr !=0; i++){
        //compara valor actual con val
        if( ptr-> value == val){
            //regresa indice
            return i;
        }
        ptr = ptr -> next;
    }
    //si no se encontró
    return -1;
    
}

//cambia el valor en la posicion ingresada
template <class T>
void DList<T>::update(int pos, T val){
    //puntero
    DLink<T> *ptr;
    ptr = head;
    
    //itera hasta llegar a la posicion
    for(int i =0; i<pos; i++){
        ptr = ptr -> next;
    }
    //cambia el valor
    ptr -> value = val;
    
    
}

//elimina el valor en la posicion asignada
template <class T>
T DList<T>::deleteAt(int pos){
    DLink<T> *ptr;
    ptr = head;
    DLink<T> *borrar;
    T elimVal;
    if(pos == 0){
        borrar = head ;
        elimVal = borrar -> value;
        head = head -> next;
        head -> previous = 0;
        delete borrar;
        size --;
        return elimVal;
        
    }
    for(int i =0; i<pos-1; i++){
        ptr = ptr->next;
    }

    borrar = ptr -> next;
    elimVal = borrar -> value;
    ptr -> next = borrar -> next ;
    if(borrar -> next != 0){
        borrar -> next -> previous =  ptr;
        
    }
    
    delete borrar;
    size --;
    return elimVal;
    
    
}

//metodo to string
template <class T>
string DList<T>::toString() const {
    stringstream aux;
    DLink<T> *p;

    p = head;
    aux << "[";
    while (p != 0) {
        aux << p->value;
        if (p->next != 0) {
            aux << ", ";
        }
        p = p->next;
    }
    aux << "]";
    return aux.str();
}


//para el destructor
template <class T>
void DList<T>::clear() {
    DLink<T> *p, *q;

    p = head;
    while (p != 0) {
        q = p->next;
        delete p;
        p = q;
    }
    head = 0;
    size = 0;
}
template <class T>
DList<T>::DList(const DList<T> &source){
    DLink<T> *p, *q;

    if (source.empty()) {
        size = 0;
        head = 0;
        tail = 0;
    } else {
        p = source.head;
        head = new DLink<T>(p->value);
        
        q = head;

        p = p->next;
        while(p != 0) {
            q->next = new DLink<T>(p->value, q, 0);
            
            p = p->next;
            q = q->next;
        }
        size = source.size;
    }
}




template <class T>
string DList<T>::toStringForward() const {
    stringstream aux;
    DLink<T> *p;

    p = head;
    aux << "[";
    while (p != 0) {
        aux << p->value;
        if (p->next != 0) {
            aux << ", ";
        }
        p = p->next;
    }
    aux << "]";
    return aux.str();
}

template <class T>
string DList<T>::toStringBackward() const {
    stringstream aux;
    DLink<T> *p;

    p = tail;
    aux << "[";
    while (p != 0) {
        aux << p->value;
        if (p->previous != 0) {
            aux << ", ";
        }
        p = p->previous;
    }
    aux << "]";
    return aux.str();
}
