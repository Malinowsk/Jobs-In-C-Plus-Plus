#include "GrafoDirigido.h"
#include <cassert>
#include <iostream>
using namespace std;

GrafoDirigido::GrafoDirigido() {

    this->listAdy = new list<Nodo> [this->MAX_VERTICES]; //Crea un arreglo, donde cada celda es una lista de nodos
    this->numVertices = 0;
}

void GrafoDirigido::agregarVertice() {
    this->numVertices++;
}

void GrafoDirigido::agregarArco(int origen, int destino, int costo) {

    if((origen >= 0) && (origen < this->numVertices) && (destino >= 0) && (destino < this->numVertices)){
        Nodo nodo{destino,costo};
        this->listAdy[origen].push_back(nodo);
    }

}

int GrafoDirigido::cantVertices() const {
    return this->numVertices;
}
bool GrafoDirigido::existeArco(int origen, int destino) const {
    assert((origen >= 0) && (origen < this->numVertices) && (destino >= 0) && (destino < this->numVertices));
    list<GrafoDirigido::Nodo>::const_iterator it;
    for(it = this->listAdy[origen].cbegin() ; it != this->listAdy[origen].cend(); it++)
        if(it->vertice == destino)
            return true;
    return false;
}
 list<GrafoDirigido::Nodo> GrafoDirigido::adyacentes(int vertice) const {
    assert((vertice >= 0) && (vertice < this->numVertices));
     return this->listAdy[vertice];
}

GrafoDirigido::~GrafoDirigido() {

}




