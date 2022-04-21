#ifndef GRAFO_ND_H_INCLUDED
#define GRAFO_ND_H_INCLUDED


#include <list>
#include <map>

using namespace std;

template <typename C> class GrafoND{
public:
	class Arco	{
	public:
		Arco();
		Arco(int adyacente, const C & costo);
		int devolverAdyacente() const;
		const C & devolverCosto() const;
	private:
		int vertice;
		C costo;
	};// class Arco

public:
	// NOTA: Dependiendo de la implementación puede ser necesario incluir otras funciones constructuras
	GrafoND();
	GrafoND(const GrafoND & otroGrafo);
	~GrafoND();
	int nrodeArcos() const;
	GrafoND & operator = (const GrafoND & otroGrafo);
	// Devuelve true si la cantidad de vértices es cero
	bool estaVacio() const;
	// Devuelve la cantidad de vértices del grafo
	int cantidadVertices() const;
	bool existeVertice(int vertice) const;
	bool existeArco(int origen, int destino) const;
	// PRE CONDICION: existeArco(origen, destino)
	const C & costoArco(int origen, int destino) const;
	void devolverVertices(list<int> & vertices) const;
	void devolverAdyacentes(int origen, list<Arco> & adyacentes) const;
	void agregarVertice(int vertice);
	// POST CONDICION: Para todo vértice v != vertice: !existeArco(v, vertice) && !existeArco(vertice, v)
	void eliminarVertice(int vertice);
	// PRE CONDICION: existeVertice(origen) && existeVertice(destino)
	// POST CONDICION: existeArco(origen, destino)
	//return true si se pudo agregar el arco y falso en caso contrario
	bool agregarArco(int origen, int destino, const C & costo);
	// POST CONDICION: !existeArco(origen, destino)
	void eliminarArco(int origen, int destino);
	// PRE CONDICION: existeArco(origen, destino)
	void modificarCostoArco(int origen, int destino, const C & costo);
	void vaciar();
private:
    //Definir la estructura interna
    map<int, map<int, C> > grafo;
    int nroArcos;
};// class Grafo

//Arco
template <typename C>
GrafoND<C>::Arco::Arco(){
}

template <typename C>
GrafoND<C>::Arco::Arco(int adyacente, const C & costo){
    this->vertice = adyacente;
    this->costo = costo;
}

template <typename C>
int GrafoND<C>::Arco::devolverAdyacente() const{
    return vertice;
}

template <typename C>
const C & GrafoND<C>::Arco::devolverCosto() const{
    return costo;
}

//Grafo

template <typename C>
GrafoND<C>::GrafoND(){
    this->nroArcos = 0;
}

template <typename C>
GrafoND<C>::GrafoND(const GrafoND & otroGrafo){
    this->operator=(otroGrafo);
    this->nroArcos = 0;
}

template <typename C>
GrafoND<C>::~GrafoND(){

}

template <typename C>
GrafoND<C>::nrodeArcos() const{
    return nroArcos;
}

template <typename C>
GrafoND<C> & GrafoND<C>::operator = (const GrafoND & otroGrafo){
    grafo.clear();
    typename map<int, map<int, C> >::const_iterator itOtro = otroGrafo.grafo.begin();
    while (itOtro != otroGrafo.grafo.end()){
        grafo[itOtro->first] = itOtro->second;
        itOtro++;
    }
    this->nroArcos = otroGrafo.nrodeArcos();
    return *this;
}

template <typename C>
bool GrafoND<C>::estaVacio() const{
    return (grafo.empty());
}

template <typename C>
int GrafoND<C>::cantidadVertices() const{
    return (grafo.size());
}

template <typename C>
bool GrafoND<C>::existeVertice(int vertice) const{
    return (grafo.find(vertice) != grafo.end());
}

