#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

template <typename elem>
class lista{

private:
//estructura de la lista
struct nodo{
        nodo * sig; //estructura de un nodo
        elem dato;
    };
    nodo * primero;
    int n; //variable para medir longitud
    int k; //variable para medir complejidad de busqueda

public:
    lista();
    void Agregar_prin(elem dato);
    void Agregar_final(elem dato);
    int unsigned longitud() const;
    void Agregar_pos(elem dato, int posicion);
    bool pertenece(elem dato) ;
    bool vacia_lista() const;
    bool Elimina_elem(elem dato);
    void Elimina_lista();
    void imprimir() const;
    int unsigned costo();
};

#endif // LISTA_H_INCLUDED
