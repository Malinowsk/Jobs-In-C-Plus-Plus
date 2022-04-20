//
// Created by noeli on 27/7/2021.
//

#include "Heap.h"
#include <cassert>
#include <iostream>

using namespace std;

Heap::Heap(int n) {
    this->n = n;
    this->arreglo = new pair<int, pair<int,int> >[this->n];
    this->cantElementos = 0;
}

void Heap::agregarHeap(int costo, pair<int, int> arista) {
    int actual = this->cantElementos;
    this->arreglo[this->cantElementos++] = {costo , arista};
    bool cumple = false;
    while ((actual != 0)&&(!cumple))
        if (this->arreglo[actual].first < this->arreglo[(actual-1) / 2].first){
            pair<int, pair<int,int> >  aux = this->arreglo[actual];
            this->arreglo[actual] = this->arreglo[(actual-1) / 2];
            this->arreglo[(actual-1) / 2] = aux;
            actual = (actual - 1) / 2;
        }
        else
            cumple = true;

}

bool Heap::vacioHeap() const {
    return this->cantElementos == 0;
}
pair<int, pair<int,int> > Heap::raizHeap() const {
    assert(!this->vacioHeap());
    return this->arreglo[0];
}

void Heap::eliminarHeap() {

    if(!vacioHeap()){
        this->arreglo[0] = this->arreglo[this->cantElementos-- - 1];
        int actual = 0;
        while (  ( 2*actual + 1 < cantElementos ) && ( (this->arreglo[actual].first > this->arreglo[2*actual+1].first )
        || (this->arreglo[actual].first > this->arreglo[2*actual+2].first)))
            if ((2*actual + 2 < cantElementos) &&(this->arreglo[2*actual + 2].first < this->arreglo[2*actual + 1].first ) ){
                pair<int,pair<int,int> > aux = this->arreglo[actual];
                this->arreglo[actual] = this->arreglo[2*actual+2];
                this->arreglo[2*actual+2] = aux;
                actual = 2*actual+2;
            }
            else{
                pair<int, pair<int,int> > aux = this->arreglo[actual];
                this->arreglo[actual] = this->arreglo[2*actual+1];
                this->arreglo[2*actual+1] = aux;
                actual = 2*actual+1;
            }
    }
}

void Heap::mostrar() {

    for (int i = 0 ; i < this->cantElementos ; i++ )
        cout<<"Arista ("<<arreglo[i].second.first<<","<<arreglo[i].second.second<<") ; Costo: "<<arreglo[i].first<<endl;
}

Heap::~Heap() {

}

