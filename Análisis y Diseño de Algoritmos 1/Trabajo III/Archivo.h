#ifndef ARCHIVO_H_INCLUDED
#define ARCHIVO_H_INCLUDED
#include <iostream>
#include <fstream>
#include "Lista.h"

using namespace std;

class Archivo
{
public:
    Archivo();
    ~Archivo();
    string ObtPalabra(int posicion);
    void Agregar(string Palabra);
    void Guardar();
    int Lineas();
    void Mostrar();
private:
    Lista <string> l;
};

Archivo::Archivo()
{ }

void Archivo::Agregar(string Palabra)
{
    l.AgregarAlPrincipio(Palabra);
}

string Archivo::ObtPalabra(int posicion)
{
    return l.ObtElemPos(posicion);
}

void Archivo::Mostrar() {
    for (int i=1; i <= l.Longitud(); i++)
        cout << l.ObtElemPos(i) << endl;
}

void Archivo::Guardar() {
    ofstream Arch("Salida.txt",ios::out);
    for (int i=1; i <= l.Longitud(); i++)
        Arch << l.ObtElemPos(i) << endl;
}

int Archivo::Lineas()
{
    return l.Longitud();
}

Archivo::~Archivo()
{ }

#endif // ARCHIVO_H_INCLUDED
