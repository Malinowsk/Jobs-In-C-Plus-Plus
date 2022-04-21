 #include <iostream>
#include "grafo ND.h"

using namespace std;

template<typename C>
ostream & operator << (ostream & salida, const GrafoND<C> & Grafo){
    // Recorremos todos los vertices
    list<int> vertices;
    Grafo.devolverVertices(vertices);
    list<int>::iterator v = vertices.begin();
    while (v != vertices.end()){
        salida << "    " << *v << "\n";
        // Recorremos todos los adyacentes de cada vertice
        list< typename GrafoND<C>::Arco> adyacentes;
        Grafo.devolverAdyacentes(*v, adyacentes);
        typename list< typename GrafoND<C>::Arco>::iterator ady = adyacentes.begin();
        while (ady != adyacentes.end()){
            salida << "   " <<  *v << "->"  << ady->devolverAdyacente() << " (" << ady->devolverCosto () << ")\n";
            ady++;
        }
        v++;
    }
    return salida;
}


//-----------   R E C O R R I D O S ----------------

template<typename C>
void BFS (GrafoND<C> & g, int origen, char marca[], int padre[], int distancia[]){
    marca[origen] = 'G';
    distancia[origen] =0;
    padre[origen] =0;
    list<int> fila;
    fila.push_back(origen);
    typename list<int>::iterator itf = fila.begin();
    int aux;
    while (itf != fila.end()){
        aux = *itf;
        itf++;
        fila.erase(fila.begin());
        list<typename GrafoND<C>::Arco> ady;
        g.devolverAdyacentes(aux, ady);
        typename list<typename GrafoND<C>::Arco>::const_iterator A = ady.begin();
        while (A != ady.end()){
            int adyacente = A->devolverAdyacente();
            if (marca[adyacente] == 'B'){
                marca[adyacente] = 'G';
                padre[adyacente] = aux;
                distancia[adyacente] = distancia[aux] +1;
                if (itf == fila.end())
                    fila.clear();
                fila.push_back(adyacente);
                itf = fila.begin();
            }
            A++;
        }
        marca[aux] = 'N';
    }
}

template<typename C>
void DFS (GrafoND<C> & g, int origen, char marca[], int Padre[], int Tinicio[], int Tfin[], int & tiempo){
    tiempo = tiempo+1;
    Tinicio[origen] = tiempo;
    marca[origen] = 'G';
    list< typename GrafoND<C>::Arco> ady;
    g.devolverAdyacentes(origen, ady);
    typename list< typename GrafoND<C>::Arco>::iterator A = ady.begin();
    while (A != ady.end()){
        if (marca[A->devolverAdyacente()] == 'B'){
            Padre[A->devolverAdyacente()] = origen;
            DFS(g, A->devolverAdyacente(), marca, Padre, Tinicio, Tfin, tiempo);
        }
        A++;
    }
    marca[origen] = 'N';
    tiempo = tiempo+1;
    Tfin[origen] = tiempo;
}

template<typename C>
void Forest (GrafoND<C> & g, char tipo, int Padre[], int Tinicio[], int Tfin[], int distancia[], char marca[]){
    for(int i=1; i<=g.cantidadVertices(); i++){
        marca[i]= 'B';
        Padre[i]= 0;
        distancia[i] = 0;
    }                                                       //0=blanco
    int tiempo=0;                                           //1=gris
                                                            //2=negro
    list<int> vertices;
    g.devolverVertices(vertices);
    list<int>::iterator v = vertices.begin();
    while (v != vertices.end()){
        if (marca[*v]== 'B'){
            if (tipo == 'D')
                DFS(g, *v, marca, Padre, Tinicio, Tfin, tiempo);
            else
                BFS(g, *v, marca, Padre, distancia);
        }
        v++;
    }
}

/* //algoritmo de PRIM ******proximamente******
template<typename C>
void Prim(GrafoD<C> & g, GrafoD<C> &h){
    typename GrafoD<C>::Arco minimo();
    arco min;
    list<int> soluciones, vertices;
    vertices = g.devolverVertices();
    vertices.push_back(vertices.front()); //vertices.front() = elemento[arco]
    vertices.pop_front(); //Elimina el primero de la lista ->front()
    list<int>::iterator its;
    list<int>::iterator itv;
    while (!vertices.empty()){
        minimo->costo() = -1;
        for(its = soluciones.begin(); its != soluciones.end(); its++)
            for(itv = vertices.begin(); itv != vertices.end(); itv++)
                if (g.costo_entre(*its,*itv) < min.costo){
                    min.costo = g.costo_entre(*its,*itv);
                    min.origen = *its;
                    min.destino = *itv;
                }
                soluciones.push_back(min.destino);
                vertices.remove(min.destino);
                h.agregar_arco(min.origen,min.destino,min.costo);
    }
}
*/

//-----------------   M A I N  ------------------

int main(int argc, char **argv)
{

	GrafoND<int> g;

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

	cout << g;

    return 0;
}
