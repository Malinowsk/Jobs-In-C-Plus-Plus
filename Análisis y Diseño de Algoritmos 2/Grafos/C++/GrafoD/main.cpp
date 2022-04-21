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

template<typename C>
void BFS2 (GrafoD<C> & g, int origen, char marca[], int padre[], int distancia[]){
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
        list<typename GrafoD<C>::Arco> ady;
        g.devolverAdyacentes(aux, ady);
        typename list<typename GrafoD<C>::Arco>::const_iterator A = ady.begin();
        while (A != ady.end()){
            int adyacente = A->devolverAdyacente();
            if (marca[adyacente] == 'B'){
                    cout << A->devolverAdyacente() << "   dist: " << distancia[aux]+1 << endl;
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
void BFS (GrafoD<C> & g, int origen, char marca[], int padre[], int distancia[]){
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
        list<typename GrafoD<C>::Arco> ady;
        g.devolverAdyacentes(aux, ady);
        typename list<typename GrafoD<C>::Arco>::const_iterator A = ady.begin();
        while (A != ady.end()){
            int adyacente = A->devolverAdyacente();
            if (marca[adyacente] == 'B'){
                    marca[adyacente] = 'G';
                    padre[adyacente] = aux;
                    distancia[adyacente] = distancia[aux] +1;
                    fila.push_back(adyacente);
                    itf = fila.begin();
            }
            A++;
        }
        marca[aux] = 'N';
    }
    for(int h=1; h<=g.cantidadVertices() ; h++){
        cout << "vert " << h << "  "  << padre[h]<< endl;

        cout << "vert " << h << "  "  << distancia[h]<< endl;
        cout << "vert " << h << "  "  << marca[h]<< endl;

    }
}


template<typename C>
void DFS (GrafoD<C> & g, int origen, char marca[], int Padre[], int Tinicio[], int Tfin[], int & tiempo){
// escriba aquí su código
    tiempo = tiempo+1;
    Tinicio[origen] = tiempo;
    marca[origen] = 'G';
    list< typename GrafoD<C>::Arco> ady;
    g.devolverAdyacentes(origen, ady);
    typename list< typename GrafoD<C>::Arco>::iterator A = ady.begin();
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
void Forest2 (GrafoD<C> & g){
// escriba aquí su código
    int Padre[g.cantidadVertices() +1], distancia[g.cantidadVertices() +1];
    char marca[g.cantidadVertices() +1];
    for(int i=1; i<=g.cantidadVertices(); i++){
        marca[i]= 'B';
        Padre[i]= 0;
        distancia[i] = 0;
    }

    list<int> vertices;
    g.devolverVertices(vertices);
    list<int>::iterator v = vertices.begin();
    BFS(g, *v, marca, Padre, distancia);
    }
    /*
    int i;
    cout << "arreglo [marcas]: " << endl;
    for(i = 1; i<=g.cantidadVertices(); i++)
        cout << marca[i] << "-";
    cout <<endl;
    if (tipo == 'D'){
        cout << "arreglo [tiempo inicial]: " << endl;
        for(i = 1; i<=g.cantidadVertices(); i++)
            cout << Tinicio[i] << "-";
        cout <<endl;
        cout << "arreglo [tiempo final]: " << endl;
        for(i = 1; i<=g.cantidadVertices(); i++)
            cout << Tfin[i] << "-";
        cout<<endl;
    }
    cout << "arreglo [Padre]: " << endl;
    for(i = 1; i<=g.cantidadVertices(); i++)
        cout << Padre[i] << "-";
    cout <<endl;
    if (tipo == 'B'){
        cout << "arreglo [Distancia]: " << endl;
        for(i = 1; i<=g.cantidadVertices(); i++)
            cout << distancia[i] << "-";
    }
    */


template<typename C>
void DFS_Forest (GrafoD<C> & g){
// escriba aquí su código
    int Padre[g.cantidadVertices() +1], Tinicio[g.cantidadVertices() +1], Tfin[g.cantidadVertices() +1];
    char marca[g.cantidadVertices() +1];
    for(int i=1; i<=g.cantidadVertices(); i++){
        marca[i]= 'B';
        Padre[i]= 0;
    }                                                       //0=blanco
    int tiempo=0;                                           //1=gris
                                                            //2=negro
    list<int> vertices;
    g.devolverVertices(vertices);
    list<int>::iterator v = vertices.begin();
    while (v != vertices.end()){
        if (marca[*v]== 'B')
            DFS(g, *v, marca, Padre, Tinicio, Tfin, tiempo);
        v++;
    }

}


template<typename C>
void DFS3 (GrafoD<C> & g, int origen, int v2, char marca[], int Padre[],  list<int> & lista ){

    marca[origen] = 'G';
    list< typename GrafoD<C>::Arco> ady;
    g.devolverAdyacentes(origen, ady);
    typename list< typename GrafoD<C>::Arco>::iterator A = ady.begin();
    while (A != ady.end()){
        if( A->devolverAdyacente() == v2){
            list<int>::iterator v = lista.begin();
            lista.push_back(v2);
            //agregar a la lsta
            //mprr lsta

            while (v != lista.end()){
                cout <<  *v << "   " ;
                v++;
            }
            cout << "costo ----> "<< lista.size() - 1 ;
            lista.remove(v2);

            cout << " " << endl;

        }
        else{
            if (marca[A->devolverAdyacente()] == 'B'){
            lista.push_back(A->devolverAdyacente());
            Padre[A->devolverAdyacente()] = origen;
            DFS3(g, A->devolverAdyacente(), v2, marca, Padre , lista);
            lista.remove(A->devolverAdyacente());
            marca[A->devolverAdyacente()] = 'B';
        }
        }
        A++;
    }



}


template<typename C>
void caminos (GrafoD<C> & g){
// escriba aquí su código
    int Padre[g.cantidadVertices() +1] ;
    char marca[g.cantidadVertices() +1];
    for(int i=1; i<=g.cantidadVertices(); i++){
        marca[i]= 'B';
        Padre[i]= 0;
    }                                                       //0=blanco
    int v1, v2;

    cin >> v1  ;
    cin >> v2  ;                                         //1=gris

     list<int> lista ;


     lista.push_back(v1);


           DFS3(g, v1, v2, marca, Padre, lista);


}


int pos_Min(int solucion[], int menor_costo[], int cantidad_vertices)
{
    int w = 111111 ;
    int pos_w = 0;
    for (int i=2;i<=cantidad_vertices;i++){
        if ( (solucion[i]==0) && (w>menor_costo[i] ) )
            {
            w=menor_costo[i];
            pos_w=i;
            }

    }
    return pos_w;
}

template<typename C>
void prim (GrafoD<C> & g){

    int menor_costo[g.cantidadVertices()+1], mas_cercano[g.cantidadVertices()+1], solucion[g.cantidadVertices()+1];
    int cantidad_vertices = g.cantidadVertices();

    int infinito = 111111 ;

    for (int i=1 ; i<=cantidad_vertices ; i++){  // inicializacion.
        solucion[i]=0;
        menor_costo[i]=infinito;
        mas_cercano[i]=-1;

    }

    solucion[1]=1;

    for (int i=2; i <= cantidad_vertices ;i++){

    if ( g.existeArco(1,i)== true) {
        menor_costo[i] = g.costoArco(1,i);
    }
        mas_cercano[i] = 1;

    }

    for (int i=2; i<=cantidad_vertices ; i++){

        int w = pos_Min(solucion,menor_costo, cantidad_vertices);
        solucion[w]=1;
        for (int j=2;j<=cantidad_vertices;j++){
            if( (solucion[j]==0) && ( g.existeArco(w,j)== true) &&  (g.costoArco(w,j)<menor_costo[j])){
                menor_costo[j]=g.costoArco(w,j);
                mas_cercano[j]=w;
            }

        }

    }

     for (int z=1 ; z<=cantidad_vertices ; z++){
        cout << "posicion " << z ;
        cout << "   conjunto solucion " << solucion[z] ;
        cout << "   menor costo " << menor_costo[z] ;
        cout << "   mas cercano " << mas_cercano[z] << endl;

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


    // Luego los arcos
	g.agregarArco(1, 2, 6);
	g.agregarArco(1, 4, 5);
	g.agregarArco(2, 5, 3);
	g.agregarArco(2, 3, 5);
	g.agregarArco(1, 3, 1);
	g.agregarArco(3, 4, 5);
	g.agregarArco(5, 3, 6);
	g.agregarArco(5, 6, 6);
	g.agregarArco(6, 3, 4);
	g.agregarArco(6, 4, 2);


	cout << "numero de arcos: " << g.nrodeArcos() <<endl;

    //prim(g);




    int n = g.cantidadVertices();
//   int costo [n+1][n+1];

//   int padres [n+1][n+1];

//    void floyd(g,costo ,padres,n);

    int v1,v2;
    cin >> v1;
    cin >> v2;

    //void recuperar_camino(costo, padre, v1, v2);

   Forest2(g);
    return 0;
}
