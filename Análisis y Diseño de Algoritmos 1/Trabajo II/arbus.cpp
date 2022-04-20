#include <iostream>
#include <iomanip>
#include "arbus.h"
#include "matriz.h"
#include "lista.h"

using namespace std;

arbus::arbus(){
    raiz = NULL;
}

void arbus::insertar_nodo(nodo *&raiz, string palabra, float frecuencia){
    if (raiz == NULL){
        nodo * nuevo = new nodo;
        nuevo -> palabra = palabra;
        nuevo -> frecuencia = frecuencia;
        nuevo -> der = NULL;
        nuevo -> izq = NULL;
        raiz = nuevo;
    }
    else{
        if (raiz -> palabra > palabra)
            insertar_nodo(raiz -> izq, palabra, frecuencia);
        else
            insertar_nodo(raiz -> der, palabra, frecuencia);
    }
}

void arbus::agregar_arbus(string palabra, float frecuencia){
    insertar_nodo(raiz, palabra, frecuencia);
}

bool arbus::buscar(nodo *raiz, string palabra, int &k)const{
    k++;
    if (raiz == NULL)
        return false;
    else
        if ((raiz -> palabra) == palabra)
            return true;
        else
            if ((raiz -> palabra) > palabra)
                return buscar(raiz -> izq, palabra, k);
            else
                return buscar(raiz ->der, palabra, k);
}

int unsigned arbus::costo_busqueda(string palabra) const{
    int k = 0;
    if (buscar(raiz, palabra, k))
        return k;
    else
        return 0;
}

bool arbus::pertenece(string palabra, int &k){
    if (buscar(raiz, palabra, k))
        return true;
    else
        return false;
}

bool arbus::vacio_arbus() const{
    return (raiz == NULL);
}

int arbus::altura(){
    int alto = 0;
    int nivel = 0;
    buscar_altura(raiz, alto, nivel);
    return alto;
}

void arbus::buscar_altura(nodo *raiz, int &alto, int nivel){
    if (raiz != NULL){
        buscar_altura(raiz -> izq, alto, nivel +1);
        if (nivel > alto)
            alto = nivel;
        buscar_altura(raiz -> der, alto, nivel +1);
    }
}

void arbus::arreglo_niveles(nodo *raiz, int nivel, string arreglo[]){
    if (raiz != NULL){
        string palabra = raiz -> palabra;
        arreglo[nivel] = arreglo[nivel] + " - " + palabra;
        arreglo_niveles(raiz -> izq, nivel +1, arreglo);
        arreglo_niveles(raiz -> der, nivel +1, arreglo);
    }
}

void arbus::imprimir_por_niveles(){
    int longitud = (altura() + 1);
    string arreglo[longitud];
    for (int i = 0; i < longitud; i++)
        arreglo[i] = "-";
    arreglo_niveles(raiz, 0, arreglo);
    for (int i = 0; i < longitud; i++)
        cout << "En nivel " << i << ": " << arreglo[i] << endl;
}

void arbus::crear_arbol_optimo(matriz &M1, lista &L1){
    int n = M1.obtener_tam() -1;
    string palabra = M1.obtener_palabra(1, n);
    float frecuencia = L1.frecuencia_de_palabra(palabra);
    agregar_arbus(palabra, frecuencia);
    int k = L1.posicion_de_palabra(palabra);
    subarbol(raiz -> izq, L1, M1, 1, k-1);
    subarbol(raiz -> der, L1, M1, k+1, n);

}

void arbus::subarbol(nodo *&raiz, lista &L1, matriz &M1, int inicio, int fin){
    if ((raiz == NULL)&&(inicio <= fin)){
        string palabra = M1.obtener_palabra(inicio, fin);
        float frecuencia = L1.frecuencia_de_palabra(palabra);
        int k = L1.posicion_de_palabra(palabra);
        nodo * nuevo = new nodo;
        nuevo -> palabra = palabra;
        nuevo -> frecuencia = frecuencia;
        nuevo -> der = NULL;
        nuevo -> izq = NULL;
        raiz = nuevo;
        subarbol(raiz -> izq, L1, M1, inicio, k-1);
        subarbol(raiz -> der, L1, M1, k+1, fin);
    }
}
