#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

template <typename elem>
class fila{

private:
//estructura de la fila
    struct nodo{
        nodo *sig;
        elem dato;
    };
    nodo *primero;

public:
    fila();   // Constructor
    ~fila();  // Destructor
    void agregar(elem dato);
    elem mostrar_primero() const;
    bool eliminar_primero();
    bool es_vacia() const;
    void imprimir() const;
};

#endif // FILA_H_INCLUDED
