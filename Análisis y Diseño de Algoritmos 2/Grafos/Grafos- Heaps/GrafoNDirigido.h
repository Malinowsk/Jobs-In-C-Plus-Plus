#include <list>

using namespace std;

class GrafoNDirigido{

    public:
        GrafoNDirigido();
        void agregarVertice();
        void agregarArista(int origen, int destino , int costo);
        int cantVertices() const;
        bool existeArista( int origen , int destino) const;
        list<int> adyacentes(int vertice) const;
        int costo (int origen , int destino) const;
        list < pair<int,int> >  aristasGrafo() const;
        virtual ~ GrafoNDirigido();

    private:
        const int MAX_VERTICES = 100;
        int ** matriz;
        list < pair<int,int> > listArcos;
        int numVertices;

};


#ifndef AYDAII_GRAFONDIRIGIDO_H
#define AYDAII_GRAFONDIRIGIDO_H

#endif //AYDAII_GRAFONDIRIGIDO_H
