#include <iostream>
#include "lista.h"

using namespace std;

lista::lista(){
    primero = NULL;
    n = 0;
}

lista::~lista(){

     while (primero != NULL){
        nodo * eliminar = primero;
        primero = primero -> sig;
        eliminar->sig = NULL;
        delete eliminar;
        n--;}
}

bool lista::vacia_lista() const{
    return (primero == NULL);
}

void lista::Agregar_prin(string palabra, float frecuencia){
    nodo *aux = new nodo;
    aux -> palabra = palabra;
    aux -> frecuencia = frecuencia;
    aux -> sig = primero;
    primero = aux;
    aux = NULL;
    n++;
}

void lista::insertar_ordenado(string palabra, float frecuencia){
    if ((primero == NULL)||((primero -> palabra) > palabra))
        Agregar_prin(palabra, frecuencia);
    else{
        nodo *aux = new nodo;
        nodo *anterior = new nodo;
        nodo *cursor = primero;
        while ((cursor -> sig != NULL)&&((cursor -> palabra) < (palabra))){
            anterior = cursor;
            cursor = cursor -> sig;
        }
        aux -> palabra = palabra;
        aux -> frecuencia = frecuencia;
        if ((cursor -> sig == NULL)&&(cursor -> palabra) < (palabra)){
            aux -> sig = NULL;
            cursor -> sig = aux;
            n++;
        }
        else{
            aux -> sig = cursor;
            anterior -> sig = aux;
            n++;
        }
    }
}

string lista::palabra_de_posicion ( int posicion) const{
    if (posicion <= longitud()){
        nodo *cursor = primero;
        int i = 1;
        while ((cursor != NULL)&&(i<posicion)){
            cursor = cursor -> sig;
            i++;
        }
        return (cursor -> palabra);
    }
    else
        return "posicion invalida";

}

int lista::posicion_de_palabra (string palabra) const{
    if (pertenece(palabra)){
        nodo *cursor = primero;
        int i = 1;
        while ((cursor != NULL)&&(cursor -> palabra < palabra)){
            cursor = cursor -> sig;
            i++;
        }
        return i;
    }
    else
        return -1;
}

float lista::frecuencia_de_posicion (int posicion) const{
    if (posicion <= longitud()){
        nodo *cursor = primero;
        int i = 1;
        while ((cursor != NULL)&&(i<posicion)){
            cursor = cursor -> sig;
            i++;
        }
        return (cursor -> frecuencia);
    }
    else
        return -1;
}

float lista::frecuencia_de_palabra (string palabra) const{
    if (pertenece(palabra)){
        nodo *cursor = primero;
        int i = 1;
        while ((cursor != NULL)&&(cursor -> palabra < palabra)){
            cursor = cursor -> sig;
            i++;
        }
        return (cursor -> frecuencia);
    }
    else
        return -1;
}

int lista::longitud() const{
    return n;
}

bool lista::pertenece(string palabra) const{
    if (vacia_lista() == true)
        return false;
    else{
        nodo * cursor = primero;
        while (((cursor -> sig) != (NULL))&&((cursor -> palabra) != (palabra)))
            cursor = cursor -> sig;
        if (cursor -> palabra == palabra)
            return true;
        else
            return false;
    }
}

void lista::imprimir() const{
    if (vacia_lista() == true)
        cout << "La lista esta vacia" <<endl;
    else{
        nodo * cursor = primero;
        while (cursor != NULL){
            cout << cursor -> palabra << ", " << cursor -> frecuencia <<endl;
            cursor = cursor -> sig;
        }
        cout <<endl;
    }
}