template <typename C>
bool GrafoND<C>::existeArco(int origen, int destino) const{
    bool result = false;
    typename map<int, map<int, C> >::const_iterator itV = grafo.find(origen);
    if (itV != grafo.end()){
        typename map<int, C>::const_iterator itA = itV->second.find(destino);
        if (itA != itV->second.end())
            result = true;
    }
    return result;
}

template <typename C>
const C & GrafoND<C>::costoArco(int origen, int destino) const{
    typename map<int, map<int, C> >::const_iterator itV = grafo.find(origen);
    if ((itV != grafo.end()) && existeVertice(destino)){
        typename map<int, C>::const_iterator itA = itV->second.find(destino);
        if (itA != itV->second.end())
            return (itA->second);
    }
    else
        return -1;
}

template <typename C>
void GrafoND<C>::devolverVertices(list<int> & vertices) const{
    typename map<int, map<int, C> >::const_iterator itV = grafo.begin();
    while (itV != grafo.end()){
        vertices.push_back(itV->first);
        itV++;
    }
}

template <typename C>
void GrafoND<C>::devolverAdyacentes(int origen, list<Arco> & adyacentes) const{
    typename map<int, map<int, C> >::const_iterator itV = grafo.find(origen);
    if (itV != grafo.end()){
        typename map<int, C>::const_iterator itA = itV->second.begin();
        while (itA != itV->second.end()) {
            adyacentes.push_back(Arco(itA->first, itA->second));
            itA++;
        }
    }
}

template <typename C>
void GrafoND<C>::agregarVertice(int vertice){
    if (grafo.find(vertice) == grafo.end()){
        map<int, C> adyacentes;
        grafo[vertice] = adyacentes;
    }
}

template <typename C>
void GrafoND<C>::eliminarVertice(int vertice){
    if (existeVertice(vertice)){
        typename map<int, map<int, C> >::iterator itV = grafo.begin();
        while(itV != grafo.end()){
            if(itV->first == vertice){
                typename map<int, map<int, C> >::iterator aux_itV = itV;
                itV++;
                grafo.erase(aux_itV);
            }
            else{
                typename map<int, C>::iterator itA = itV->second.find(vertice);
                if(itA != itV->second.end())
                    itV->second.erase(itA);
                itV++;
            }
        }
    }
    else
        cout<< "vertice invalido" <<endl;
}

template <typename C>
void GrafoND<C>::modificarCostoArco(int origen, int destino, const C & costo){
    if(existeArco(origen, destino)){
        typename map<int, map<int, C> >::iterator itV = grafo.find(origen);
        itV->second[destino] = costo;
        if(origen>destino)
            itV = grafo.begin();
        itV = grafo.find(destino);
        itV->second[origen] = costo;
    }
    else
        cout << "arco invalido" <<endl;
}

template <typename C>
bool GrafoND<C>::agregarArco(int origen, int destino, const C & costo){
    typename map<int, map<int, C> >::iterator itV = grafo.find(origen);
    if ( (itV != grafo.end() ) && existeVertice(destino)){
        itV->second[destino] = costo;
        this->nroArcos = nroArcos+1;
        if(origen>destino)
            itV = grafo.begin();
        itV = grafo.find(destino);
        itV->second[origen] = costo;
        return true;
        }
    else
        return false;
}

template <typename C>
void GrafoND<C>::eliminarArco(int origen, int destino){
    if(existeArco(origen, destino)){
        typename map<int, map<int, C> >::iterator itV = grafo.find(origen);
        typename map<int, C>::iterator itA = itV->second.find(destino);
        itV->second.erase(itA);
        if(origen>destino)
            itV = grafo.begin();
        itV = grafo.find(destino);
        itA = itV->second.find(origen);
        itV->second.erase(itA);
    }
    else
        cout << "arco invalido" <<endl;
}

template <typename C>
void GrafoND<C>::vaciar(){
    grafo.clear();
    this->nroArcos = 0;

}


#endif // GRAFO_ND_H_INCLUDED
