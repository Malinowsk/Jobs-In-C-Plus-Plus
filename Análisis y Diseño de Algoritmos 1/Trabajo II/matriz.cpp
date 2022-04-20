#include "matriz.h"
#include <iostream>
#include <string.h>


using namespace std;


matriz::matriz(int n){
    this -> n = n;
    matriz_frecuencia = new float *[n];
    matriz_string = new string *[n];
    for (int i=0; i<n; i++){
        matriz_frecuencia[i]= new float [n];
        matriz_string[i]= new string [n];
    }
    for (int i=0; i< n; i++){
        for (int j=0; j< n; j++){
            matriz_frecuencia[i][j] = 0;
            matriz_string[i][j] = " ";
        }
    }
}

matriz:: ~ matriz(){
    for (int i=0; i<n; i++){
        matriz_frecuencia[i]=NULL;
            delete [] matriz_frecuencia[i];
            delete [] matriz_string[i];
    }
    matriz_frecuencia=NULL;
    delete [] matriz_frecuencia;
    delete [] matriz_string;
    matriz_frecuencia=NULL;
    matriz_string=NULL;
}

void matriz::agregar(int fila,int columna, float frecuencia, string palabra){
    if ((fila >= 0)&&(fila < n)){
        if ((columna >= 0)&&(columna < n)){
            matriz_frecuencia[fila][columna] = frecuencia;
            matriz_string[fila][columna] = palabra;
        }
    }
}

int matriz::obtener_tam() const{
    return n;
}

float matriz::obtener_frecuencia(int fila, int columna) const{
    return matriz_frecuencia[fila][columna];
}

string matriz::obtener_palabra (int fila, int columna) const{
    return matriz_string[fila][columna];
}
