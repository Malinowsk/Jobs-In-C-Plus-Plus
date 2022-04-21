#include <iostream>
#include "GrafoDirigido.h"
#include "GrafoNDirigido.h"
#include <list>
#include <queue>
#include "UNIONFIND.h"
#include <set>
#include "HeapModificado.h"
#include "Heap.h"
#include "time.h"

using namespace std;



const int INFINITO = INT_MAX - 100000;
const int DISCERNIBLE = -1;
const int CANT_POSICIONES = 4;

struct infoDFS {
    char estado;
    int inicioVisita;
    int finVisita;
    int predecesor;
};

struct celdaLaberinto{
    bool visitado = false;
    bool paredes[CANT_POSICIONES];
};


///////////////////////////////////////////   Grafos ///////////////////////////////////////////////////

void cargarGrafoD(GrafoDirigido & grafoD);
void cargarGrafoN(GrafoNDirigido & grafoN);

//Primera versión sin considerar el tiempo con Grafo No Dirigido
void DFS_ND(GrafoNDirigido grafoN , int fuente , char visitados []);
void bosqueDFS_ND (GrafoNDirigido grafoN );

//Segunda versión considerando el tiempo y predecesor con Grafo Dirigido



void DFS_D(GrafoDirigido grafoD , int fuente , int & tiempo , infoDFS arr[]);
void bosqueDFS_D(GrafoDirigido grafoD , infoDFS arr[]);

//Primer versión BFS
void BFS_f(GrafoDirigido grafoD , int fuente , char estado[]);
void bosqueBFS_f(GrafoDirigido grafoD);

//Excentricidad en un Grafo DFS
int DFS_excentricidadGrafo(GrafoNDirigido grafoN);


//Excentricidad en un Grafo BFS
int BFS_excentricidadGrafo(GrafoNDirigido grafoN);

//Clasificacion de arcos
void DFS_clasificacion (GrafoDirigido grafoD , int fuente, infoDFS arr[] , int & t);

//Clasificación de aristas
void DFS_aristas (GrafoNDirigido grafoN , int fuente , infoDFS arr[] , int & tiempo);
void bosqueDFS_aristas (GrafoNDirigido grafoN , infoDFS arr[]);

//Numeración Post-Orden
void DFS_postOrden (GrafoDirigido grafoD , int fuente, char estado[] , int postOrden[] , int & num);
void numeracionPostOrden (GrafoDirigido grafoD , int postOrden[]);

//Numeración Pre-Orden
void DFS_preOrdenGD (GrafoDirigido grafoD , int fuente, char estado[] , int preOrden[] , int & num);
void numeracionPreOrdenGD (GrafoDirigido grafoD , int preOrden[]);



//Test de Aciclicidad
bool esAciclico (GrafoDirigido grafoD);

//Sort Topológico
void sortTopologico(GrafoDirigido grafoD, int fuente , char estado[] , list<int> & l);
list<int> bosqueSortTopologico (GrafoDirigido grafoD);

//Puntos de Articulación
void DFS_preOrdenGND (GrafoNDirigido grafoN , int fuente, char estado[] , int * preOrden , int * masAlto, int & num);
void puntosArticulacion(GrafoNDirigido grafoN, int i);

//Componentes Fuertemente Conectadas
list< list<int> > componentesFC (GrafoDirigido grafoD);
void DFS_CFC ( GrafoDirigido grafoD , int fuente , char estado[] , list<int> & verticesPostOrden , GrafoDirigido & grafoDR);

//Componentes Conexas - Versión DFS
list< list<int> > componentesConexas (GrafoNDirigido grafoN);
void DFS_CC ( GrafoNDirigido grafoN , int fuente , list<int> & componente , char estado[]);

//Componentes Conexas - Versión UNION-FIND
UNIONFIND compConexas (GrafoNDirigido);

//Caminos Mínimos - Dijkstra
void Dijkstra ( GrafoDirigido grafoD , int fuente);
void DijkstraH ( GrafoDirigido grafoD , int fuente);

//Caminos Mínimos - Floyd
void Floyd ( GrafoDirigido grafoD , int**a , int**p);
void caminoFloyd( int**p , int i , int j);
void Warshall ( GrafoDirigido grafoD , bool**a );

//Árbol de Recubrimiento de Mínimo Costo
void Prim ( GrafoNDirigido grafoN , int inicio);
list < pair<int,int> > PrimH (GrafoNDirigido grafoN , int inicio);
void Kruskal (GrafoNDirigido grafoN);

///////////////////////////////////////////   Problemas NP ///////////////////////////////////////////////////
//////////Algoritmos Aproximados/////////////////

set<int> VertexCoverAprox ( GrafoNDirigido grafoN);
set<int> TSPMetricoAprox( GrafoNDirigido grafoN , int inicio); //No funciona
set< set<int> > SetCoveringAprox ( set<int> tareas , set<set<int>> subconjuntos);
///Bin Packing
list <pair<float,set<float>>> nextFit(  list<float> objetos  );
list <pair<float,set<float>>> firstFit(  list<float> objetos  );
list <pair<float,set<float>>> bestFit(  list<float> objetos  );

//////////Algoritmos Heurísticos/////////////////
int*coloreoGrafoHeuristico (GrafoNDirigido grafoN);
set < pair<int,int> > TSPHeuristico (GrafoNDirigido grafoN, int inicio);

//////////Backtracking/////////////////
void backNReinas(int**costos,int*solucion,int*solucionActual,int& cota,int costoActual,int fila,int N);
void backLaberinto (celdaLaberinto*laberinto , bool & solucion , int N , int entrada, int salida );
void backSetCovering (set<int> & solucion , set<int> personas , bool**asignacion , set<int> tareas ,
                      int& cota, int numPersona , int T , int P );

void backColoreoGrafo (GrafoNDirigido grafoN ,int* solucion,int vertice,int C,int cantVertices,bool& fin );
void backAsignacionTareas (int* tareas , int* procesadores , list<int>& solucion, list<int> solucionActual,
                           int numTarea , int& cota , int P , int T);

