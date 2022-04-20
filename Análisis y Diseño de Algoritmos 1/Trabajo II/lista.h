#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <cstring>

using namespace std;

class lista{
//estructura de la lista
struct nodo {
        string palabra;
        float frecuencia;
        nodo * sig;
           };
    nodo * primero;
    int n;

public:
    lista();
    ~lista();
    void Agregar_prin(string palabra, float frecuencia);
    int longitud() const;
    void insertar_ordenado(string palabra, float frecuencia);
    string palabra_de_posicion (int posicion) const;
    int posicion_de_palabra (string palabra) const;
    float frecuencia_de_posicion (int posicion) const;
    float frecuencia_de_palabra (string palabra) const;
    bool pertenece(string palabra) const;
    bool vacia_lista() const;
    void imprimir() const;
};

#endif // LISTA_H_INCLUDED
