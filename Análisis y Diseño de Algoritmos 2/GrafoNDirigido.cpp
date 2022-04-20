#include "GrafoNDirigido.h"
#include <climits>
#include <cassert>

GrafoNDirigido::GrafoNDirigido() {
    this->matriz = new int*[MAX_VERTICES];
    for(int i = 0 ; i < MAX_VERTICES; i++)
        this->matriz[i] = new int[MAX_VERTICES];

    for(int i = 0 ; i < MAX_VERTICES ; i++)
        for(int j = 0 ; j < MAX_VERTICES ; j++)
            this->matriz[i][j] = INT_MAX;

    this->numVertices = 0;
}

void GrafoNDirigido::agregarVertice() {
    this->numVertices++;
}

void GrafoNDirigido::agregarArista(int origen, int destino, int costo) {
    if((origen >= 0) && (origen < this->numVertices) && (destino >= 0) && (destino < this->numVertices)){
        this->matriz[origen] [destino] = costo;
        this->matriz[destino] [origen] = costo;
        pair<int,int> arista1;
        arista1.first = origen;
        arista1.second = destino;
        listArcos.push_back(arista1);

    }
}

int GrafoNDirigido::cantVertices() const {
    return this->numVertices;

}

bool GrafoNDirigido::existeArista(int origen, int destino) const {
    assert((origen >= 0) && (origen < this->numVertices) && (destino >= 0) && (destino < this->numVertices));
    return this->matriz[origen][destino] != INT_MAX;
}

list<int>  GrafoNDirigido::adyacentes(int vertice) const {
    list<int> lRetorno;
    for(int i = 0 ; i < this->numVertices; i++)
        if(this->matriz[vertice][i] != INT_MAX)
            lRetorno.push_back(i);

    return lRetorno;
}

list<pair<int, int> > GrafoNDirigido::aristasGrafo() const {
    list<pair<int, int> > copia ;
    list<pair<int, int> >::const_iterator itCopia;
    for( itCopia = this->listArcos.cbegin() ; itCopia != this->listArcos.cend(); itCopia++)
        copia.push_back(*itCopia);

    return copia;
}

GrafoNDirigido::~GrafoNDirigido() {

}

int GrafoNDirigido::costo(int origen, int destino) const {
    return this->matriz[origen][destino];
}