int main() {

///////////////////////////////////////////   Grafos ///////////////////////////////////////////////////

    GrafoDirigido grafoD;
    GrafoNDirigido grafoN;

    //cargarGrafoN(grafoN);
    int numVerticesGND = grafoN.cantVertices();
    //cargarGrafoD(grafoD);
    int numVerticesGD = grafoD.cantVertices();

    /*    //////////////////////Testing Grafo Dirigido/////////////////////////////////////////////

    grafo.agregarArco(0,1,10);
    grafo.agregarArco(0,3,30);
    grafo.agregarArco(0,4,100);
    grafo.agregarArco(1,2,50);
    grafo.agregarArco(2,4,10);
    grafo.agregarArco(3,2,20);
    grafo.agregarArco(3,4,60);


    int vertAdy;
    cout << "Ingrese un vertice para determinar sus adyacentes"<<endl;
    cin>> vertAdy;
    list<GrafoDirigido::Nodo> ady = grafo.adyacentes(vertAdy);
    list<GrafoDirigido::Nodo>::const_iterator it;
    cout << "Los adyacentes de "<< vertAdy << " son: ";
    for ( it = ady.cbegin(); it!= ady.cend(); it++)
        cout << it->vertice << " ";
    cout<<endl;

    if(grafo.existeArco(3,1))
        cout <<"Existe arco";
    */

    /*//////////////////////////////////7Testing Grafo No Dirigido////////////////////////////////////

    int vertAdy;
    cout << "Ingrese un vertice para determinar sus adyacentes"<<endl;
    cin>> vertAdy;
    list<int> ady = grafoN.adyacentes(vertAdy);
    list<int>::const_iterator it;
    cout << "Los adyacentes de "<< vertAdy << " son: ";
    for ( it = ady.cbegin(); it!= ady.cend(); it++)
        cout << *it << " ";
    cout<<endl;

    if(grafoN.existeArista(3,1))
        cout <<"Existe arco";
    */

    /*    ///////////////////////////////////////////DFS Primera versión/////////////////////////////////////////////
    bosqueDFS_ND(grafoN);*/

    /* //////////////////////////// DFS segunda versión /////////////////////////////////////////////////////

    infoDFS arr[numVerticesGD];
    bosqueDFS_D(grafoD,arr);
    for(int i = 0 ; i < numVerticesGD ; i++){
        cout<< "Vertice "<< i << " :"<<endl;
        cout<< "    Inicio: "<<arr[i].inicioVisita<<endl;
        cout<< "    Fin: "<<arr[i].finVisita<<endl;
        cout<< "    Predecesor: ";
        if(arr[i].predecesor != -1)
          cout << " "<<arr[i].predecesor<<endl;
        else
            cout<< "No tiene predecesor"<<endl;
        cout<<"......................."<<endl;
    }
    */

    /*//////////////////////////////////// BFS Primera Version ///////////////////////////////////////////////////
    bosqueBFS_f(grafoD);
    */

    ////////////////////////////////// Excentricidad de un Grafo //////////////////////////////////////////////
    //cout << "El grado de excentricidad del Grafo es: "<< DFS_excentricidadGrafo(grafoN) << endl;
    //cout << "El grado de excentricidad del Grafo es: "<< BFS_excentricidadGrafo(grafoN) << endl;


    ////////////////////////////////////Clasificacion de arcos////////////////////////////////////////////////
    /*
    infoDFS arr[numVerticesGD];
    for(int i = 0 ; i < numVerticesGD; i++){
        arr[i].estado = 'N';
        arr[i].inicioVisita = INFINITO;
        arr[i].finVisita = INFINITO;
    }
    int tiempo = 1;
    DFS_clasificacion(grafoD,0,arr,tiempo);
    cout<<"........................................."<<endl;
    for(int i = 0 ; i < numVerticesGD ; i++){
        cout<< "Vertice "<< i << " :"<<endl;
        cout<< "    Inicio: "<<arr[i].inicioVisita<<endl;
        cout<< "    Fin: "<<arr[i].finVisita<<endl;

    }
    */

    ///////////////////////////////////Clasificacion de aristas////////////////////////////////////////////////

    /*infoDFS arr[numVerticesGND];
    for(int i = 0 ; i < numVerticesGND; i++){
        arr[i].estado = 'N';
        arr[i].inicioVisita = INFINITO;
        arr[i].finVisita = INFINITO;
        arr[i].predecesor = -1;
    }

    bosqueDFS_aristas(grafoN,arr);
    for(int i = 0 ; i < numVerticesGND ; i++){
        cout<< "Vertice "<< i << " :"<<endl;
        cout<< "    Inicio: "<<arr[i].inicioVisita<<endl;
        cout<< "    Fin: "<<arr[i].finVisita<<endl;

    }*/


     ///////////////////////////////////Numeración Post Orden/////////////////////////////
     /*int postOrden[grafoD.cantVertices()] ;
     numeracionPostOrden(grafoD,postOrden);
     for (int i = 0; i < grafoD.cantVertices() ; i++)
         cout<<"Vertice "<< i << " : " << postOrden[i] <<endl;
     cout<<endl;*/

    ///////////////////////////////////Numeración Pre Orden/////////////////////////////
    /*int preOrden[grafoD.cantVertices()] ;
    numeracionPreOrdenGD(grafoD,preOrden);
    for (int i = 0; i < grafoD.cantVertices() ; i++)
        cout<<"Vertice "<< i << " : " << preOrden[i] <<endl;
    cout<<endl;*/

    //////////////////////////////////Test de Aciclicidad/////////////////////////////////
    /*if ( esAciclico(grafoD))
        cout<<"El grafo no tiene ciclos"<<endl;
    else
        cout<<"El grafo tiene ciclos"<<endl;*/

    //////////////////////////////////Sort Topológico/////////////////////////////////

    /*list<int> ordTopologico = bosqueSortTopologico(grafoD);
    list<int>::const_iterator iterador;
    cout<<"El ordenamiento topologico es: "<<endl;
    for (iterador = ordTopologico.cbegin() ; iterador != ordTopologico.cend() ; iterador++)
        cout<< *iterador << "-" ;*/

    ///////////////////////////////Puntos de Articulación///////////////////////////////////

    //puntosArticulacion(grafoN, 4);

    ///////////////////////////////Componentes Fuertemente Conectadas///////////////////////////////////

    /*list< list<int> > lComponentes = componentesFC(grafoD);

    list< list<int> >::const_iterator itCompS ;
    for (itCompS = lComponentes.cbegin() ; itCompS != lComponentes.cend() ; itCompS++){
        list<int>::const_iterator itComp;
        for(itComp = (*itCompS).cbegin() ; itComp != (*itCompS).cend() ; itComp++)
            cout<< *itComp <<"-";
        cout<<"........................."<<endl;
    }
    */

    ///////////////////////////////Componentes Conexas - DFS ///////////////////////////////////

    /*list< list<int> > lcompConexas = componentesConexas(grafoN);
    list< list<int> >::const_iterator itCompS ;
    for (itCompS = lcompConexas.cbegin() ; itCompS != lcompConexas.cend() ; itCompS++){
        list<int>::const_iterator itComp;
        for(itComp = (*itCompS).cbegin() ; itComp != (*itCompS).cend() ; itComp++)
            cout<< *itComp <<"-";
        cout<<"........................."<<endl;
    }
     */

    ///////////////////////////////Componentes Conexas - UNION-FIND ///////////////////////////////////

    //compConexas(grafoN).mostrar();

    /////////////////////////////// Caminos Mínimos - Algoritmo de Dijkstra ///////////////////////////
    //Dijkstra(grafoD,0);
    /////////////////////////////// Caminos Mínimos - Algoritmo de Dijkstra con Heap///////////////////////////
    //DijkstraH(grafoD,0);

    /////////////////////////////// Caminos Mínimos - Algoritmo de Floyd ///////////////////////////
    /*int** a = new int*[numVerticesGD];
    int** p = new int*[numVerticesGD];
    for (int i = 0 ; i < numVerticesGD ; i++){
        a[i] = new int[numVerticesGD];
        p[i] = new int[numVerticesGD];
    }

    for (int i = 0 ; i < numVerticesGD ; i++)
        for(int j = 0 ; j < numVerticesGD ; j++){
            p[i][j] = -1;
            if ( i == j)
                a[i][j] = 0;
            else
                a[i][j] = INFINITO;
        }


    Floyd(grafoD,a,p);
    cout<<"La matriz de caminos mínimos queda: "<<endl;
    for ( int i = 0 ; i < numVerticesGD ; i++){
        for ( int j = 0 ; j < numVerticesGD ; j++)
            cout << a[i][j] << " ";
        cout<<endl;
    }
    cout<<"En tanto los predecesores: "<<endl;
    for ( int i = 0 ; i < numVerticesGD ; i++){
        for ( int j = 0 ; j < numVerticesGD ; j++)
            cout << p[i][j] << " ";
        cout<<endl;
    }

    caminoFloyd(p,0,1);

    */
    /////////////////////////////// Caminos Mínimos - Algoritmo de Warshall ///////////////////////////

    /*bool** a = new bool*[numVerticesGD];
    for (int i = 0 ; i < numVerticesGD ; i++)
        a[i] = new bool[numVerticesGD];


    for (int i = 0 ; i < numVerticesGD ; i++)
        for(int j = 0 ; j < numVerticesGD ; j++)
            a[i][j] = 0;



    Warshall(grafoD,a);
    cout<<"La matriz de caminos minimos queda: "<<endl;
    for ( int i = 0 ; i < numVerticesGD ; i++){
        for ( int j = 0 ; j < numVerticesGD ; j++)
            cout << a[i][j] << " ";
        cout<<endl;
    }

    */
    /////////////////////////////// Árbol de Recubrimiento de Mínimo Costo - Algoritmo de Prim /////////////
    //Prim(grafoN,0);
    //PrimH(grafoN,0);
    /////////////////////////////// Árbol de Recubrimiento de Mínimo Costo - Algoritmo de Kruskal /////////////
    //Kruskal(grafoN);


//////////////////////////////////////////////////   Problemas NP ///////////////////////////////////////////////////

  ///////////////////////////////////// Algoritmos Aproximados ///////////////////////////////////////////////

    ///////////////////////////////  Vertex Cover ///////////////////////////////////////////////////////
    /*set<int> solucion = VertexCoverAprox(grafoN);
    set<int>::const_iterator it;
    for (it=solucion.cbegin(); it!=solucion.cend();it++)
        cout<< *it << "-";
    */

    ///////////////////////////////  TSP Métrico ///////////////////////////////////////////////////////
    /*int inicio = 0;
    set<int> solucion = TSPMetricoAprox(grafoN,inicio);
    set<int>::const_iterator it;
    cout<< inicio <<endl;
    */

    //////////////////////////////////  Set Covering ////////////////////////////////////////////////////

    /*set< set<int> > subconjuntos = { {1,2,3,4,5,6} , {5,6,8,9} , {1,4,7,10} , {2,5,8,11} , {3,6,9,12},{10,11} };
    set<int> tareas = {1,2,3,4,5,6,7,8,9,10,11,12};

    set< set<int> > solucion = SetCoveringAprox(tareas,subconjuntos);
    cout<<"La cantidad de conjuntos es de: " << solucion.size() <<endl;
    set< set<int> >::const_iterator itList ;
    for ( itList = solucion.cbegin() ; itList != solucion.cend() ; itList++ ){
        cout<<"Subconjunto :" <<endl;
        set<int> subconjunto = *itList;
        set<int>::const_iterator itSet ;
        for(itSet = subconjunto.cbegin() ; itSet != subconjunto.cend(); itSet++)
            cout<<*itSet<<"-";
        cout<<endl;
    }
    */

    //////////////////////////////////  Bin Packing ////////////////////////////////////////////////////
    /*//list<float> S = {0.7 , 0.4 , 0.3 , 0.8 , 0.2 , 0.1 , 0.5}; //Conjunto original
    //list<float> S = {0.8 , 0.7 , 0.5 , 0.4 , 0.3 , 0.2 , 0.1}; //Conjunto ordenado
    list <pair<float,set<float>>> baldes = nextFit(S);
    list <pair<float,set<float>>> baldes = firstFit(S);
    //list <pair<float,set<float>>> baldes = bestFit(S);
    list <pair<float,set<float>>>::const_iterator itList;
    for(itList = baldes.cbegin();itList!= baldes.cend(); itList++){
        cout<<"El costo de este balde llega a "<<itList->first<<endl;
        set<float>::const_iterator itSet;
        for(itSet = itList->second.cbegin(); itSet != itList->second.cend() ; itSet++)
            cout<<*itSet<<"-";
        cout<<endl;
    }
    */

    ///////////////////////////////////// Algoritmos Heurísticos ///////////////////////////////////////////////
    //////////////////////////////////  Coloreo del Grafo //////////////////////////////////////////////
    /*int * verticesColoreados = coloreoGrafoHeuristico(grafoN);
    for (int i = 0 ; i < numVerticesGND ; i++)
        cout<<"El vertice "<<i<<" tiene "<<verticesColoreados[i]<<endl;
    */

    //////////////////////////////////  Problema del Viajante //////////////////////////////////////////////
    /*set < pair<int,int> > T = TSPHeuristico(grafoN,0);

    set < pair<int,int> >::const_iterator itSet;
    for (itSet = T.cbegin() ;itSet != T.cend() ; itSet++)
        cout<< "("<<itSet->first<<","<<itSet->second<<") ;";
    */
    ///////////////////////////////////// Backtracking ///////////////////////////////////////////////
    //////////////////////////////////  N-Reinas - Minimización //////////////////////////////////////////////
    /*int N;
    cout<<"Ingrese el N para el problema de las N reinas"<<endl;
    cin>>N;
    int**costos = new int*[N];
    for(int i = 0 ; i < N ; i++){
        costos[i] = new int[N];
        for(int j = 0; j < N ; j++){
            costos[i][j] = rand() % (100);
            cout<< costos[i][j] << "  ";
        }
        cout<<endl;
    }

    int*solucion = new int[N];
    int*solucionActual = new int[N];
    int cota = INT_MAX;
    backNReinas(costos,solucion,solucionActual,cota,0,0,N);
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j < N ; j++)
            if (solucion[i] == j)
                cout << "X" << " ";
            else
                cout << "-" << " ";
        cout<<endl;
    }
    for(int i = 0; i < N; i++)
        cout<< solucion[i] << "-";

    cout<<"El costo es: "<<cota<<endl;
    */
    //////////////////////////////////  Problema del Laberinto //////////////////////////////////////////////
    /*int M = 5;
    int N = 3;
    int salida = 8;
    celdaLaberinto * laberinto = new celdaLaberinto[M*N];
    int i = 0;
    bool solucion = false;
    while (i < M) {
        int j = 0;
        while (j < N) {
            if (i == 0)
                laberinto[N*i+j].paredes[2] = true;
            if (i == M - 1)
                laberinto[N*i+j].paredes[1] = true;
            if (j == 0)
                laberinto[N*i+j].paredes[3] = true;
            if ( (j == N - 1) && ( N*i+j != salida) )
                laberinto[N*i+j].paredes[0] = true;
            j++;
        }
        cout<<endl;
        i++;
    }
    laberinto[1].paredes[0] = true;
    laberinto[2].paredes[3] = true;
    laberinto[3].paredes[0] = true;
    laberinto[4].paredes[0] = true;
    laberinto[4].paredes[1] = true;
    laberinto[4].paredes[3] = true;
    laberinto[5].paredes[3] = true;
    laberinto[6].paredes[1] = true;
    laberinto[7].paredes[0] = true;
    laberinto[7].paredes[1] = true;
    laberinto[7].paredes[2] = true;
    laberinto[8].paredes[3] = true;
    laberinto[10].paredes[2] = true;



    backLaberinto(laberinto,solucion,N,0,salida);
    if(solucion)
        cout<<"Hay solucion"<<endl; */

    //////////////////////////////////  Set Covering - Backtracking //////////////////////////////////////////////
    /*int P = 15;
    int T = 24;
    bool**asignacion = new bool*[P];
    srand(time(NULL));
    for(int i = 0 ; i < P ; i++){
        asignacion[i] = new bool[T];
        for(int j = 0; j < T ; j++){
            asignacion[i][j] = rand() % (2);
            cout<< asignacion[i][j] << "  ";
        }
        cout<<endl;
    }
    set<int> solucion, personas , tareas;
    int cota = INT_MAX;
    backSetCovering(solucion, personas,asignacion, tareas,cota,-1,T,P);
    cout<<"El conjunto solucion es: "<<endl;
    set<int>::const_iterator it;
    for(it = solucion.cbegin(); it!=solucion.cend();it++)
        cout<<*it<<"-";
    */
//////////////////////////////////  Coloreo del Grafo - Backtracking //////////////////////////////////////////////
    /*int * solucion = new int[numVerticesGND];
    int C = 6;
    bool fin = false;
    backColoreoGrafo(grafoN,solucion,0,C,numVerticesGND,fin);
    for(int i = 0 ; i < numVerticesGND ; i++)
        cout<<solucion[i]<<"-";
    */
//////////////////////////////////  Asignación de Tareas //////////////////////////////////////////////
    list<int> solucion,solucionActual;
    int cota = INT_MAX;
    int P = 2;
    int T = 5;
    int* tareas = new int[T];
    tareas[0] = 15;
    tareas[1] = 10;
    tareas[2] = 32;
    tareas[3] = 11;
    tareas[4] = 23;
    int* procesadores = new int[P];
    procesadores[0] = 0;
    procesadores[1] = 0;
    backAsignacionTareas(tareas,procesadores,solucion,solucionActual,0,cota,P,T);
    cout<<"El valor minimo es: "<<cota;
    list<int>::const_iterator it;
    for(it = solucion.cbegin();it!= solucion.cend() ; it++)
        cout<<*it<<"-";

    return 0;
}

