//
// Created by noeli on 25/7/2021.
//

#include <cstdio>
#include "HeapModificado.h"
#include <iostream>
#include <cassert>

using namespace std;


HeapModificado::HeapModificado(int n) {
    this->n = n;
    this->arreglo = new pair<int,int>[n];
    this->punteroHeap = new int[n];
    this->cantElementos = 0;
    for (int i = 0 ; i < n ; i++)
        punteroHeap[i] = -1;
}

void HeapModificado::agregarHeap(int costo, int vertice) {
    if ( this->cantElementos < this->n){
        pair<int,int> dupla;
        dupla.first = costo;
        dupla.second = vertice;
        this->arreglo[this->cantElementos] = dupla;
        this->punteroHeap[ vertice ] = this->cantElementos;
        int actual = this->cantElementos++;
        bool cumple = false;
        while ((actual != 0)&&(!cumple))
            if(this->arreglo[actual].first < this->arreglo[(actual-1) / 2].first ){
                int auxPunt = this->punteroHeap[ this->arreglo[actual].second ];
                this->punteroHeap[ this->arreglo[actual].second ] = this->punteroHeap[ this->arreglo[(actual-1)/2].second ];
                this->punteroHeap[ this->arreglo[(actual-1) / 2].second ] = auxPunt;
                pair<int,int> aux = this->arreglo[actual];
                this->arreglo[actual] = this->arreglo[(actual-1) / 2];
                this->arreglo[(actual-1) / 2] = aux;
                actual = (actual-1) / 2;
            }
            else
                cumple = true;
    }
}

bool HeapModificado::vacioHeap() const {
    return this->cantElementos == 0;
}
pair<int, int> HeapModificado::raizHeap() const {
    assert(!this->vacioHeap());
    pair<int, int> dupla = this->arreglo[0];
    return dupla;
}
void HeapModificado::eliminarHeap() {
    if (!this->vacioHeap()){
        this->punteroHeap[ this->arreglo[0].second ] = -1;
        this->punteroHeap[ this->arreglo[cantElementos-1].second ] = 0;
        this->arreglo[0] = this->arreglo[cantElementos-1];
        this->cantElementos--;
        int actual = 0;
        while (  ( 2*actual + 1 < cantElementos ) && ( (this->arreglo[actual].first > this->arreglo[2*actual+1].first )
                 || (this->arreglo[2*actual+2].first > this->arreglo[actual].first)))
            if ((2*actual + 2 < cantElementos) &&(this->arreglo[2*actual + 2].first < this->arreglo[2*actual + 1].first ) ){
                int auxPunt = this->punteroHeap[ this->arreglo[actual].second ];
                this->punteroHeap[ this->arreglo[actual].second ] = this->punteroHeap[ this->arreglo[2*actual+2].second ];
                this->punteroHeap[ this->arreglo[2*actual+2].second ] = auxPunt;
                pair<int,int> aux = this->arreglo[actual];
                this->arreglo[actual] = this->arreglo[2*actual+2];
                this->arreglo[2*actual+2] = aux;
                actual = 2*actual+2;
            }
            else{
                int auxPunt = this->punteroHeap[ this->arreglo[actual].second ];
                this->punteroHeap[ this->arreglo[actual].second ] = this->punteroHeap[ this->arreglo[2*actual+1].second ];
                this->punteroHeap[ this->arreglo[2*actual+1].second ] = auxPunt;
                pair<int,int> aux = this->arreglo[actual];
                this->arreglo[actual] = this->arreglo[2*actual+1];
                this->arreglo[2*actual+1] = aux;
                actual = 2*actual+1;
            }
    }
}

void HeapModificado::modificarHeap(int costo, int vertice) {

    this->arreglo[ this->punteroHeap[vertice]].first = costo;

    int actual = this->punteroHeap[vertice];
    bool cumple = false;
    while ((actual >= 0) && (!cumple)){

        if( this->arreglo[actual].first  < this->arreglo[(actual-1) / 2].first){
            int auxPunt = this->punteroHeap[ this->arreglo[actual].second ];
            this->punteroHeap[ this->arreglo[actual].second ] = this->punteroHeap[ this->arreglo[(actual-1)/2].second ];
            this->punteroHeap[ this->arreglo[(actual-1) / 2].second ] = auxPunt;

            pair<int,int> aux = this->arreglo[actual];
            this->arreglo[actual] = this->arreglo[(actual-1) / 2];
            this->arreglo[(actual-1) / 2] = aux;

            actual = (actual-1) / 2;
        }
        else
            cumple = true;
    }
}

int HeapModificado::costo(int vertice) const {
    return this->arreglo[ punteroHeap[vertice] ].first;
}

HeapModificado::~HeapModificado() {

}





