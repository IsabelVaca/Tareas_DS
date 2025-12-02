//
//  sorts.h
//  Alg_de_busqueda
//
//  Created by Isabel Vaca on 08/09/25.
//
using namespace std;

template <class T>
class Sorts {
public:
    int busqSecuencial(vector<T> &v, int val ){
        for(int i=0; i<v.size(); i++){
            if(v[i]==val){
                return i;
            }
            
        }
        return -1;
    }
    
    int busqBinaria( vector<T> &v, int val){
        int low = 0;
        long high = v.size()-1;
        
        while(low<=high){
            int mid = ((low+high)/2);
            if(v[mid] == val){
                return mid;
            }
            if(v[mid] > val){
                high = mid-1;
            }
            if (v[mid] < val){
                low = mid + 1;
            }
        }
        return -1;
    }
    
    void ordenaBurbuja(vector<T> &s){
        for(int i=0; i<s.size(); i++){
            for(int j=0;j<s.size()-1;j++){
                if (s[j]>s[j+1]){
                    swap(s, j,j+1);
                }
            }
        }

    }
    
    void swap(vector<T> &v, int i, int j){
        T aux = v[i];
        v[i] = v[j];
        v[j] = aux;
    }
    
    void mergeSplit(vector<T> &A, vector<T> &B,int low, long high){
        if((high-low)<1){
            return;
        }
        int mid = low+ ((high-low)/2);
        mergeSplit(A,B,low,mid);
        mergeSplit(A,B,mid+1,high);
        mergeArr(A,B,low,mid,high);
        
    }
    
    void ordenaMerge( vector<T> &s){
        vector<T> tmp(s.size());
        
        int high = s.size()-1;
        int low = 0;

        
        mergeSplit(s, tmp, low, high);
        
    }
    
    void mergeArr(vector<T> &A, vector<T> &B,int low,int mid, int high ){
        
        int i = low;
        int j = mid +1;
        int k = low;
        
        while(i<= mid && j <= high){
            if(A[i] < A[j]){
                B[k] = A[i];
                i++;
                k++;
            }
            else{
                B[k] = A[j];
                j++;
                k++;
            }
            
            
        }
        while(i<=mid){
            B[k] = A[i];
            i++;
            k++;
            
        }
        while(j<=high){
            B[k] = A[j];
            j++;
            k++;
        }
        
        for(int l=low;l<=high; l++){
            A[l] = B[l];
            
        }
        
    }
    
    void ordenaSeleccion( vector<T> &v){
        int length = v.size();
        
        for(int i = 0; i<v.size()-1; i++){
            int min = i;
            for(int j = i+1; j<length; j++){
                if(v[min]>v[j]){
                    min = j;
                }
                
            }
            if(min!= i){
                swap(v, i, min);
            }
           
        }
    }
    
};

