

#ifndef AYDAII_HEAPMODIFICADO_H
#define AYDAII_HEAPMODIFICADO_H

#include <utility>

using namespace std;

class HeapModificado {

    public:
        HeapModificado(int n);
        void agregarHeap (int costo , int vertice);
        bool vacioHeap() const;
        void eliminarHeap();
        void modificarHeap(int costo, int vertice);
        int costo (int vertice) const;
        pair<int,int> raizHeap() const;
        void mostrar();
        virtual ~HeapModificado();

    private:
        const int DISCERNIBLE = -1;
        int cantElementos;
        int n;
        pair<int,int> * arreglo;
        int * punteroHeap;

};


#endif //AYDAII_HEAPMODIFICADO_H