///////////////////////////////////////////   Grafos ///////////////////////////////////////////////////

void cargarGrafoD(GrafoDirigido & grafoD){

    int cantidadVertices;
    cout <<"Ingrese el numero de vertices para tener en el grafo"<<endl;
    cin >> cantidadVertices;
    for(int i = 1 ; i <= cantidadVertices ; i++)
        grafoD.agregarVertice();
    char continuar;
    do{
        int origen,destino,costo;

        cout<<"Ingrese el arco  con su costo"<<endl;
        cin >> origen >> destino >> costo;
        grafoD.agregarArco(origen,destino,costo);
        cout<<"Continuar?"<<endl;
        cin >> continuar;
    } while ( continuar == 's');
}

void cargarGrafoN(GrafoNDirigido & grafoN) {

    int cantidadVertices;
    cout <<"Ingrese el numero de vertices para tener en el grafo"<<endl;
    cin >> cantidadVertices;
    for(int i = 1 ; i <= cantidadVertices ; i++)
        grafoN.agregarVertice();
    char continuar;
    do{
        int origen,destino,costo;

        cout<<"Ingrese la arista con su costo"<<endl;
        cin >> origen >> destino >> costo;
        grafoN.agregarArista(origen,destino,costo);
        cout<<"Continuar?"<<endl;
        cin >> continuar;
    } while ( continuar == 's');

}




void DFS_ND(GrafoNDirigido grafoN , int fuente , char visitados []){

    cout<< fuente << "-"; // Procesamiento, en este caso se imprime el vértice en el que se está recorriendo
    visitados[fuente] = 'v';
    list<int> ady = grafoN.adyacentes(fuente); // En ady estarán los adyacentes del fuente
    list<int>:: const_iterator itAdy; //El iterador que recorrera ady
    for ( itAdy = ady.cbegin() ; itAdy != ady.cend() ; itAdy++) //Se recorren todos los adyacentes del fuente
        if( visitados[*itAdy] != 'v') { //Se controla si el vértice adyacente en ese momento ya se visitó
            visitados[*itAdy] = 'v';
            DFS_ND(grafoN, *itAdy , visitados);
        }
}

void bosqueDFS_ND (GrafoNDirigido grafoN ){

    int N = grafoN.cantVertices();
    char visitados[N];
    for(int i = 0; i < N ; i++) //Se marca a todos los vertices como "No visitados"
        visitados[i] = 'n';
    for(int i = 0; i < N ; i++) //Se hace el control desde afuera del DFS para cada vértice si fue visitado.
        if(visitados[i] != 'v')
            DFS_ND(grafoN,i,visitados);
}

void DFS_D(GrafoDirigido  grafoD , int fuente , int & tiempo , infoDFS arr []) {

    arr[fuente].estado = 'v'; //Se visita al vértice fuente
    cout<<fuente <<'-';
    arr[fuente].inicioVisita = tiempo; //Se marca el tiempo en que se comienza a visitar
    tiempo++;
    list<GrafoDirigido::Nodo> ady = grafoD.adyacentes(fuente);
    list<GrafoDirigido::Nodo>::const_iterator itAdy;
    for( itAdy = ady.cbegin(); itAdy != ady.cend() ; itAdy++)
        if(arr[itAdy->vertice].estado == 'n'){
            arr[itAdy->vertice].predecesor = fuente;
            arr[itAdy->vertice].estado = 'd';
            DFS_D(grafoD, itAdy->vertice , tiempo , arr);
        }
    arr[fuente].finVisita = tiempo;
    tiempo++;

}

void bosqueDFS_D(GrafoDirigido grafoD , infoDFS arr[]){

    int tiempo = 1;
    int numVerticesGD = grafoD.cantVertices();
    for(int i = 0; i < numVerticesGD ; i++){
        arr[i].estado = 'n';
        arr[i].inicioVisita = 0;
        arr[i].finVisita = 0;
        arr[i].predecesor = -1;
    }
    for(int i = 0; i < numVerticesGD ; i++)
        if(arr[i].estado == 'n')
            DFS_D(grafoD , i , tiempo, arr);

    cout<<endl;
}

