#ifndef GRAFOD_H_
#define GRAFOD_H_

#include <list>
#include <map>

using namespace std;

template <typename C> class GrafoD{
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
	}; // class Arco

public:
	// NOTA: Dependiendo de la implementación puede ser necesario incluir otras funciones constructuras
	GrafoD();
	GrafoD(const GrafoD & otroGrafo);

	~GrafoD();

	int nrodeArcos() const;

	GrafoD & operator = (const GrafoD & otroGrafo);

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

	void grafoReverso(GrafoD<C> & reverso) ;

	void vaciar();

private:
	/*
	 * Definir la estructura interna
	 */

    map<int, map<int, C> > grafo;
    int nroArcos;
}; // class Grafo


/*
 * Arco
 */

template <typename C> GrafoD<C>::Arco::Arco(){
}

template <typename C> GrafoD<C>::Arco::Arco(int adyacente, const C & costo){
    this->vertice = adyacente;
    this->costo = costo;
}

template <typename C> int GrafoD<C>::Arco::devolverAdyacente() const{
    return vertice;
}

template <typename C> const C & GrafoD<C>::Arco::devolverCosto() const{
    return costo;
}


/*
 * Grafo
 */

template <typename C> GrafoD<C>::GrafoD(){
    this->nroArcos = 0;
}

template <typename C> GrafoD<C>::GrafoD(const GrafoD & otroGrafo){
    this->operator=(otroGrafo);
    this->nroArcos = 0;
}

template <typename C> GrafoD<C>::~GrafoD(){

}

template <typename C> GrafoD<C>::nrodeArcos() const{
    return nroArcos;
}

template <typename C> GrafoD<C> & GrafoD<C>::operator = (const GrafoD & otroGrafo){
    grafo.clear();
    typename map<int, map<int, C> >::const_iterator itOtro = otroGrafo.grafo.begin();
    while (itOtro != otroGrafo.grafo.end()){
        grafo[itOtro->first] = itOtro->second;
        itOtro++;
    }
    this->nroArcos = otroGrafo.nrodeArcos();
    return *this;
}

template <typename C> bool GrafoD<C>::estaVacio() const{
    return (grafo.empty());
}

template <typename C> int GrafoD<C>::cantidadVertices() const{
    return (grafo.size());
}

template <typename C> bool GrafoD<C>::existeVertice(int vertice) const{
    return (grafo.find(vertice) != grafo.end());
}

template <typename C> bool GrafoD<C>::existeArco(int origen, int destino) const{
    bool result = false;
    typename map<int, map<int, C> >::const_iterator itV = grafo.find(origen);
    if (itV != grafo.end()){
        typename map<int, C>::const_iterator itA = itV->second.find(destino);
        if (itA != itV->second.end())
            result = true;
    }
    return result;
}

template <typename C> const C & GrafoD<C>::costoArco(int origen, int destino) const{
    if (existeArco(origen, destino)){
        typename map<int, map<int, C> >::const_iterator itV = grafo.find(origen);
        typename map<int, C>::const_iterator itA = itV->second.find(destino);
        return (itA->second);
    }
    else{
        if(origen == destino)
            return 0;
    }
    return 1000;
}

template <typename C> void GrafoD<C>::devolverVertices(list<int> & vertices) const{
    typename map<int, map<int, C> >::const_iterator itV = grafo.begin();
    while (itV != grafo.end()){
        vertices.push_back(itV->first);
        itV++;
    }
}

template <typename C> void GrafoD<C>::devolverAdyacentes(int origen, list<Arco> & adyacentes) const{
    typename map<int, map<int, C> >::const_iterator itV = grafo.find(origen);
    if (itV != grafo.end()){
        typename map<int, C>::const_iterator itA = itV->second.begin();
        while (itA != itV->second.end()) {
            adyacentes.push_back(Arco(itA->first, itA->second));
            itA++;
        }
    }
}

template <typename C> void GrafoD<C>::agregarVertice(int vertice){
    if (grafo.find(vertice) == grafo.end()){
        map<int, C> adyacentes;
        grafo[vertice] = adyacentes;
    }
}

template <typename C> void GrafoD<C>::eliminarVertice(int vertice){
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

template <typename C> void GrafoD<C>::modificarCostoArco(int origen, int destino, const C & costo){
    if(existeArco(origen, destino)){
        typename map<int, map<int, C> >::iterator itV = grafo.find(origen);
        itV->second[destino] = costo;
    }
    else
        cout << "arco invalido" <<endl;
}

template <typename C> bool GrafoD<C>::agregarArco(int origen, int destino, const C & costo){
    typename map<int, map<int, C> >::iterator itV = grafo.find(origen);
    if ( (itV != grafo.end() ) and existeVertice(destino)){
        itV->second[destino] = costo;
        this->nroArcos = nroArcos+1;
        return true;
        }
    else
        return false;
}

template <typename C> void GrafoD<C>::eliminarArco(int origen, int destino){
    if(existeArco(origen, destino)){
        typename map<int, map<int, C> >::iterator itV = grafo.find(origen);
        typename map<int, C>::iterator itA = itV->second.find(destino);
        itV->second.erase(itA);
    }
    else
        cout << "arco invalido" <<endl;
}

template <typename C>  void GrafoD<C>::grafoReverso(GrafoD<C> & reverso){
    reverso.grafo.clear();
    typename map<int, map<int, C> >::iterator itV = grafo.begin();

    // agrego los vértices a reverso
    while (itV != grafo.end())
        {reverso.agregarVertice(itV->first); cout << "vertice "  << itV->first; itV++;}
    itV = grafo.begin();
    while (itV!= grafo.end())    {
        typename map<int,C>::iterator itA = itV->second.begin();
        while (itA!= itV->second.end())        {
            reverso.agregarArco(  itA->first, itV->first, itA->second);
            itA++;
        }
        itV++;
    }

}

template <typename C> void GrafoD<C>::vaciar(){
    grafo.clear();
    this->nroArcos = 0;

}

#endif /* GRAFOD_H_ */
