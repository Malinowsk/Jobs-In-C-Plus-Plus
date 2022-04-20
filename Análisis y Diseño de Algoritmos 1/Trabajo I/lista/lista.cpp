#include <iostream>
#include "lista.h"

using namespace std;

template <typename elem>
lista<elem>::lista(){
    primero = NULL;
    n = 0;
    k = 0;
}

template <typename elem>
bool lista<elem>::vacia_lista() const{
    return (primero == NULL);
}

template <typename elem>
void lista<elem>::Agregar_prin(elem dato){
    nodo * aux = new nodo;
    aux -> dato = dato;
    aux -> sig = primero;
    primero = aux;
    aux = NULL;
    n++;
}

template <typename elem>
void lista<elem>::Agregar_final(elem dato){
    if (vacia_lista() == true)
        Agregar_prin(dato);
    else{
        nodo * cursor = primero;
        while (cursor -> sig != NULL)
            cursor = cursor -> sig;
        nodo * aux = new nodo;
         aux -> dato = dato;
         aux -> sig = NULL;
         cursor -> sig = aux ;
             n++;
        }
}

template <typename elem>
int unsigned lista<elem>::longitud() const{
    return n;
}

template <typename elem>
void lista<elem>::Agregar_pos(elem dato, int posicion){
    if ((posicion >= 1) && (posicion <= longitud() + 1)){
        if (posicion == 1)
            Agregar_prin(dato);
        else{
            nodo * cursor = primero;
            int j = 2;
            while (j != posicion){
                j++;
                cursor = cursor -> sig;
            }
            nodo * aux = new nodo;
            aux -> dato = dato;
            aux -> sig = cursor -> sig;
            cursor -> sig = aux;
            n++;
        }
    }
    else
        cout << "la posicion es invalida" <<endl;
}

template <typename elem>
int unsigned lista<elem>::costo(){
    return k;
}

template <typename elem>
bool lista<elem>::pertenece(elem dato) {
    k = 1;
    if (vacia_lista() == true)
        return false;
    else{
        nodo * cursor = primero;
        while (((cursor -> dato) != (dato)) && ((cursor -> sig) != (NULL))){
            cursor = cursor -> sig;
            k++;
        }
        if (cursor -> dato == dato)
            return true;
        else
            return false;
    }
}

template <typename elem>
void lista<elem>::imprimir() const{
    if (vacia_lista() == true)
        cout << "La lista esta vacia" <<endl;
    else{
        nodo * cursor = primero;
        cout << "Lista: ";
        while (cursor != NULL){
            cout << cursor -> dato << " - ";
            cursor = cursor -> sig;
        }
        cout <<endl;
        }
}

template <typename elem>
bool lista<elem>::Elimina_elem(elem dato){
    if (vacia_lista() == true)
            return false;
    if (primero -> dato == dato){
        nodo * eliminar = primero;
        primero = primero -> sig;
        delete eliminar;
        n--;
        return true;
    }
    else{
        nodo * cursor = primero;
        nodo * aux = new nodo;
        while ((cursor -> sig != NULL) && (cursor -> dato != dato)){
            aux = cursor;
            cursor = cursor -> sig;
        }
        if (cursor -> dato == dato){
            aux -> sig = cursor -> sig;
            cursor -> sig = NULL;
            delete cursor;
                n--;
            return true;
        }
        else
            return false;
    }
}

template <typename elem>
void lista<elem>::Elimina_lista(){
    while (primero != NULL){
        nodo * eliminar = primero;
        primero = primero -> sig;
        delete eliminar;
        n--;
    }
}
template class lista <int>;
template class lista <char>;
template class lista <float>;
template class lista <string>;