void BFS_f(GrafoDirigido grafoD , int fuente , char estado[]) {
    queue<int> f;
    f.push(fuente); //Se inserta el elemento fuente en la fila
    estado[fuente] = 'V';
    cout<< fuente << "-"; //Procesamiento del vértice
    while (!f.empty()){ //Iteracion principal hasta que la fila no se vacíe.
        list<GrafoDirigido::Nodo> ady = grafoD.adyacentes(f.front());//Lista de adyacentes del primer elemento de la fila.
        list<GrafoDirigido::Nodo>::const_iterator itAdy;
        for( itAdy = ady.cbegin() ; itAdy!= ady.cend() ; itAdy++){ //Se recorre toda la lista de adyacencia
            int verticeActual = itAdy->vertice;
            if ( estado[verticeActual] != 'V') { //Control de si el vértice está visitado o no
                //Se visita verticeActual
                f.push( verticeActual);//Se ingresa a la fila.
                cout << verticeActual << "-"; //Se procesa.
                estado[verticeActual] = 'V';
            }
        }
        //Luego de recorrer los adyacentes del primero de la fila, se elimina
        f.pop();
    }
}

void bosqueBFS_f(GrafoDirigido grafoD){
    int N = grafoD.cantVertices();
    char estado[N];
    for(int i = 0; i < N ; i++)
        if(estado[i] != 'V')
            BFS_f(grafoD,i,estado);

}

void DFS_excentricidad(GrafoNDirigido grafoN , int fuente , char estado[] , int prof[] , int act) {
    act++;
    estado[fuente] = 'V';
    if ( act < prof[fuente] )
        prof[fuente] = act;
    /*cout<< "act: " << act <<endl;
    cout << "La profundidad del vertice " << fuente << " es: " << prof[fuente] <<endl;
    cout <<"........................................"<<endl;*/

    list<int> ady = grafoN.adyacentes(fuente);
    list<int>:: const_iterator itAdy ;
    for(itAdy=ady.cbegin() ; itAdy!=ady.cend(); itAdy++)
        if(estado[*itAdy] != 'V'){
            cout<<"Se llama a recursion desde: "<< fuente <<" a "<< *itAdy << endl;
            DFS_excentricidad(grafoN,*itAdy,estado,prof,act); //Cada llamado recursivo aumenta la profundidad

            estado[*itAdy] = 'N';
        }
}

void cargarDistancias (int prof[], int N){
    for (int i = 0; i < N ; i++)
        prof[i] = INT_MAX;
}

int mayorDistancia( int prof[] ,int N){

    int mayorActual = INT_MIN;
    for ( int i = 0; i < N; i++)
        if(prof[i] > mayorActual)
            mayorActual = prof[i];

    return mayorActual;

}

int DFS_excentricidadGrafo(GrafoNDirigido grafoN) {

    int N = grafoN.cantVertices();
    char estado[N];
    int mayorActual = 0;

    for(int i = 0; i < N ; i++){
        for (int j = 0; j < N ; j++)
            estado[j]='N';
        int prof[N];
        cargarDistancias(prof,N);
        DFS_excentricidad(grafoN,i,estado, prof , -1);
        int excVertice = mayorDistancia(prof,N);

        cout << "La excentricidad del vertice " << i << " es: " << excVertice<<endl;
        if(excVertice > mayorActual){
            mayorActual = excVertice;
            if ( excVertice == INT_MAX)
                return INT_MAX;
        }
    }
    return mayorActual;
}




int BFS_excentricidad(GrafoNDirigido grafoN , int fuente , char estado[]) {
    queue<int> f;
    int excVertice = 0;
    int visitados = 1; //Permite controlar al final si quedaron vertices sin visitar
    int verticesNivel = 0; // Marca después de cuántos vértices desencolados debo actualizar la excentricidad
    int verticesDesencolados = 0;
    int limite = 1; // Por defecto al arrancar en un vértice, después de la primer desencolada, ya el próximo hará dist 1
    f.push(fuente); //Se inserta el elemento fuente en la fila
    estado[fuente] = 'V';
    while (!f.empty()){ //Iteracion principal hasta que la fila no se vacíe.
        list<int> ady = grafoN.adyacentes(f.front());//Lista de adyacentes del primer elemento de la fila.
        list<int>::const_iterator itAdy;
        for( itAdy = ady.cbegin() ; itAdy!= ady.cend() ; itAdy++) { //Se recorre toda la lista de adyacencia

            int verticeActual = *itAdy;
            if (estado[verticeActual] != 'V') { //Control de si el vértice está visitado o no
                //Se visita verticeActual
                f.push(verticeActual);//Se ingresa a la fila.
                visitados++;
                verticesNivel++;
                estado[verticeActual] = 'V';
            }
        }
        f.pop();
        verticesDesencolados++;
        cout<<"Vertices Nivel: "<< verticesNivel <<", Vertices desencolados: "<<verticesDesencolados<<", Limite: "<< limite<<endl;

        if (verticesDesencolados == limite){
            excVertice++; //Actualizo la excentricidad
            limite = verticesNivel; //Ahora el límite son aquellos que entraron en la anterior.
            verticesDesencolados = 0; //Reseteo los vertices desencolados
            verticesNivel = 0;
        }

    }
    if ( (excVertice == 1) || (visitados < grafoN.cantVertices() ) ) //Esto
        return INT_MAX;
    else
        return excVertice - 1;
}



int BFS_excentricidadGrafo(GrafoNDirigido grafoN) {

    int N = grafoN.cantVertices();
    char estado[N];
    int mayorActual = 0;

    for(int i = 0; i < N ; i++){
        int excVertice = BFS_excentricidad(grafoN,i,estado);
        for (int j = 0; j < N ; j++)
            estado[j]='N';
        cout << "La excentricidad del vertice " << i << " es: " << excVertice<<endl;
        if(excVertice > mayorActual)
            mayorActual = excVertice;
    }
    return mayorActual;
}

void DFS_clasificacion (GrafoDirigido grafoD , int fuente, infoDFS arr[] , int & t){

    arr[fuente].estado = 'D'; //Se descubre el vértice al cuál se está visitando
    arr[fuente].inicioVisita = t++; //Se setea el tiempo de descubrimiento, actualizando el tiempo
    list<GrafoDirigido::Nodo> ady = grafoD.adyacentes(fuente);
    list<GrafoDirigido::Nodo>::const_iterator itAdy;
    for( itAdy = ady.cbegin() ; itAdy != ady.cend() ; itAdy++){
        cout<<"EL arco ( "<<fuente<<" , "<<itAdy->vertice<<" ) es ";
        if(arr[itAdy->vertice].estado != 'D'){ //Control si es un arco tree, que genera la recursión
            cout<<"tree"<<endl;
            DFS_clasificacion(grafoD,itAdy->vertice,arr,t);
        }
        else if( arr[fuente].inicioVisita < arr[itAdy->vertice].inicioVisita) //Control si es un arco forward
                 cout<<"forward"<<endl;
             else if(arr[itAdy->vertice].finVisita == INFINITO) //Control si es un arco back
                    cout<<"back"<<endl;
                  else
                      cout<<"cross"<<endl; //Si no se cumplen las tres condiciones anteriores es cross
    }
    arr[fuente].finVisita = t++; //Se setea el tiempo de finalización del vértice visitado. Aquí se vuelve al invocador.
}

void DFS_aristas (GrafoNDirigido grafoN , int fuente , infoDFS arr[] , int & tiempo){

    arr[fuente].estado = 'V';
    arr[fuente].inicioVisita = tiempo++;
    list<int> ady = grafoN.adyacentes(fuente);
    list<int>::const_iterator itAdy;
    for(itAdy = ady.cbegin(); itAdy != ady.cend() ; itAdy++)
        if(arr[*itAdy].estado != 'V'){
            cout<<*itAdy<<endl;
            cout<<"La arista ( "<<fuente<<" , "<<*itAdy<<") es tree"<<endl;
            arr[*itAdy].predecesor = fuente;
            DFS_aristas(grafoN , *itAdy , arr , tiempo);
        }
        //Acá caen arcos (v,u) donde (u,v) ya se visito y los back. Acá se controlan los back
        else if( (arr[fuente].predecesor!= *itAdy) && (arr[fuente].inicioVisita > arr[*itAdy].inicioVisita) )
            cout<<"La arista ( "<<fuente<<" , "<<*itAdy<<") es back"<<endl;

    arr[fuente].finVisita = tiempo++;
}

void bosqueDFS_aristas (GrafoNDirigido grafoN , infoDFS arr[]){

    int tiempo = 1;
    for(int i = 0 ; i < grafoN.cantVertices() ; i++)
        if(arr[i].estado != 'V')
            DFS_aristas(grafoN,i,arr,tiempo);

}

void DFS_longitud (GrafoNDirigido grafoN , int fuente , int profundidad , char estado[] , int longitud[]){

    estado[fuente] = 'V';
    longitud[fuente] = profundidad++; //Se setea la longitud del vértice visitado al origen
    list<int> ady = grafoN.adyacentes(fuente);
    list<int>::const_iterator itAdy;
    for(itAdy = ady.cbegin(); itAdy != ady.cend() ; itAdy++)
        if(estado[*itAdy] != 'V')
            DFS_longitud(grafoN,*itAdy,profundidad,estado,longitud);
        else if(longitud[*itAdy] > profundidad) //Aca se pregunta por longitud+1 por si lo recorre
                longitud[*itAdy] = profundidad;
}

void DFS_postOrden (GrafoDirigido grafoD , int fuente, char estado[] , int * postOrden , int & num){

    estado[fuente] = 'V';
    list<GrafoDirigido::Nodo> ady = grafoD.adyacentes(fuente);
    list<GrafoDirigido::Nodo>::const_iterator itAdy;
    for (itAdy = ady.cbegin() ; itAdy != ady.cend() ; itAdy++)
        if ( estado[itAdy->vertice] != 'V')
            DFS_postOrden(grafoD , itAdy->vertice , estado, postOrden , num);
    postOrden[fuente] = num++;
}

