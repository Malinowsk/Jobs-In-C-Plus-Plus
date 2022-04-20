#include <list>

using namespace std;

    class GrafoDirigido{

    public:

        struct Nodo {
            int vertice;
            int costo;
        };

        GrafoDirigido();
        void agregarVertice();
        void agregarArco(int origen, int destino , int costo);
        int cantVertices() const;
        bool existeArco( int origen , int destino) const;
        list<Nodo> adyacentes(int vertice) const;
        virtual ~ GrafoDirigido();

    private:

        const int MAX_VERTICES = 100;
        list<Nodo> * listAdy;
        int numVertices;
  };






#ifndef AYDAII_GRAFODIRIGIDO_H
#define AYDAII_GRAFODIRIGIDO_H

#endif //AYDAII_GRAFODIRIGIDO_H
