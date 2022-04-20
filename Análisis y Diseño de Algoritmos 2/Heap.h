//
// Created by noeli on 27/7/2021.
//

#ifndef AYDAII_HEAP_H
#define AYDAII_HEAP_H
#include <utility>

using namespace std;


class Heap {
    public:
       Heap (int n);
       void agregarHeap(int costo , pair<int,int> arista);
       bool vacioHeap() const;
       pair < int , pair <int,int> > raizHeap() const;
       void eliminarHeap();
       void mostrar();
       ~Heap();

    private:
        pair<int , pair<int,int> > * arreglo;
        int n;
        int cantElementos;
};


#endif //AYDAII_HEAP_H