void numeracionPostOrden (GrafoDirigido grafoD , int postOrden []){

    int N = grafoD.cantVertices();
    int num = 0;
    char estado[N];
    for(int i = 0; i < N ; i++) //Se marca a todos los vertices como "No visitados"
        estado[i] = 'n';
    for(int i = 0; i < N ; i++) //Se hace el control desde afuera del DFS para cada vértice si fue visitado.
        if(estado[i] != 'V')
            DFS_postOrden(grafoD,i,estado,postOrden,num);

}

void DFS_preOrdenGD (GrafoDirigido grafoD , int fuente, char estado[] , int * preOrden , int & num){

    estado[fuente] = 'V';
    preOrden[fuente] = num++;
    list<GrafoDirigido::Nodo> ady = grafoD.adyacentes(fuente);
    list<GrafoDirigido::Nodo>::const_iterator itAdy;
    for (itAdy = ady.cbegin() ; itAdy != ady.cend() ; itAdy++)
        if ( estado[itAdy->vertice] != 'V')
            DFS_preOrdenGD(grafoD , itAdy->vertice , estado, preOrden , num);

}

void numeracionPreOrdenGD (GrafoDirigido grafoD , int preOrden []){

    int N = grafoD.cantVertices();
    int num = 0;
    char estado[N];
    for(int i = 0; i < N ; i++) //Se marca a todos los vertices como "No visitados"
        estado[i] = 'n';
    for(int i = 0; i < N ; i++) //Se hace el control desde afuera del DFS para cada vértice si fue visitado.
        if(estado[i] != 'V')
            DFS_preOrdenGD(grafoD,i,estado,preOrden,num);
}


bool esAciclico (GrafoDirigido grafoD){
    int n = grafoD.cantVertices();
    int postOrden[n];
    numeracionPostOrden(grafoD,postOrden);
    for (int i = 0 ; i < n ; i++)
        for (int j = 0; j < n ; j++)
            if ( (grafoD.existeArco(i,j) ) && (postOrden[j] > postOrden[i]))
                return false;
    return true;
}

void sortTopologico(GrafoDirigido grafoD, int fuente , char estado[] , list<int> & l){
    estado[fuente] = 'V';
    list<GrafoDirigido::Nodo> ady = grafoD.adyacentes(fuente);
    list<GrafoDirigido::Nodo>::const_iterator itAdy;
    for (itAdy = ady.cbegin() ; itAdy != ady.cend() ; itAdy++)
        if (estado[itAdy->vertice] != 'V')
            sortTopologico(grafoD,itAdy->vertice , estado, l);
    l.push_front(fuente);
}

list<int> bosqueSortTopologico (GrafoDirigido grafoD) {

    list<int> l;
    int n = grafoD.cantVertices();
    char estado[n];

    for ( int i = 0 ; i < n ; i++)
        if(estado[i] != 'V')
            sortTopologico(grafoD,i,estado,l);
    return l;
}

int menorPreOrdenBack(GrafoNDirigido grafoN , int fuente ,  infoDFS estado [] ,  list<int> ady , int * preOrden){
    int menorActual = INT_MAX;
    list<int>::const_iterator itAdy;

    for (itAdy = ady.cbegin() ; itAdy != ady.cend() ; itAdy++){
        if(preOrden[*itAdy] < preOrden[fuente] &&
        (estado[fuente].predecesor!= *itAdy) &&
        (estado[fuente].inicioVisita > estado[*itAdy].inicioVisita)){

            if (preOrden[*itAdy] < menorActual)
                menorActual= preOrden[*itAdy];} }
    return menorActual;
}

int menorMasAltoTree(GrafoNDirigido grafoN , int fuente, list<int> ady , int * preOrden , int * masAlto) {
    int menorActual = INT_MAX;
    list<int>::const_iterator itAdy;
    for (itAdy = ady.cbegin() ; itAdy != ady.cend() ; itAdy++)
        if(preOrden[*itAdy] > preOrden[fuente])
            if (masAlto[*itAdy] < menorActual)
                menorActual= masAlto[*itAdy];
    return menorActual;
}

void DFS_preOrdenGND (GrafoNDirigido grafoN , int fuente, infoDFS estado [] , int * preOrden , int * masAlto, int & num , int & t){

    estado[fuente].estado = 'V';
    estado[fuente].inicioVisita = t++;
    preOrden[fuente] = num++;
    list<int> ady = grafoN.adyacentes(fuente);
    list<int>::const_iterator itAdy;
    for (itAdy = ady.cbegin() ; itAdy != ady.cend() ; itAdy++)
        if ( estado[*itAdy].estado != 'V'){
            estado[*itAdy].predecesor = fuente;
            DFS_preOrdenGND(grafoN , *itAdy, estado, preOrden , masAlto, num , t);

        }
    estado[fuente].finVisita = t++;
    cout<<"El padre del vertice "<< fuente <<" es: "<<estado[fuente].predecesor<<endl;
    int param1 = preOrden[fuente];
    int param2 = menorPreOrdenBack(grafoN, fuente ,estado, ady,preOrden); //Controla a los back
    int param3 = menorMasAltoTree(grafoN,fuente,ady,preOrden,masAlto);

    cout<<"Parametro 1: "<<param1<<" ; Parametro 2: "<<param2<<" ; Parametro 3: "<<param3<<endl;
    cout<<"........................................................"<<endl;
    masAlto[fuente] = min(param1, min (param2,param3) );

}

bool esPtoArticulacion (GrafoNDirigido grafoN , int masAlto[] , int preOrden[] , int vertice ){
    list<int> ady = grafoN.adyacentes( vertice);
    list<int>::const_iterator itAdy;
    for(itAdy = ady.cbegin() ; itAdy != ady.cend() ; itAdy++)
        if (masAlto[*itAdy] >= preOrden[vertice])
            return true;
    return false;
}

void puntosArticulacion(GrafoNDirigido grafoN , int fuente){
    int n = grafoN.cantVertices();
    int preOrden[n];
    int masAlto[n];
    infoDFS estado[n];
    int tiempo = 0;
    int num = 0;
    for(int i = 0; i < n ; i++){ //Se marca a todos los vertices como "No visitados"
        estado[i].estado = 'n';
        estado[i].predecesor = -1;
    }
    DFS_preOrdenGND(grafoN,0,estado,preOrden,masAlto,num,tiempo);
    for (int i = 0 ; i < n; i++)
        if (esPtoArticulacion(grafoN,masAlto,preOrden,i))
            cout<<"El vertice "<< i << "es un punto de articulacion"<<endl;
}

void DFS_CFC ( GrafoDirigido grafoD , int fuente , char estado[] , list<int> & verticesPostOrden , GrafoDirigido & grafoDR){

    estado[fuente] = 'V';
    list<GrafoDirigido::Nodo> ady = grafoD.adyacentes(fuente);
    list<GrafoDirigido::Nodo>::const_iterator itAdy;
    for(itAdy = ady.cbegin(); itAdy != ady.cend(); itAdy++){
        grafoDR.agregarArco(itAdy->vertice,fuente,0);
        if(estado[itAdy->vertice] != 'V')
            DFS_CFC(grafoD,itAdy->vertice,estado,verticesPostOrden,grafoDR);
    }

    verticesPostOrden.push_front(fuente);


}

bool estaEnLista ( list<int> verticesPostOrden , int vertice ){

    list<int>::const_iterator it;
    for(it=verticesPostOrden.cbegin(); it!=verticesPostOrden.cend(); it++)
        if(*it == vertice)
            return true;
    return false;

}

void sacarVertice ( list<int> & verticesPostOrden , int vertice){
    bool continuar = true;
    list<int>::const_iterator it = verticesPostOrden.cbegin();
    while (continuar)
        if(*it == vertice){
            verticesPostOrden.erase(it);
            continuar = false;
        }
        else
            it++;
}

void DFS_GR (GrafoDirigido grafoDR , int fuente , list<int> & verticesPostOrden , list<int> & componente){

    componente.push_back( fuente);
    sacarVertice(verticesPostOrden,fuente);
    list<GrafoDirigido::Nodo> ady = grafoDR.adyacentes(fuente);
    list<GrafoDirigido::Nodo>::const_iterator itAdy;
    for(itAdy = ady.cbegin(); itAdy != ady.cend(); itAdy++)
        if(estaEnLista(verticesPostOrden,itAdy->vertice))
            DFS_GR(grafoDR,itAdy->vertice,verticesPostOrden,componente);

}


list< list<int> > componentesFC (GrafoDirigido grafoD){
    list< list<int> > componentes;
    int n = grafoD.cantVertices();
    GrafoDirigido grafoReverso;
    char estado[n];
    for(int i = 0 ; i < n; i++){
        grafoReverso.agregarVertice();
        estado[i] = 'N';
    }
    list<int> verticesPostOrden;
    for(int i = 0; i < n; i++)
        if (estado[i] != 'V')
            DFS_CFC(grafoD,i,estado,verticesPostOrden,grafoReverso);
    list<int>::const_iterator it = verticesPostOrden.cbegin();
    while (!verticesPostOrden.empty()){
        cout<<verticesPostOrden.size()<<endl;
        list<int>::const_iterator first = verticesPostOrden.cbegin();
        if(estaEnLista(verticesPostOrden,*first)){
            list<int> componente;
            DFS_GR(grafoReverso,*first,verticesPostOrden,componente);
            componentes.push_back(componente);
        }
    }
    return componentes;

}

