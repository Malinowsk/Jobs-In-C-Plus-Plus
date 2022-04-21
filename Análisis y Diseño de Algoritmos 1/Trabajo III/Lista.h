#ifndef LISTA_H
#define LISTA_H
#include "Lista.h"

template <typename Elem>
class Lista
{
    public:
        Lista();
        void AgregarAlPrincipio(Elem valor);
        void AgregarAlFinal(Elem valor);
        void AgregarPos(Elem valor, int);
        int Longitud() const;
        Elem ObtElemPos(int);
        bool VerificarElem(Elem valor);
        void EliminarElem(Elem valor);
        void Mostrar();
        virtual ~Lista();
    private:
        struct listaElem{
            Elem valor;
            listaElem * sig;
        };
        listaElem * lista;
};

template <typename Elem>
Lista<Elem>::Lista()
{
    lista = 0;
}

template <typename Elem>
void Lista<Elem> :: AgregarAlPrincipio (Elem valor)
{
    if (lista == 0)
    {
        lista = new listaElem;
        lista->valor=valor;
        lista->sig=0;
    }
    else
    {
        listaElem * nodo = new listaElem;
        nodo->valor=valor;
        nodo->sig=lista;
        lista=nodo;
    }
}

template <typename Elem>
void Lista<Elem> :: AgregarAlFinal (Elem valor)
{
    if (lista == 0)
    {
        lista = new listaElem;
        lista->valor=valor;
        lista->sig=0;
    }
    else
    {
        listaElem * cursor;
        cursor = lista;
        while (cursor->sig != 0)
            cursor=cursor->sig;
        listaElem * nodo = new listaElem;
        nodo->valor=valor;
        nodo->sig=0;
        cursor->sig=nodo;
    }
}

template <typename Elem>
void Lista<Elem> :: AgregarPos(Elem valor,int pos)
{
  if (pos == 1){
      AgregarAlPrincipio(valor);
    }
  else if (pos == Longitud()){
    AgregarAlFinal(valor);
  }
  else{
    listaElem * nodo = new listaElem;
    listaElem * aux;
    aux=lista;
  while (pos>1){
    aux=aux->sig;
    pos--;
  }
    nodo->valor=valor;
    nodo->sig=aux;
    aux=nodo;
    }
}

template <typename Elem>
void Lista<Elem> :: EliminarElem(Elem valor)
{
    listaElem* NodoAEliminar;
    if (lista->valor == valor){
        NodoAEliminar=lista;
        lista=lista->sig;
        delete NodoAEliminar;
    }
    else {
    listaElem* aux;
    aux=lista;
    bool encontrado=false;
    while (not encontrado){
        if (aux->sig->valor == valor)
        {
            NodoAEliminar=aux->sig;
            aux->sig=aux->sig->sig;
            delete NodoAEliminar;
            encontrado=true;
        }
        else
            aux=aux->sig;
    }
    }
}

template <typename Elem>
bool Lista<Elem> :: VerificarElem (Elem valor)
{
    listaElem* aux;
    aux=lista;
    for (int i=1; i <= Longitud(); i++)
    {
        if (valor == aux->valor )
            return true;
        else
            aux=aux->sig;
    }
    return false;
}


template <typename Elem>
Elem Lista<Elem> ::ObtElemPos(int pos)
{
    listaElem* aux;
    aux=lista;
    int i=1;
    while (i<pos) {
        i++;
        aux=aux->sig;
    }
    return aux->valor;
}

template <typename Elem>
int Lista<Elem> :: Longitud() const
{
    int pos=0;
    listaElem * cursor;
    cursor = lista;
    while (cursor != 0){
        pos++;
        cursor=cursor->sig;
    }
    return pos;
}


template <typename Elem>
Lista<Elem>::~Lista()
{
    listaElem* NodoAEliminar;
    while (lista != 0)
    {
        NodoAEliminar=lista;
        lista=lista->sig;
        delete NodoAEliminar;
    }
}

template <typename Elem>
void Lista<Elem> :: Mostrar()
{
    listaElem * Nodo;
    Nodo=lista;
    while (Nodo != 0)
    {
        std::cout << Nodo->valor<< std::endl;
        Nodo=Nodo->sig;
    }
}

#endif // LISTAA_H
