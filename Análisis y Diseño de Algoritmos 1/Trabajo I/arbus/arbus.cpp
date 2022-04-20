#include <iostream>
#include "arbus.h"

using namespace std;

template <typename elem>
arbus<elem>::arbus(){
    raiz = NULL;
    n = 0;
    k = 0;
}

template <typename elem>
void arbus<elem>::insertar_nodo(nodo * & raiz, elem dato){
    if (raiz == NULL){
        nodo * nuevo = new nodo;
        nuevo -> dato = dato;
        nuevo -> der = NULL;
        nuevo -> izq = NULL;
        raiz = nuevo;
        n++;
    }
    else{
        if (raiz -> dato > dato)
            insertar_nodo(raiz -> izq, dato);
        else
            insertar_nodo(raiz -> der, dato);
    }
}

template <typename elem>
void arbus<elem>::agregar_arbus(elem dato){
    insertar_nodo(raiz, dato);
}

template <typename elem>
int arbus<elem>::costo(){
    int p = 0;
    p = k;
    k = 0;
    return p;
}

template <typename elem>
bool arbus<elem>::buscar(nodo * raiz, elem dato){
    k ++;
    if (raiz == NULL)
        return false;
    else
        if ((raiz -> dato) == dato)
            return true;
        else
            if ((raiz -> dato) > dato)
                return buscar(raiz -> izq, dato);
            else
                return buscar(raiz ->der, dato);
}

template <typename elem>
bool arbus<elem>::pertenece(elem dato){
    return buscar(raiz, dato);
}

template <typename elem>
int unsigned arbus<elem>::cant_elementos() const{
    return n;
}

template <typename elem>
bool arbus<elem>::vacio_arbus() const{
    return (raiz == NULL);
}

template <typename elem>
void arbus<elem>::imprimir(nodo * raiz) const{
    if (raiz != NULL){
        imprimir(raiz -> izq);
        cout << raiz -> dato << " ";
        imprimir(raiz -> der);
    }
}

template <typename elem>
void arbus<elem>::inorden() const{
    if (raiz == NULL)
        cout << "el arbol esta vacio"<<endl;
    else{
        imprimir(raiz);
        cout <<endl;
    }
}
template class arbus <int>;
template class arbus <char>;
template class arbus <float>;
template class arbus <string>;