void DFS_CC ( GrafoNDirigido grafoN , int fuente , list<int> & componente , char estado[]){

    estado[fuente] = 'V';
    componente.push_back(fuente);
    list<int> ady = grafoN.adyacentes(fuente);
    list<int>::const_iterator itAdy;
    for(itAdy = ady.cbegin() ; itAdy != ady.cend() ; itAdy++)
        if(estado[*itAdy] != 'V')
            DFS_CC(grafoN,*itAdy,componente,estado);
}

list< list<int> > componentesConexas (GrafoNDirigido grafoN){

    int n = grafoN.cantVertices();
    list< list <int> > componentes;
    char estado[n];
    for (int i = 0; i < n ; i++)
        estado[i] = 'N';

    for (int i = 0; i < n ; i++)
        if(estado[i] != 'V'){
            list<int> componente;
            DFS_CC(grafoN,i,componente,estado);
            componentes.push_back(componente);
        }

    return componentes;

}

UNIONFIND compConexas (GrafoNDirigido grafoN){

    UNIONFIND componentesConexas(grafoN.cantVertices());
    list< pair<int,int> > lAristas = grafoN.aristasGrafo();
    list< pair<int,int> >::const_iterator itLAristas;
    for ( itLAristas = lAristas.cbegin() ; itLAristas != lAristas.cend() ; itLAristas++ )
        if ( componentesConexas.buscar( itLAristas->first ) != componentesConexas.buscar(itLAristas->second))
            componentesConexas.unir(itLAristas->first,itLAristas->second);
    return componentesConexas;

}

int menorVertice ( int d[] , set<int> S , int n ){


    int menorActual = INFINITO;
    int verticeMenorActual = DISCERNIBLE;
    for ( int i = 0 ; i < n ; i++){
        set<int>::const_iterator it = S.find(i);
        if ( (it == S.cend()) && (d[i] < menorActual ) ){
            menorActual = d[i];
            verticeMenorActual = i;

        }
    }
    return verticeMenorActual;
}

void Dijkstra ( GrafoDirigido grafoD , int fuente){
    int n = grafoD.cantVertices();
    set<int> S = {fuente}; //Acá irán los vértices que se van agregando a la solución
    int d[n]; //Se guardará cada una de las distancias desde el vértice fuente a cada uno de ellos
    int p[n]; //Se guardará quién es el predecesor que logró la distancia que tiene asociada.
    //Se inicializan las estructuras
    for(int i = 0 ; i < n ; i++){
        p[i] = DISCERNIBLE;
        if (i == fuente)
            d[i] = 0;
        else
            d[i] = INFINITO;
    }
    list<GrafoDirigido::Nodo> adyFuente = grafoD.adyacentes(fuente);
    list<GrafoDirigido::Nodo>::const_iterator itAdyFuente;
    for ( itAdyFuente = adyFuente.cbegin() ; itAdyFuente != adyFuente.cend(); itAdyFuente++){
        d[itAdyFuente->vertice] = itAdyFuente->costo;
        p[itAdyFuente->vertice] = fuente;
    }
    while ( S.size() < (n -1) ){ //La iteración principal se cortará cuando se agreguen n-1 vértices
        cout<< S.size() <<endl;
        int verticeMenor = menorVertice(d,S,n);
        S.insert(verticeMenor);
        list<GrafoDirigido::Nodo> ady = grafoD.adyacentes(verticeMenor);
        list<GrafoDirigido::Nodo>::const_iterator itAdy;
        for ( itAdy = ady.cbegin(); itAdy != ady.cend() ; itAdy++){ //Por cada uno de los adyacentes de verticeMenor
            set<int>::const_iterator it = S.find(itAdy->vertice); //Aquí se crea un iterador y busca al vértice de la iteración
            if (it == S.cend() ){ // Se busca que el elemento no esté en S para buscar la mejora
               if (d[itAdy->vertice] > d[verticeMenor] + itAdy->costo){ //Pregunta si el costo actual es peor que el nuevo
                   d[itAdy->vertice] = d[verticeMenor] + itAdy->costo; //Lo actualiza si se cumple
                   p[itAdy->vertice] = verticeMenor;

               }
            }
        }
    }

    for (int i = 0 ; i < n ; i++){
        cout<<"La distancia del vertice "<<fuente<< " al vertice  "<< i <<" es de: "<< d[i]<<endl;
        cout<<"El predecesor de "<< i << " es: "<<p[i]<<endl;
    }

}

void DijkstraH ( GrafoDirigido grafoD , int fuente){
    int n = grafoD.cantVertices();
    set<int> S = {fuente}; //Acá irán los vértices que se van agregando a la solución
    int d[n]; //Se guardará cada una de las distancias desde el vértice fuente a cada uno de ellos
    int p[n]; //Se guardará quién es el predecesor que logró la distancia que tiene asociada.
    HeapModificado h(n); //Aquí estará la estructura eficiente para buscar los valores de forma logaritmica.
    //Se inicializan las estructuras
    for(int i = 0 ; i < n ; i++){
        p[i] = DISCERNIBLE;
        if (i == fuente)
            d[i] = 0;
        else{
            d[i] = INFINITO;
            h.agregarHeap(INFINITO,i);
        }
    }
    list<GrafoDirigido::Nodo> adyFuente = grafoD.adyacentes(fuente);
    list<GrafoDirigido::Nodo>::const_iterator itAdyFuente;
    for ( itAdyFuente = adyFuente.cbegin() ; itAdyFuente != adyFuente.cend(); itAdyFuente++){
        d[itAdyFuente->vertice] = itAdyFuente->costo;
        h.modificarHeap(itAdyFuente->costo , itAdyFuente->vertice);
        p[itAdyFuente->vertice] = fuente;
    }
    while ( S.size() < (n -1) ){ //La iteración principal se cortará cuando se agreguen n-1 vértices
        pair<int,int> verticeMenor = h.raizHeap();
        S.insert(verticeMenor.second);
        h.eliminarHeap();
        list<GrafoDirigido::Nodo> ady = grafoD.adyacentes(verticeMenor.second);
        list<GrafoDirigido::Nodo>::const_iterator itAdy;
        for ( itAdy = ady.cbegin(); itAdy != ady.cend() ; itAdy++){ //Por cada uno de los adyacentes de verticeMenor
            set<int>::const_iterator it = S.find(itAdy->vertice); //Aquí se crea un iterador y busca al vértice de la iteración
            if (it == S.cend() ){ // Se busca que el elemento no esté en S para buscar la mejora
                if (d[itAdy->vertice] > d[verticeMenor.second] + itAdy->costo){ //Pregunta si el costo actual es peor que el nuevo
                    d[itAdy->vertice] = d[verticeMenor.second] + itAdy->costo; //Lo actualiza si se cumple
                    h.modificarHeap(d[verticeMenor.second] + itAdy->costo , itAdy->vertice);
                    p[itAdy->vertice] = verticeMenor.second;
                } } } }


    for (int i = 0 ; i < n ; i++){
        cout<<"La distancia del vertice "<<fuente<< " al vertice  "<< i <<" es de: "<< d[i]<<endl;
        cout<<"El predecesor de "<< i << " es: "<<p[i]<<endl;
    }

}

void Floyd ( GrafoDirigido grafoD , int**a , int**p){
    int n = grafoD.cantVertices();
    //Carga de los costos directos
    for ( int i = 0; i < n ; i++ ){ //Para cada uno de los vértices origen
        list<GrafoDirigido::Nodo> ady = grafoD.adyacentes(i); //Se cargan sus adyacentes
        list<GrafoDirigido::Nodo>::const_iterator itAdy;
        for (itAdy = ady.cbegin() ; itAdy != ady.cend(); itAdy++)
            if (i != itAdy->vertice) //Como puede haber bucles, se excluyen, ya que deben tener costo 0
                a[i][itAdy->vertice] = itAdy->costo;
    }
    for (int k = 0 ; k < n ; k++)
        for (int i = 0 ; i < n ; i++)
            for (int j = 0 ; j < n ; j++)
                if (a[i][j] > a[i][k] + a[k][j]){ //Si el camino anterior supera al intermedio con el vértice k
                    a[i][j] = a[i][k] + a[k][j]; //Se actualiza el costo
                    p[i][j] = k; //Y el predecesor del cambio es el vértice k por el cuál se pasó.
                }
}

void caminoFloyd( int**p , int i , int j){

    int k = p[i][j];
    if(k>-1){
        caminoFloyd(p,i,k);
        cout<<k<<endl;
        caminoFloyd(p,k,j);
    }
}

void Warshall ( GrafoDirigido grafoD , bool**a ){
    int n = grafoD.cantVertices();
    for ( int i = 0; i < n ; i++ ){
        list<GrafoDirigido::Nodo> ady = grafoD.adyacentes(i);
        list<GrafoDirigido::Nodo>::const_iterator itAdy;
        for (itAdy = ady.cbegin() ; itAdy != ady.cend(); itAdy++)
                a[i][itAdy->vertice] = 1;
    }
    for (int k = 0 ; k < n ; k++)
        for (int i = 0 ; i < n ; i++)
            for (int j = 0 ; j < n ; j++)
                if ( (a[i][j])  or  (a[i][k]) and (a[k][j]))
                    a[i][j] = 1;
    }

