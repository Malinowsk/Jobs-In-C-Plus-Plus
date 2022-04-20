#ifndef ARBUS_H_INCLUDED
#define ARBUS_H_INCLUDED

template <typename elem>
class arbus{

private:
//estructura del arbol
struct nodo{
        nodo * izq; //estructura de un nodo
        nodo * der;
        elem dato;
    };
    nodo * raiz;
    int n;  //variable que cuenta los elementos del arbol
    int k;  //variable para medir complejidad de busqueda
    void insertar_nodo(nodo * & raiz, elem dato);   //funcion recursiva que inserta un nodo
    bool buscar(nodo * raiz, elem dato);    //funcion recursiva que busca un elemento
    void imprimir(nodo * raiz) const;   //funcion recursiva que imprime el arbol

public:
    arbus();
    void agregar_arbus(elem dato);
    bool pertenece(elem dato);
    int unsigned cant_elementos() const;
    bool vacio_arbus() const;
    void inorden() const;
    int costo();
};

#endif // ARBUS_H_INCLUDED
