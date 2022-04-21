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

struct arco{
    int origen;
    int destino;
    int costo;
};

void insertar_ordenado(list<arco*> &fila, arco *nuevo){
    list<arco*>::iterator it = fila.begin();
    while((it != fila.end())&&((*it)->costo)<(nuevo->costo))
        it++;
    fila.insert(it, 1, nuevo);
}

template<typename C>
void lista_adyacentes(GrafoD<C> &grafo, list<int> &adyacentes, int origen){
    adyacentes.clear();
    list<typename GrafoD<C>::Arco> A;
    grafo.devolverAdyacentes(origen, A);
    typename list<typename GrafoD<C>::Arco>::iterator itA = A.begin();
    while(itA != A.end()){
        adyacentes.push_back(itA->devolverAdyacente());
        itA++;
    }
}

template<typename C>
void cargar_fila(GrafoD<C> &grafo, list<arco*> &fila){
    list<int> adyacentes;
    list<int>::iterator it;
    for(int i=1; i<= grafo.cantidadVertices(); i++){
        lista_adyacentes(grafo, adyacentes, i);
        for(it = adyacentes.begin(); it != adyacentes.end(); it++){
            arco *nuevo = new arco;
            nuevo-> origen = i;
            nuevo-> destino = *it;
            nuevo-> costo = grafo.costoArco(i, *it);
            insertar_ordenado(fila, nuevo);
        }
    }
}

void agregar_arco(list<arco*> &A, int orig, int dest, int cost){
    arco *nuevo = new arco;
    nuevo-> origen = orig;
    nuevo-> destino = dest;
    nuevo -> costo = cost;
    A.push_back(nuevo);
}

template<typename C>
void kruskal(GrafoD<C> &grafo, GrafoD<C> &H){
    list<arco*> fila;

    cargar_fila(grafo, fila);
    int contador = 0;
    while(contador < (grafo.cantidadVertices()-1)){
        int origen = fila.front()->origen;
        int destino = fila.front()->destino;
        int costo = fila.front()->costo;
        fila.pop_front();
        if(H.hay_camino(origen, destino) = false){ //existe_camino
            H.agregarArco(origen, destino, costo);
            contador = contador ++;
        }
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
}*/

//-----------------   M A I N  ------------------

int main(int argc, char **argv)
{

	GrafoD<int> g;
	GrafoD<int> h;

	// Cargamos un GrafoDirigido dirigido
	// Primero los vértices
	g.agregarVertice(1);
	g.agregarVertice(2);
	g.agregarVertice(3);
	g.agregarVertice(4);
    g.agregarVertice(5);

    h.agregarVertice(1);
	h.agregarVertice(2);
	h.agregarVertice(3);
	h.agregarVertice(4);
    h.agregarVertice(5);

    // Luego los arcos
	g.agregarArco(1, 2, 3);
	g.agregarArco(1, 3, 5);
	g.agregarArco(1, 4, 6);
	g.agregarArco(1, 5, 4);
	g.agregarArco(2, 3, 5);
	g.agregarArco(2, 4, 6);
	g.agregarArco(2, 5, 7);
	g.agregarArco(3, 4, 4);
	g.agregarArco(3, 5, 7);
	g.agregarArco(4, 5, 3);

    cout <<h;
    kruskal(g, h);
    if(h.hay_camino(5, 4) = false)
        cout <<"existe camino"<<endl;
    cout <<h;

    return 0;
}