void Prim ( GrafoNDirigido grafoN , int inicio){

    int n = grafoN.cantVertices();
    set< pair<int,int> > T;
    set <int> S = {inicio};
    int menor_costo[n];
    int mas_cercano[n];

    for (int i = 0 ; i < n ; i++){
        set <int>::const_iterator itSet = S.find(i);
        if (itSet == S.cend()){
            menor_costo[i] = grafoN.costo(inicio,i);
            mas_cercano[i] = inicio;
        }
    }
    while ( S.size() < n){
        int w = menorVertice(menor_costo,S,n);
        S.insert(w);
        T.insert( {w,mas_cercano[w]} );
        for(int i = 0 ; i < n ; i++){
            set <int>::const_iterator itSet = S.find(i);
            if ( (itSet == S.cend()) && (grafoN.costo(w,i) < menor_costo[i])){
                menor_costo[i] = grafoN.costo(w,i);
                mas_cercano[i] = w;
            }
        }
    }
}

list< pair<int,int> > PrimH (GrafoNDirigido grafoN , int inicio){
    int n = grafoN.cantVertices();
    list< pair<int,int> > T;
    set <int> S = {inicio};
    HeapModificado h(n);
    int mas_cercano[n];
    for (int i = 0 ; i < n ; i++){
        set <int>::const_iterator itSet = S.find(i);
        if (itSet == S.cend()){
            h.agregarHeap( grafoN.costo(inicio,i) , i );
            mas_cercano[i] = inicio;
        }
    }
    while ( S.size() < n){
        int w = h.raizHeap().second;
        h.eliminarHeap();
        S.insert(w);
        T.push_back( {w,mas_cercano[w]} );
        for(int i = 0 ; i < n ; i++){
            set <int>::const_iterator itSet = S.find(i);
            if ( (itSet == S.cend()) && (grafoN.costo(w,i) < h.costo(i))){
                h.modificarHeap( grafoN.costo(w,i) , i );
                mas_cercano[i] = w;
            }
        }
    }

    return T;
}




void Kruskal ( GrafoNDirigido grafoN ) {
  int cantAristas = 0;
  int n = grafoN.cantVertices();
  set< pair<int,int> > T ; //Inicialmente vacío
  UNIONFIND VS(n); //Por defecto, todos los vértices están separados
  Heap Q(n*n);//Aquí se insertarán las aristas de menor a mayor

  for (int i = 0 ; i < n ; i++)
      for (int j = i ; j < n ; j++)
          if (grafoN.costo(i,j) != INT_MAX)
              Q.agregarHeap(grafoN.costo(i, j), {i, j});

  while (cantAristas < n-1){
      pair<int , pair<int,int>> aristaMenor = Q.raizHeap();//Se obtiene la raíz donde está el menor costo
      Q.eliminarHeap(); //Se saca la arista con costo menor ya que se usó.
      if (VS.buscar(aristaMenor.second.first) != VS.buscar(aristaMenor.second.second) ){
          VS.unir(aristaMenor.second.first , aristaMenor.second.second);
          T.insert( {aristaMenor.second.first,aristaMenor.second.second}  );
          cantAristas++;
      }
  }

 }

///////////////////////////////////////////   Problemas NP ///////////////////////////////////////////////////
 void mostrarAristas ( GrafoNDirigido grafoN , list < pair<int,int> > lista ){
    list < pair<int,int> >::const_iterator it = lista.cbegin();
    for(;it != lista.cend() ; it++)
        cout<<"("<<it->first<<","<<it->second<<") ;";
    cout<<endl<<".............."<<endl;
}



set<int> VertexCoverAprox ( GrafoNDirigido grafoN){
    set<int> C; //Este será el conjunto solución
    list < pair <int,int> > E = grafoN.aristasGrafo();
    do{
        int numArista;
        if(E.size() != 1)
          numArista = rand() % (E.size() - 1) ; //Selecciona una arista, teniendo a la cantidad de aristas como límite
        else
          numArista = 0; //Acá entra si queda solo una arista
        list < pair <int,int> >::iterator it = E.begin();
        for (int i = 0 ; i != numArista ; i++)
            it++; //Avanzo el iterador hasta llegar al número de arista
        pair<int,int> arista = *it;
        C.insert({it->first,it->second}); //Inserto los vértices de la arista seleccionada en la solución
        it = E.begin(); //Reseteo el iterador para que recorra toda la lista
        while (it != E.end()){
            cout<<"("<<it->first<<","<<it->second<<")"<<endl;
            if( (it->first == arista.first)  || (it->first == arista.second) ||
                (it->second == arista.first) || (it->second == arista.second) ){ //Detecta aquellas aristas que tengan a los vértices de la it
                it = E.erase(it); //Se elimina la arista del conjunto de tener a los vértices de la iteración
            }
            else
                it++;
        }
    }
    while (E.size() != 0); //Se hará hasta que no haya más aristas
    return C;
}

set<int> TSPMetricoAprox( GrafoNDirigido grafoN , int inicio){

    list < pair<int,int>  > T = PrimH(grafoN,inicio);
    set<int> solucion ;

    list< pair<int,int> >::const_iterator it;
    for(it= T.cbegin(); it!=T.cend();it++){
        set<int>::const_iterator itFirst = solucion.find(it->first);
        if(itFirst == solucion.cend()){
            cout<<it->first<<"-";
            solucion.insert(it->first);
        }
        set<int>::const_iterator itSecond = solucion.find(it->second);
        if(itSecond == solucion.cend()){
            cout<<it->second<<"-";
            solucion.insert(it->second);
        }
    }
    //Aqui se agregaría al final el elemento principal, pero al hacerlo con set no me permite repetidos
    return solucion;
}

set<int> subconjuntoMayor(set<int> U , set<set<int>> subconjuntos){
    set<set<int>>::iterator itList;
    int mayorActual = INT_MIN;
    set<int> subMayor;
    for(itList = subconjuntos.begin() ; itList != subconjuntos.end() ; itList++){
        int cont = 0;
        set<int> subActual = *itList;
        set<int>::const_iterator itSet;
        for(itSet = subActual.cbegin(); itSet != subActual.cend(); itSet++){
           set<int>::const_iterator itFind = U.find(*itSet);
           if (itFind != U.cend())
               cont++;
        }
        if(cont > mayorActual){
            mayorActual = cont;
            subMayor = subActual;
        }
    }
    return subMayor;
}


set< set<int> > SetCoveringAprox ( set<int> tareas ,set<set<int>> subconjuntos){
    set < set<int> > C; //Acá irá los subconjuntos que entren a la solución
    set<int> U = tareas; //Estarán todas las tareas existentes
    while ( U.size() > 0){
        set< int > S = subconjuntoMayor(U,subconjuntos); //El iterador estará en el sub mayor
        C.insert(S);
        subconjuntos.erase(S);
        set<int>::iterator itErase;
        for(itErase = S.begin() ; itErase != S.end() ; itErase++)
            U.erase(*itErase);
    }
    return C;
}

list <pair<float,set<float>>> nextFit(  list<float> objetos  ){
    list <pair<float,set<float>>> baldes;
    set<float> balde;
    list<float>::const_iterator it;
    float costoBalde = 0;
    for (it=objetos.cbegin() ; it!=objetos.cend();it++) {

        if (*it + costoBalde > 1) {
            baldes.push_back({costoBalde, balde});
            costoBalde = 0;
            balde.clear();
        }
        costoBalde += *it;
        balde.insert(*it);
    }

    if (costoBalde != 0)
        baldes.push_back({costoBalde,balde});

    return baldes;
}

list <pair<float,set<float>>> firstFit(  list<float> objetos  ){

    list <pair<float,set<float>>> baldes;
    set<float> balde;
    float costoBalde = 0;
    baldes.push_back({costoBalde,balde});
    list<float>::const_iterator it;
    for (it=objetos.cbegin() ; it!=objetos.cend();it++) {
        list<pair<float, set<float>>>::iterator itBaldes = baldes.begin();
        while ((itBaldes != baldes.end()) && (itBaldes->first + *it > 1))
            itBaldes++;
        if (itBaldes != baldes.end()) {
            itBaldes->first += *it;
            itBaldes->second.insert(*it);
        } else {
            set<float> baldeNuevo = {*it};
            float nuevoCosto = *it;
            baldes.push_back({nuevoCosto, baldeNuevo});
        }
    }
    return baldes;
}

list <pair<float,set<float>>> bestFit(  list<float> objetos  ) {

    list <pair<float,set<float>>> baldes;
    set<float> balde;
    float costoBalde = 0;
    baldes.push_back({costoBalde,balde});
    list<float>::const_iterator it;
    for (it=objetos.cbegin() ; it!=objetos.cend();it++) {
        list<pair<float, set<float>>>::iterator itBaldes = baldes.begin();
        list<pair<float, set<float>>>::iterator itBaldesMenorDesperdicio;
        float menorDesperdicio = 0;
        while (itBaldes != baldes.end()){
            if ( (itBaldes->first + *it <= 1) && (itBaldes->first + *it > menorDesperdicio ) ){
                menorDesperdicio = itBaldes->first + *it;
                itBaldesMenorDesperdicio = itBaldes;
            }
            itBaldes++;
        }
        if (menorDesperdicio != 0 ) {
            itBaldesMenorDesperdicio->first += *it;
            itBaldesMenorDesperdicio->second.insert(*it);
        } else {
            set<float> baldeNuevo = {*it};
            float nuevoCosto = *it;
            baldes.push_back({nuevoCosto, baldeNuevo});
        }
    }
    return baldes;
}

