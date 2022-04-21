#ifndef GRAFO_H_
#define GRAFO_H_

#include <list>
#include <map>

using namespace std;

template <typename C> class Grafo
{
public:
	class Arco
	{
	public:
		Arco(int adyacente, const C & costo);
		int devolver_adyacente() const;
		const C & devolver_costo() const;
	private:
		int vertice;
		C costo;
	}; // class Arco
public:
	// NOTA: Dependiendo de la implementaci�n puede ser necesario incluir otras funciones constructuras
	Grafo();
	Grafo(const Grafo & otroGrafo);

	~Grafo();

	Grafo & operator = (const Grafo & otroGrafo);

	// Devuelve true si la cantidad de v�rtices es cero
	bool esta_vacio() const;
	// Indica la cantidad de v�rtices del grafo
	int devolver_longitud() const;

	bool existe_vertice(int vertice) const;

	bool existe_arco(int origen, int destino) const;

	// PRE CONDICION: existe_arco(origen, destino)
	const C & costo_arco(int origen, int destino) const;

	void devolver_vertices(list<int> & vertices) const;

	void devolver_adyacentes(int origen, list<Arco> & adyacentes) const;

	void agregar_vertice(int vertice);

	// POST CONDICION: Para todo v�rtice v != vertice: !existeArco(v, vertice) && !existeArco(vertice, v)
	void eliminar_vertice(int vertice);

	// PRE CONDICION: existeArco(origen, destino)
	void modificar_costo_arco(int origen, int destino, const C & costo);

	// PRE CONDICION: existeVertice(origen) && existeVertice(destino)
	// POST CONDICION: existeArco(origen, destino)
	void agregar_arco(int origen, int destino, const C & costo);

	// POST CONDICION: !existeArco(origen, destino)
	void eliminar_arco(int origen, int destino);

	void vaciar();

private:

	// * Definir la estructura interna


    //Algunas alternativas vistas en la presentaci�n.
   /* struct Vertice {
        int v;
        list<Arco> adyacentes;
    };*/

    //list<Vertice> vertices;
    map<int, list<Arco> > vertices;
}; // class Grafo


/*
 * Arco
 */

template <typename C> Grafo<C>::Arco::Arco(int adyacente, const C & costo)
{
    vertice = adyacente;
    this->costo = costo;
}

template <typename C> int Grafo<C>::Arco::devolver_adyacente() const
{
    return vertice;
}

template <typename C> const C & Grafo<C>::Arco::devolver_costo() const
{
    return costo;
}


/*
 * Grafo
 */

template <typename C> Grafo<C>::Grafo()
{

}

template <typename C> Grafo<C>::Grafo(const Grafo & otroGrafo)
{

}

template <typename C> Grafo<C>::~Grafo()
{

}

template <typename C> Grafo<C> & Grafo<C>::operator = (const Grafo & otroGrafo)
{

    return *this;
}

template <typename C> bool Grafo<C>::esta_vacio() const
{
    typename map<int, map<int,C> >::const_iterator it = vertices.begin();
    if (it != vertices.end() )
        return false;
    return true;
}

template <typename C> int Grafo<C>::devolver_longitud() const
{
    int Cant=0;
    typename map<int, list<Arco> >::const_iterator it= vertices.begin();
    for (it ; it != vertices.end(); it++)
        Cant++;
    return Cant;
}

template <typename C> bool Grafo<C>::existe_vertice(int vertice) const
{
    typename map<int, list<Arco> >::const_iterator itV = vertices.find(vertice);
    if ( itV != vertices.end() )
        return true;
    return false;
}

template <typename C> bool Grafo<C>::existe_arco(int origen, int destino) const
{
    bool existe = false;

    //Algunas implementaciones de referencia de acuerdo a la estructura elegida.

    /*typename list<Vertice>::const_iterator itV = vertices.begin();
    while ((itV != vertices.end()) && !existe) {
        if (itV->v == origen) {
            typename list<Arco>::const_iterator itA = itV->adyacentes.begin();
            while ((itA != itV->adyacentes.end()) && !existe) {
                if (itA->devolver_adyacente() == destino)
                    existe = true;
            itA++;
            }
        }
        itV++;
    }*/

    typename map<int, list<Arco> >::const_iterator itV = vertices.find(origen);
    if (itV != vertices.end()) {
        typename list<Arco>::const_iterator itA = itV->second.begin();
        while((itA != itV->second.end()) && !existe) {
                if (itA->devolver_adyacente() == destino)
                    existe = true;
            itA++;
        }
    }

    /*
    typename map<int, map<int, C> >::const_iterator itV = vertices.find(origen);
    if (itV != vertices.end()) {
        typename map<int, C>::const_iterator itA = itV->second.find(destino);
        if (itA != itV->second.end())
            existe = true;
    }*/

    return existe;
}

template <typename C> const C & Grafo<C>::costo_arco(int origen, int destino) const
{
    typename map<int, list<Arco> >::const_iterator itV = vertices.find(origen);
    if (itV != vertices.end()) {
        typename list<Arco>::const_iterator itA = itV->second.begin();
        bool encontrado;
        while((itA != itV->second.end()) && !encontrado) {
                if (itA->devolver_adyacente() == destino)
                    return itA->devolver_costo();
            itA++;
        }
    }
}

template <typename C> void Grafo<C>::devolver_vertices(list<int> & vertices) const
{
    typename map<int, list<Arco> >::const_iterator it = this->vertices.begin();
    for  (it=this->vertices.begin(); it != this->vertices.end(); it++)
        vertices.push_back(it->first);
}

template <typename C> void Grafo<C>::devolver_adyacentes(int origen, list<Arco> & adyacentes) const
{
    typename map<int, list<Arco> >::const_iterator itV = vertices.find(origen);
    if (itV != vertices.end())
        adyacentes = vertices->second;
}

template <typename C> void Grafo<C>::agregar_vertice(int vertice)
{
    vertices[vertice];
}

template <typename C> void Grafo<C>::eliminar_vertice(int vertice)
{
    vertices.erase(vertice);
}

template <typename C> void Grafo<C>::modificar_costo_arco(int origen, int destino, const C & costo)
{
   /* if (existe_arco(origen,destino)) {
        bool encontrado=false;
        typename map<int, list<Arco> >::iterator itV= vertices.find(origen);
        list<Arco> lista=itV->second;
        typename list<Arco> ::iterator itA= lista.begin();
        while((itA != lista.end()) && !encontrado) {
                if (itA->devolver_adyacente() == destino){
                    encontrado = true;
                    lista.erase(itA);
                }
            itA++;
        }
    }*/
}

template <typename C> void Grafo<C>::agregar_arco(int origen, int destino, const C & costo)
{
    if (existe_vertice(origen)) {
        typename map<int, list<Arco> >::const_iterator it= vertices.find(origen);
        list<Arco> lista=it->second;
        lista.push_back(Arco(destino,costo));
        vertices[it->first]=lista;
    }
}

template <typename C> void Grafo<C>::eliminar_arco(int origen, int destino)
{
    if (existe_arco(origen,destino)) {
        bool encontrado=false;
        typename map<int, list<Arco> >::iterator itV= vertices.find(origen);
        list<Arco> lista=itV->second;
        typename list<Arco> ::iterator itA= lista.begin();
        while((itA != lista.end()) && !encontrado) {
                if (itA->devolver_adyacente() == destino){
                    encontrado = true;
                    lista.erase(itA);
                }
            itA++;
        }
        vertices[itV->first]=lista;
    }
}

template <typename C> void Grafo<C>::vaciar()
{
    vertices.clear();
}

#endif /* GRAFO_H_ */
