#ifndef ARBUS_H_INCLUDED
#define ARBUS_H_INCLUDED
#include "matriz.h"
#include "lista.h"

using namespace std;

class arbus{
private:
//estructura del arbol
struct nodo{
        nodo * izq; //estructura de un nodo
        nodo * der;
        float frecuencia;
        string palabra;
    };
    nodo *raiz;
    void insertar_nodo(nodo *&raiz, string palabra, float frecuencia);   //funcion recursiva que inserta un nodo
    bool buscar(nodo *raiz, string palabra, int &k)const;    //funcion recursiva que busca un elemento
    void buscar_altura(nodo *raiz, int &alto, int nivel);
    void arreglo_niveles(nodo *raiz, int nivel, string arreglo[]);
    void subarbol(nodo *&raiz, lista &L1, matriz &M1, int inicio, int fin);


public:
    arbus();
    void agregar_arbus(string palabra, float frecuencia);
    int unsigned costo_busqueda(string palabra) const;
    bool pertenece(string palabra, int &k);
    bool vacio_arbus() const;
    void imprimir_por_niveles();
    int altura();
    void crear_arbol_optimo(matriz &M1, lista &L1);
};

#endif // ARBUS_H_INCLUDED