int * coloreoGrafoHeuristico (GrafoNDirigido grafoN){
   int n = grafoN.cantVertices();
   int *  verticesColoreados = new int[n];
   for (int i = 0 ; i < n ; i++)
       verticesColoreados[i] = 0;

   for(int i = 0; i < n ; i++){
       int c = 1; //Numero del color
       bool coloreado = false;
       list<int> ady = grafoN.adyacentes(i);
       while (!coloreado){
          list<int>::const_iterator itAdy = ady.cbegin();
          while ( (itAdy != ady.cend() ) && (verticesColoreados[*itAdy] != c) )
             itAdy++;
          if(itAdy!= ady.cend())
             c++;
          else
             coloreado = true;
       }
       verticesColoreados[i] = c;
   }
   return verticesColoreados;
}

void actualizarCosto ( GrafoNDirigido grafoN, int menor_costo[] , int mas_cercano[] , int grado_incidencia[], int n , int verticeCambio){

    int menor = INFINITO;
    int verticeMenor = DISCERNIBLE;
    for (int i = 0 ; i < n ; i++ ){
        int costoArista = grafoN.costo(i,verticeCambio);
        if ( (grado_incidencia[i] < 2) && (costoArista < menor ) ){
            menor = costoArista;
            verticeMenor = i;
        }
    }
    menor_costo[verticeCambio] = menor;
    mas_cercano[verticeCambio] = verticeMenor;

}


int menorVerticeH ( GrafoNDirigido grafoN, int * menor_costo , int * mas_cercano , int * grado_incidencia, set<int> S , int n ){
    int menorActual = INFINITO;
    int verticeMenorActual = DISCERNIBLE;
    for ( int i = 0 ; i < n ; i++){
        set<int>::const_iterator it = S.find(i);
        if (it == S.cend() ){
            if (grado_incidencia [mas_cercano[i]] > 1 ){
                cout<<"Entra"<<endl;
                actualizarCosto(grafoN, menor_costo,mas_cercano,grado_incidencia, n, i);
            }
            if(menor_costo[i] < menorActual ){
                menorActual = menor_costo[i] ;
                verticeMenorActual = i;
            }
        }
     }
    return verticeMenorActual;
}

void obtenerAristaCierre ( int * grado_incidencia , int & primerVertice , int & segundoVertice){
    int limit = 0;
    int i = 0;
    while (limit < 2) {
        if (grado_incidencia[i] == 1) {
            if (primerVertice == DISCERNIBLE)
                primerVertice = i;
            else
                segundoVertice = i;
            limit++;
        }
        i++;
    }
}

set < pair<int,int> > TSPHeuristico (GrafoNDirigido grafoN , int inicio){
    int n = grafoN.cantVertices();
    int menor_costo[n]; int mas_cercano[n]; int grado_incidencia[n];
    set< pair<int,int> > T; set <int> S = {inicio};
    menor_costo[inicio] = DISCERNIBLE; mas_cercano[inicio] = inicio; grado_incidencia[inicio] = 0;
    for (int i = 0 ; i < n ; i++){
        set <int>::const_iterator itSet = S.find(i);
        if (itSet == S.cend()){
            menor_costo[i] = grafoN.costo(inicio,i);
            cout<<menor_costo[i]<<endl;
            mas_cercano[i] = inicio;
            grado_incidencia[i] = 0;
        }
    }
    while ( S.size() < n){
        int w = menorVerticeH(grafoN,menor_costo,mas_cercano,grado_incidencia,S,n);
        S.insert(w);
        T.insert( {w,mas_cercano[w]} );
        grado_incidencia[w]++; grado_incidencia [ mas_cercano[w]]++;
        for(int i = 0 ; i < n ; i++){
            set <int>::const_iterator itSet = S.find(i);
            if ( (itSet == S.cend()) && (grafoN.costo(w,i) < menor_costo[i])){
                menor_costo[i] = grafoN.costo(w,i);
                mas_cercano[i] = w;
            }
        }
    }
    int primerVertice = DISCERNIBLE; int segundoVertice = DISCERNIBLE;
    obtenerAristaCierre (grado_incidencia , primerVertice, segundoVertice);
    T.insert({primerVertice,segundoVertice});

    return T;
}

bool podaColumna ( int fila,int j , int*solucionActual){

    for (int i = 0; i < fila ; i++ )
        if(solucionActual[i] == j)
            return true;
    return false;
}

bool podaDiagonal ( int fila,int j , int*solucionActual){

    for (int i = 0; i < fila ; i++ )
        if( (i-solucionActual[i] == fila-j) || (i+solucionActual[i] == fila+j) )
            return true;
    return false;
}


void backNReinas(int**costos,int*solucion,int*solucionActual,int& cota,int costoActual,int fila,int N){

    if (fila == N){
        for(int i = 0 ; i < N; i++)
            solucion[i] = solucionActual[i];
        cota = costoActual;
    }
    else
        for (int j = 0 ; j < N ; j++)
            if( (!podaColumna(fila,j,solucionActual) ) && (!podaDiagonal(fila,j,solucionActual) ) &&
                (costoActual + costos[fila][j] < cota)){
                    solucionActual[fila] = j;
                    costoActual+= costos[fila][j];
                    fila++;
                    backNReinas(costos,solucion,solucionActual,cota,costoActual,fila,N);
                    fila--;
                    costoActual-= costos[fila][j];
                }
}

void backLaberinto (celdaLaberinto*laberinto , bool & solucion , int N , int entrada, int salida ){

    if (entrada==salida){
        solucion = true;
    }
    else
        {
            for ( int i = 0 ; i < CANT_POSICIONES ; i++)
                if((!laberinto[entrada].paredes[i]) && (!laberinto[entrada].visitado) && (!solucion) ){
                    laberinto[entrada].visitado = true;
                    int hijo = entrada;
                    switch (i) {
                        case 0 :
                            hijo++;
                            break;
                        case 1 :
                            hijo+=N;
                            break;
                        case 2 :
                            hijo-=N;
                            break;
                        case 3 :
                            hijo--;
                            break;
                    }
                    backLaberinto(laberinto,solucion,N,hijo,salida);
                    laberinto[entrada].visitado = false;
                }
        }
}

set<int>nuevasTareas (bool**asignacion , set<int> tareas , int numPersona, int T ){
    set<int> newTareas;
    for(int j = 0 ; j < T ; j++)
        if( asignacion[numPersona][j]){
            set<int>::const_iterator itFind = tareas.find(j);
            if(itFind == tareas.cend())
                newTareas.insert(j);
        }
    return newTareas;
}

void modificarTareas (set<int>& tareas , set<int> newTareas , char accion){
    set<int>::const_iterator it ;
    for ( it = newTareas.cbegin() ; it!= newTareas.cend() ; it++)
        if(accion == 'A')
            tareas.insert(*it);
        else
            tareas.erase(*it);
}

void backSetCovering (set<int> & solucion , set<int> personas , bool**asignacion , set<int> tareas ,
                      int& cota, int numPersona , int T , int P ){

    if(tareas.size() == T){
        cota = personas.size();
        solucion = personas;
    }
    else{
        for( int i = numPersona+1; i < P ; i++){
            set<int> newTareas = nuevasTareas(asignacion,tareas,i,T);
            if((personas.size()+1 < cota) && (newTareas.size() > 0 ) ){
                modificarTareas(tareas,newTareas,'A');
                personas.insert(i);
                backSetCovering(solucion,personas,asignacion,tareas,cota,i,T,P);
                personas.erase(i);
                modificarTareas(tareas,newTareas,'E');
            }
        }
    }
}

bool podaColorRepetido(GrafoNDirigido grafoN, int* solucion, int i, int vertice) {
    list<int> ady = grafoN.adyacentes(vertice);
    list<int>::const_iterator itAdy;
    for(itAdy = ady.cbegin() ; itAdy != ady.cend() ; itAdy++)
        if(solucion[*itAdy] == i )
            return true;
    return false;
}

void backColoreoGrafo (GrafoNDirigido grafoN ,int* solucion,int vertice,int C,int cantVertices,bool& fin ){

    if(vertice == cantVertices)
        fin = true;
    else{
        for(int i = 1 ; i <= C ; i++)
            if ( (!podaColorRepetido(grafoN,solucion,i,vertice)) && (!fin) ){
                solucion[vertice] = i;
                vertice++;
                backColoreoGrafo(grafoN,solucion,vertice,C,cantVertices,fin);

            }
    }
}

int maximo(int*procesadores , int P){
    int maximoActual = INT_MIN;
    for(int i = 0 ; i < P ; i++)
        if(procesadores[i] > maximoActual)
            maximoActual = procesadores[i];
    return maximoActual;
}

void backAsignacionTareas (int* tareas , int* procesadores , list<int>& solucion, list<int> solucionActual,
                           int numTarea , int& cota , int P , int T){

    if (solucionActual.size() == T){
        cota = maximo(procesadores,P);
        solucion = solucionActual;
    }
    else{
        for(int i = 0 ; i < P ; i++)
            if(tareas[numTarea] + procesadores[i] < cota){
                procesadores[i] += tareas[numTarea];
                solucionActual.push_back(i);
                numTarea++;
                backAsignacionTareas(tareas,procesadores,solucion,solucionActual,numTarea,cota,P,T);
                numTarea--;
                solucionActual.pop_back();
                procesadores[i] -= tareas[numTarea];
            }
    }
}

