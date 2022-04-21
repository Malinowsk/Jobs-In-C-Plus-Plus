#include "fila.h"
#include <iostream>

using namespace std;

template <typename elem>
fila<elem>::fila(){
    primero = NULL;
}

template <typename elem>
fila<elem>::~fila(){
    while (primero != NULL){
        nodo *eliminar = primero;
        primero = primero -> sig;
        delete eliminar;
    }
}

template <typename elem>
void fila<elem>::agregar(elem dato){
    if (primero == NULL){
        nodo *aux = new nodo;
        aux -> dato = dato;
        aux -> sig = primero;
        primero = aux;
        aux = NULL;
    }
    else{
        nodo *cursor = primero;
        while (cursor -> sig != NULL)
            cursor = cursor -> sig;
        nodo *aux = new nodo;
        aux -> dato = dato;
        aux -> sig = NULL;
        cursor -> sig = aux ;
    }
}

template <typename elem>
elem fila<elem>::mostrar_primero() const{
    return (primero -> dato);
}

template <typename elem>
bool fila<elem>::eliminar_primero(){
    nodo *eliminar = primero;
    primero = primero -> sig;
    delete eliminar;
}

template <typename elem>
bool fila<elem>::es_vacia() const{
    return (primero == NULL);
}

template <typename elem>
void fila<elem>::imprimir() const{
        if (primero == NULL)
        cout << "La fila esta vacia" <<endl;
    else{
        nodo *cursor = primero;
        cout << "fila: " <<endl;
        while (cursor != NULL){
            cout << cursor -> dato << " - ";
            cursor = cursor -> sig;
        }
        cout <<endl;
    }
}

template class fila <int>;
template class fila <char>;
template class fila <float>;
template class fila <string>;
