//
//  funciones.h
//  Tarea1_ds
//
//  Created by Isabel Vaca on 26/08/25.
//

#ifndef FUNCIONES_H
#define FUNCIONES_H

class Funciones{
    
public:
    
    //Funcion iterativa O(n)
    int sumaIterativa(int n) {
        int i = 0;
        int acum = 0;
        
        if (n<=0){
            return 0;
        }
        
        while(i<=n){
            acum+=i;
            i++;
        }
        return acum;
    }
    
    
    //Funcion recursiva O(2*n)
    int sumaRecursiva(int n){
        if (n<=0){
            return 0;
        }
            return sumaRecursiva(n-1) + n;

    }
    
    //Funcion directa O(1)
    //Explicación (con apoyo de internet)
    //Gauss. se hace la suma de la sucesion de inicio a fin  (n-1) +n
    //y la suma de la sucesion del fin al inicio n+(n-1). cada par suma n+1 y hay n pares
    //https://www.youtube.com/watch?v=cYw4MFWsB6c&t=197s
    int sumaDirecta(int n){
        if(n<=0){
            return 0;
        }
        int res = (n*(n+1))/2;
        return res;
    }
    
    
};


#endif
