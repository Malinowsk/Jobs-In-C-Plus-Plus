#include <iostream>
#include "GrafoD.h"

using namespace std;

template<typename C>
ostream & operator << (ostream & salida, const GrafoD<C> & Grafo){
    // Recorremos todos los vertices
    list<int> vertices;
    Grafo.devolverVertices(vertices);
    list<int>::iterator v = vertices.begin();
    while (v != vertices.end()){
        salida << "    " << *v << "\n";
        // Recorremos todos los adyacentes de cada vertice
        list< typename GrafoD<C>::Arco> adyacentes;
        Grafo.devolverAdyacentes(*v, adyacentes);
        typename list< typename GrafoD<C>::Arco>::iterator ady = adyacentes.begin();
        while (ady != adyacentes.end()){
            salida << "   " <<  *v << "->"  << ady->devolverAdyacente() << " (" << ady->devolverCosto () << ")\n";
            ady++;
        }
        v++;
    }
    return salida;
}


//-----------   R E C O R R I D O S ----------------

int minimo(list<int> vertices, int D[], int solucion[]){
    int valor_minimo = 1000;
    int indice_minimo = 1000;
    list<int>::iterator v = vertices.begin();
    while (v!=vertices.end()){
        if((solucion[*v] == 0) && (D[*v] < valor_minimo)){
            valor_minimo = D[*v];
            indice_minimo = *v;
        }
        v++;
    }
    return indice_minimo;
}



template<typename C>
void dijkstra(GrafoD<C> & grafo,int origen, int distancia[], int predecesor[]){
    int S[grafo.cantidadVertices()+1];
    for(int i=1; i<=grafo.cantidadVertices(); i++)
        S[i]=0;
    S[origen] = 1;
    list<int> vertices;
    grafo.devolverVertices(vertices);
    list<int>::iterator v = vertices.begin();
    while (v!=vertices.end()){
        distancia[*v] = grafo.costoArco(origen, *v);
        if((distancia[*v]!=1000)&&(distancia[*v]!=0))
            predecesor[*v] = origen;
        else
            predecesor[*v] = -1;
        v++;
    }
    for(int i=1; i < grafo.cantidadVertices(); i++){
        int posmin = minimo(vertices, distancia, S);
        S[posmin] = 1;
        list<typename GrafoD<C>::Arco> adyacentes;
        grafo.devolverAdyacentes(posmin, adyacentes);
        typename list<typename GrafoD<C>::Arco>::iterator ady;
        for(ady = adyacentes.begin(); ady != adyacentes.end(); ady++){
            int ady_pos_min = ady->devolverAdyacente();
            if (( S[ady_pos_min] == 0) &&
                (distancia[ady_pos_min] > (grafo.costoArco(posmin, ady_pos_min) + distancia[posmin]) ) ){
                    distancia[ady_pos_min] = (grafo.costoArco(posmin, ady_pos_min) + distancia[posmin]);
                    predecesor[ady_pos_min] = posmin;
            }

        }
    }
}

//-----------------   M A I N  ------------------

int main(int argc, char **argv)
{

	GrafoD<int> g;

	// Cargamos un GrafoDirigido dirigido
	// Primero los vértices
	g.agregarVertice(1);
	g.agregarVertice(2);
	g.agregarVertice(3);
	g.agregarVertice(4);
	g.agregarVertice(5);
	g.agregarVertice(6);
	g.agregarVertice(7);
	g.agregarVertice(8);
	g.agregarVertice(9);
	g.agregarVertice(10);
	g.agregarVertice(11);
	g.agregarVertice(12);

    // Luego los arcos
	g.agregarArco(1, 2, 1);
	g.agregarArco(1, 7, 5);
	g.agregarArco(2, 3, 3);
	g.agregarArco(4, 3, 4);
	g.agregarArco(5, 3, 7);
	g.agregarArco(5, 7, 2);
	g.agregarArco(6, 5, 1);
	g.agregarArco(6, 8, 15);
	g.agregarArco(7, 11, 3);
	g.agregarArco(8, 4, 10);
	g.agregarArco(8, 5, 2);
	g.agregarArco(8, 12, 1);
	g.agregarArco(9, 8, 2);
	g.agregarArco(10, 6, 4);
	g.agregarArco(10, 7, 9);
	g.agregarArco(10, 9, 20);
	g.agregarArco(11, 10, 2);
	g.agregarArco(11, 12, 3);

	int distancia[g.cantidadVertices()+1], predecesor[g.cantidadVertices()+1];
	int origen = 1;

    dijkstra(g, origen, distancia, predecesor);
    int i;
    cout << "arreglo de DISTANCIA[]: " <<endl;
    cout << "-";
    for(i=1; i<=g.cantidadVertices(); i++)
        cout << distancia[i] << "-";
    cout<<endl;
    cout << "arreglo de PRECEDENTES[]: " <<endl;
    for(i=1; i<=g.cantidadVertices(); i++)
        cout << predecesor[i] << "-";

    return 0;
}
