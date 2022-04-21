#ifndef DICCIONARIO_H_INCLUDED
#define DICCIONARIO_H_INCLUDED
#include "Lista.h"

class Diccionario
{
public:
    Diccionario();
    ~Diccionario();
    void Agregar(string PalabraDir);
    bool Existe(string PalabraDir);
    string Palabra(int posicion);
    int Cantidad();
    void Mostrar();

private:
    Lista <string> l;
};

Diccionario::Diccionario()
{ }

void Diccionario::Agregar(string PalabraDir){
    l.AgregarAlPrincipio(PalabraDir);
}

string Diccionario::Palabra(int Posicion)
{
    return l.ObtElemPos(Posicion);
}

bool Diccionario::Existe(string Palabra)
{
    return l.VerificarElem(Palabra);
}

int Diccionario::Cantidad()
{
    return l.Longitud();
}

void Diccionario::Mostrar() {
    for (int i=1; i <= l.Longitud(); i++)
        cout << l.ObtElemPos(i) << endl;
}

Diccionario::~Diccionario(){
}

#endif // DICCIONARIO_H_INCLUDED
