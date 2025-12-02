//
//  list.h
//  lista_ligada_simple
//
//  Created by Isabel Vaca on 27/09/25.
//

#include <sstream>
#include <string>


using namespace std;
template <class T> class List;
template <class T> class Link;


template <class T>
//Elemento
class Link{
private:
    //Crea elemento
    Link(T val);
    //Crea elemento y su apuntador
    Link(T val, Link<T>*);
    //Crea copia
    Link(const Link<T>&);
    
    //elemento tipo T
    T value;
    //Apuntador tipo Link
    Link<T> *next;
    
    //esta clase puede acceder a atributos privados de Link
    friend class List<T>;
    
};

template <class T>
Link<T>::Link(T val)
: value(val), next(0){}

template <class T>
Link<T>::Link(T val, Link<T>* nxt)
: value(val), next(nxt){}

template <class T>
Link<T>::Link(const Link<T>&source): value(source.value), next(source.next)
{}


//clase list
template <class T>
class List{
private:
    //atributos privados
    Link<T> *head;
    int size;
public:
    //constructores
    List();
    List(const List<T>& );
    //destructor
    ~List();
    
    //metodos
    void insertion(T val);
    int search( T val) const;
    void update(int pos, T val);
    T deleteAt(int pos);
    
    void clear();
    string toString() const;
    
    
};
//constructores
template <class T>
List<T>::List()
: size(0), head(0){}

template <class T>
List<T>::~List()
 {
    clear();
}

//metodo insertion que ingresa valor
template <class T>
void List<T>::insertion(T val){
    //puntero del nuevo elemento
    Link<T> *newLink;
    //se crea
    newLink = new Link<T>(val);
    //apunta a null, osea al final
    newLink -> next = 0;
    //en caso de que este vacia
    if(head == 0){
        //nueva head
        head = newLink;
        size ++;
        return;
    }
    Link<T> *ptr;
    ptr = head;
    //itera hasta el final
    while (ptr->next != 0) {
        ptr = ptr -> next;
    }
        
    ptr -> next = newLink;
    size++;
        
    }
    
    
//busca el valor y regresa su indice
template <class T>
int List<T>::search(T val) const{
    //puntero
    Link<T> *ptr;
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
void List<T>::update(int pos, T val){
    //puntero
    Link<T> *ptr;
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
T List<T>::deleteAt(int pos){
    Link<T> *ptr;
    ptr = head;
    Link<T> *borrar;
    T elimVal;
    if(pos == 0){
        borrar = head ;
        elimVal = borrar -> value;
        head = head -> next;
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
    delete borrar;
    size --;
    return elimVal;
    
    
}

//metodo to string
template <class T>
string List<T>::toString() const {
    stringstream aux;
    Link<T> *p;

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
void List<T>::clear() {
    Link<T> *p, *q;

    p = head;
    while (p != 0) {
        q = p->next;
        delete p;
        p = q;
    }
    head = 0;
    size = 0;
}

//constructor por copia
template <class T>
List<T>::List(const List<T> &source)  {
    Link<T> *p, *q;

    if (source.head ==0) {
        size = 0;
        head = 0;
    } else {
        p = source.head;
        head = new Link<T>(p->value);
        
        q = head;

        p = p->next;
        while(p != 0) {
            q->next = new Link<T>(p->value);
            
            p = p->next;
            q = q->next;
        }
        size = source.size;
    }
}
