#include <iostream>
#include <set>
#include "GrafoM.h"
#include <climits>
#include <cstdlib>
#include <ctime>
#include <list>
#include <cmath>
#include <array>


using namespace std;
const float Costo_Cambio_Colectivo_Mayores10=35;
const float Costo_Cambio_Colectivo_Menores10=18;
const float Costo_Cambio_Colectivo=40;

const float Feromonas_Iniciales=0.01;

const float Disminucion_Feromona_Global=0.1;
const float Disminucion_Feromona_Local=0.1;

const float q0_=0.85;

const float alpha_=1; //Peso feromonas
const float beta_=2; //Peso heuristica

const int Cant_Nodos_Generales=31;
const int Origen_Nodos=-2;

const int CANT_HORMIGAS=10;

struct Camino{
    int Costo;
    list<int> Recorrido;
};

struct Eleccion{
        int vertice;
        float probabilidad;
    };

void CrearMatriz(float ** & matriz, int ancho, int alto) {
    matriz = new float*[alto];
    for (int f = 0; f < alto; f++)
        matriz[f] = new float[ancho];
}
void EliminarMatriz(float ** & matriz, int ancho, int alto) {
    for (int f = 0; f < alto; f++)
        delete [] matriz[f];
    delete [] matriz;
    matriz = 0;
}

void CrearMatrizBool(bool ** & matriz, int ancho, int alto) {
    matriz = new bool*[alto];
    for (int f = 0; f < alto; f++){
        matriz[f] = new bool[ancho];
        for (int c = 0; c < ancho; c++){
            matriz[f][c]=false;
        }
    }
}
void EliminarMatrizBool(bool ** & matriz, int ancho, int alto) {
    for (int f = 0; f < alto; f++)
        delete [] matriz[f];
    delete [] matriz;
    matriz = 0;
}

int SeleccionarEstadoExplotacion(list<Grafo<float>::Arco> & adyacentes,int Origen,float ** CantFeromonas,bool Visitado[],int n, int indirecciones[]){
    //Aca se siguen otras reglas. Hay que cambiarlo
    list<Eleccion> PosiblesElecciones;

    list<Grafo<float>::Arco>::iterator it;
    for (it=adyacentes.begin() ; it != adyacentes.end(); it++){
        Grafo<float>::Arco a=*it;
        if(!Visitado[indirecciones[a.devolver_adyacente()]]){ // Para no volver
            Eleccion posibilidad;
            posibilidad.vertice=a.devolver_adyacente();
            posibilidad.probabilidad=(CantFeromonas[indirecciones[Origen]][indirecciones[posibilidad.vertice]]) * pow((1/a.devolver_costo()),beta_);
            PosiblesElecciones.push_back(posibilidad);
        }
    }

    int mejorOpcion=-1;
    float mejorProbabilidad;
    list<Eleccion>::iterator itP;
    for (itP=PosiblesElecciones.begin() ; itP != PosiblesElecciones.end(); itP++){
        if(itP==PosiblesElecciones.begin()){ //Es el primero
            mejorOpcion=itP->vertice;
            mejorProbabilidad=itP->probabilidad;
        }else{
            if (itP->probabilidad>=mejorProbabilidad){
                mejorOpcion=itP->vertice;
                mejorProbabilidad=itP->probabilidad;
            }
        }
    }

    return mejorOpcion;
}
int SeleccionarEstadoExploracion(list<Grafo<float>::Arco> & adyacentes,int Origen,float ** CantFeromonas,bool Visitado[],int n,int indirecciones[]){
    list<Eleccion> PosiblesElecciones;

    float Sum=0;

    list<Grafo<float>::Arco>::iterator it;
    for (it=adyacentes.begin() ; it != adyacentes.end(); it++){
        Grafo<float>::Arco a=*it;
        if(!Visitado[indirecciones[a.devolver_adyacente()]]){ // Para no volver
            Eleccion posibilidad;
            posibilidad.vertice=a.devolver_adyacente();
            posibilidad.probabilidad=pow(CantFeromonas[indirecciones[Origen]][indirecciones[posibilidad.vertice]], alpha_) * pow((1/a.devolver_costo()),beta_);
            PosiblesElecciones.push_back(posibilidad);
            Sum+=posibilidad.probabilidad;
        }
    }

    float Aux=0;
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); //random de 0 a 1 flotante
    list<Eleccion>::iterator itP;
    for (itP=PosiblesElecciones.begin() ; itP != PosiblesElecciones.end(); itP++){
        Aux+=(itP->probabilidad/Sum);
        if (r<=Aux){
            return itP->vertice;
        }
    }
    //-1 si no hay salida
    return -1;
}
int SeleccionarEstado(Grafo<float> & g,int Origen,float ** CantFeromonas,bool Visitado[],int n, int indirecciones[])
{
    list<Grafo<float>::Arco> Ady;
    g.devolver_adyacentes(Origen,Ady); //en Ady se encuentra todos los arcos

    float q= static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    /*if (Origen==1){
        cout<<"Buscando proximo estado desde "<<Origen<< endl;
        cout<<"Nodos adyacentes: "<<endl;
        list<Grafo<float>::Arco>::const_iterator it;
        for(it=Ady.begin();it!=Ady.end();it++){
            cout<<it->devolver_adyacente()<<"-";
        }
        cout<<endl;
        char l;
        cin>>l;
    }*/

    if (q<=q0_) {
        //cout<<"Explotacion"<<endl;
        return SeleccionarEstadoExplotacion(Ady,Origen,CantFeromonas,Visitado,n,indirecciones);
    }else{
        //cout<<"Exploracion"<<endl;
        return SeleccionarEstadoExploracion(Ady,Origen,CantFeromonas,Visitado,n,indirecciones);
    }
}

Camino CalcularMejorSolucion(list<Camino> Soluciones)
{
    Camino MejorActual;
    Camino Aux;
    bool primero=true;
    list<Camino>::iterator it;
    for(it=Soluciones.begin();it!=Soluciones.end();it++){
        if(primero){
            MejorActual=*it;
            primero=false;
        }
        else{
            Aux=*it;
            if(Aux.Costo < MejorActual.Costo){
                MejorActual=Aux;
            }
        }
    }
    return MejorActual;
}

void ActualizarFeromonasGlobal(float ** & CantFeromonas,Camino MejorSolucion, int indirecciones[], int n){
    bool ** Evaporado;
    CrearMatrizBool(Evaporado,n,n);
    bool Primero=true;
    int i;
    float k=1.0/MejorSolucion.Costo;
    list<int> lista=MejorSolucion.Recorrido;
    list<int> ::iterator itlist;
    for(itlist=lista.begin();itlist!=lista.end();itlist++){
        if(Primero){
            i=*itlist;
            Primero=false;
        }
        else{
            //cout<<"Cambiando feromonas global de "<<i<<" a "<<*itlist<<" Valor de "<<CantFeromonas[indirecciones[i]][indirecciones[*itlist]];
            CantFeromonas[indirecciones[i]][indirecciones[*itlist]]=(1-Disminucion_Feromona_Global)*CantFeromonas[indirecciones[i]][indirecciones[*itlist]]+Disminucion_Feromona_Global*k;
            Evaporado[indirecciones[i]][indirecciones[*itlist]]=true;
            //cout<<" a "<<CantFeromonas[indirecciones[i]][indirecciones[*itlist]]<<endl;
            i=*itlist;
        }
    }

    for(int f=0;f<n;f++){
        for(int c=0;c<n;c++){
            if(!Evaporado[f][c]){
                CantFeromonas[f][c]=(1-Disminucion_Feromona_Global)*CantFeromonas[f][c];
            }
        }
    }

    EliminarMatrizBool(Evaporado,n,n);
}
void ActualizarFeromonasLocal(float ** & CantFeromonas,list<int> Camino,int costo,int indirecciones[]){
    bool Primero=true;
    int i;
    float evaporacionLocal;
    float depositoLocal;
    list<int> ::iterator itlist;
    for(itlist=Camino.begin();itlist!=Camino.end();itlist++)
        if(Primero){
            i=*itlist;
            Primero=false;
        }
        else{
            //cout<<"Cambiando feromonas local de "<<i<<" a "<<*itlist<<" Valor de "<<CantFeromonas[indirecciones[i]][indirecciones[*itlist]];
            evaporacionLocal=(1-Disminucion_Feromona_Local)*CantFeromonas[indirecciones[i]][indirecciones[*itlist]];
            depositoLocal=Disminucion_Feromona_Local*0.5*Feromonas_Iniciales;
            CantFeromonas[indirecciones[i]][indirecciones[*itlist]]=evaporacionLocal+depositoLocal;
            //cout<<" a "<<CantFeromonas[indirecciones[i]][indirecciones[*itlist]]<<endl;
            i=*itlist;
        }
}

void InicializarCantFeromonas(float ** & CantFeromonas, int ancho, int alto)
{
    for(int i=0;i<ancho;i++)
        for(int j=0;j<alto;j++){
            CantFeromonas[i][j]=Feromonas_Iniciales;
        }
}
void InicializarVisitados(bool Visitados[],int n)
{
    for(int i=0;i<n;i++)
        Visitados[i]=false;
}
void InicializarIndirecciones(int * & indirecciones,Grafo<float> & g)
{
    list<int> vertices;
    g.devolver_vertices(vertices);

    //Obtener mayor de vertices
    int maximo=0;
    list<int>::iterator it;

    for(it= vertices.begin(); it!= vertices.end() ;it++){
        if(*it>maximo){
            maximo=*it;
        }
    }

    indirecciones = new int[maximo+1];

    int direccion=0;
    for (it= vertices.begin(); it!= vertices.end() ;it++) {
        indirecciones[*it]=direccion;
        direccion++;
    }
}
void InicializarMapa(Grafo<float> & g){

    g.agregar_vertice(1);
    g.agregar_vertice(3);
    g.agregar_vertice(5);

    g.agregar_vertice(10);

    g.agregar_vertice(17);
    g.agregar_vertice(0);

    g.agregar_vertice(7);

    g.agregar_vertice(24);
    g.agregar_vertice(145);

    g.agregar_vertice(31);
    g.agregar_vertice(14);

    g.agregar_vertice(138);

    g.agregar_vertice(131);
    g.agregar_vertice(36);

    g.agregar_vertice(124);
    g.agregar_vertice(43);

    g.agregar_vertice(12);
    g.agregar_vertice(8);

    g.agregar_vertice(15);
    g.agregar_vertice(19);

    g.agregar_vertice(22);

    g.agregar_vertice(29);
    g.agregar_vertice(26);

    g.agregar_vertice(50);
    g.agregar_vertice(33);

    g.agregar_vertice(57);
    g.agregar_vertice(4);

    g.agregar_vertice(21);
    g.agregar_vertice(38);
    g.agregar_vertice(117);
    g.agregar_vertice(2);
    g.agregar_vertice(25);
    g.agregar_vertice(78);

    g.agregar_vertice(64);
    g.agregar_vertice(16);
    g.agregar_vertice(35);

    g.agregar_vertice(28);
    g.agregar_vertice(45);
    g.agregar_vertice(110);
    g.agregar_vertice(9);
    g.agregar_vertice(18);
    g.agregar_vertice(71);

    g.agregar_vertice(23);
    g.agregar_vertice(42);

    g.agregar_vertice(32);
    g.agregar_vertice(52);

    g.agregar_vertice(30);
    g.agregar_vertice(59);

    g.agregar_vertice(80);
    g.agregar_vertice(37);
    g.agregar_vertice(39);

    g.agregar_vertice(44);
    g.agregar_vertice(66);

    g.agregar_vertice(73);

    g.agregar_vertice(51);

    g.agregar_vertice(85);

    g.agregar_vertice(49);

    g.agregar_vertice(56);

    g.agregar_vertice(58);
    g.agregar_vertice(103);

    g.agregar_vertice(65);
    g.agregar_vertice(96);

    g.agregar_vertice(46);

    g.agregar_arco(1,3,Costo_Cambio_Colectivo_Menores10);
    g.agregar_arco(1,5,Costo_Cambio_Colectivo_Menores10);

    g.agregar_arco(3,1,Costo_Cambio_Colectivo_Mayores10);
    g.agregar_arco(3,5,Costo_Cambio_Colectivo_Mayores10);

    g.agregar_arco(5,1,Costo_Cambio_Colectivo_Menores10);
    g.agregar_arco(5,3,Costo_Cambio_Colectivo_Menores10);


    g.agregar_arco(3,10,24);
    g.agregar_arco(10,3,24);


    g.agregar_arco(10,17,3);
    g.agregar_arco(17,10,3);

    g.agregar_arco(0,17,Costo_Cambio_Colectivo_Menores10);

    g.agregar_arco(17,0,Costo_Cambio_Colectivo_Menores10);


    g.agregar_arco(0,7,9);
    g.agregar_arco(7,0,9);


    g.agregar_arco(24,17,3);
    g.agregar_arco(17,24,3);

    g.agregar_arco(24,145,Costo_Cambio_Colectivo);

    g.agregar_arco(145,24,Costo_Cambio_Colectivo);


    g.agregar_arco(24,31,11);
    g.agregar_arco(31,24,11);

    g.agregar_arco(31,14,Costo_Cambio_Colectivo);

    g.agregar_arco(14,31,Costo_Cambio_Colectivo);


    g.agregar_arco(14,7,5);
    g.agregar_arco(7,14,5);

    g.agregar_arco(145,138,5);

    g.agregar_arco(138,131,4);

    g.agregar_arco(131,36,Costo_Cambio_Colectivo);

    g.agregar_arco(36,131,Costo_Cambio_Colectivo);


    g.agregar_arco(124,43,Costo_Cambio_Colectivo);

    g.agregar_arco(43,124,Costo_Cambio_Colectivo);

    g.agregar_arco(131,124,5);
    g.agregar_arco(36,43,5);


    g.agregar_arco(12,8,Costo_Cambio_Colectivo);

    g.agregar_arco(8,12,Costo_Cambio_Colectivo);

    g.agregar_arco(1,8,7);
    g.agregar_arco(8,1,7);

    g.agregar_arco(12,5,7);
    g.agregar_arco(5,12,7);


    g.agregar_arco(19,15,Costo_Cambio_Colectivo);

    g.agregar_arco(15,19,Costo_Cambio_Colectivo);

    g.agregar_arco(15,8,4);
    g.agregar_arco(8,15,4);

    g.agregar_arco(12,19,4);
    g.agregar_arco(19,12,4);


    g.agregar_arco(15,22,11);
    g.agregar_arco(22,15,11);



    g.agregar_arco(19,26,14);
    g.agregar_arco(26,19,14);

    g.agregar_arco(29,22,9);
    g.agregar_arco(22,29,9);

    g.agregar_arco(26,29,Costo_Cambio_Colectivo);

    g.agregar_arco(29,26,Costo_Cambio_Colectivo);


    g.agregar_arco(29,36,8);
    g.agregar_arco(36,29,8);


    g.agregar_arco(124,145,5);


    g.agregar_arco(50,33,Costo_Cambio_Colectivo);

    g.agregar_arco(33,50,Costo_Cambio_Colectivo);

    g.agregar_arco(26,33,7);
    g.agregar_arco(33,26,7);

    g.agregar_arco(43,50,5);
    g.agregar_arco(50,36,8);


    g.agregar_arco(57,4,Costo_Cambio_Colectivo);

    g.agregar_arco(4,57,Costo_Cambio_Colectivo);

    g.agregar_arco(50,57,5);
    g.agregar_arco(57,50,5);



    g.agregar_arco(21,38,Costo_Cambio_Colectivo);
    g.agregar_arco(21,117,Costo_Cambio_Colectivo);
    g.agregar_arco(21,2,Costo_Cambio_Colectivo);
    g.agregar_arco(21,78,Costo_Cambio_Colectivo);
    g.agregar_arco(21,25,Costo_Cambio_Colectivo);

    g.agregar_arco(38,21,Costo_Cambio_Colectivo);
    g.agregar_arco(38,117,Costo_Cambio_Colectivo);
    g.agregar_arco(38,2,Costo_Cambio_Colectivo);
    g.agregar_arco(38,78,Costo_Cambio_Colectivo);
    g.agregar_arco(38,25,Costo_Cambio_Colectivo);

    g.agregar_arco(117,21,Costo_Cambio_Colectivo);
    g.agregar_arco(117,38,Costo_Cambio_Colectivo);
    g.agregar_arco(117,2,Costo_Cambio_Colectivo);
    g.agregar_arco(117,78,Costo_Cambio_Colectivo);
    g.agregar_arco(117,25,Costo_Cambio_Colectivo);

    g.agregar_arco(2,21,Costo_Cambio_Colectivo);
    g.agregar_arco(2,38,Costo_Cambio_Colectivo);
    g.agregar_arco(2,117,Costo_Cambio_Colectivo);
    g.agregar_arco(2,78,Costo_Cambio_Colectivo);
    g.agregar_arco(2,25,Costo_Cambio_Colectivo);

    g.agregar_arco(78,21,Costo_Cambio_Colectivo);
    g.agregar_arco(78,38,Costo_Cambio_Colectivo);
    g.agregar_arco(78,117,Costo_Cambio_Colectivo);
    g.agregar_arco(78,2,Costo_Cambio_Colectivo);
    g.agregar_arco(78,25,Costo_Cambio_Colectivo);

    g.agregar_arco(25,21,Costo_Cambio_Colectivo);
    g.agregar_arco(25,38,Costo_Cambio_Colectivo);
    g.agregar_arco(25,117,Costo_Cambio_Colectivo);
    g.agregar_arco(25,2,Costo_Cambio_Colectivo);
    g.agregar_arco(25,78,Costo_Cambio_Colectivo);

    g.agregar_arco(31,38,4);
    g.agregar_arco(38,31,4);

    g.agregar_arco(14,21,5);
    g.agregar_arco(21,14,5);

    g.agregar_arco(117,124,10);
    g.agregar_arco(124,117,10);


    g.agregar_arco(64,16,Costo_Cambio_Colectivo);
    g.agregar_arco(64,35,Costo_Cambio_Colectivo);

    g.agregar_arco(16,64,Costo_Cambio_Colectivo);
    g.agregar_arco(16,35,Costo_Cambio_Colectivo);

    g.agregar_arco(35,64,Costo_Cambio_Colectivo);
    g.agregar_arco(35,16,Costo_Cambio_Colectivo);

    g.agregar_arco(57,64,7);
    g.agregar_arco(64,57,7);



    g.agregar_arco(9,45,Costo_Cambio_Colectivo);
    g.agregar_arco(9,71,Costo_Cambio_Colectivo);
    g.agregar_arco(9,28,Costo_Cambio_Colectivo);
    g.agregar_arco(9,18,Costo_Cambio_Colectivo);
    g.agregar_arco(9,110,Costo_Cambio_Colectivo);

    g.agregar_arco(45,9,Costo_Cambio_Colectivo);
    g.agregar_arco(45,71,Costo_Cambio_Colectivo);
    g.agregar_arco(45,28,Costo_Cambio_Colectivo);
    g.agregar_arco(45,18,Costo_Cambio_Colectivo);
    g.agregar_arco(45,110,Costo_Cambio_Colectivo);

    g.agregar_arco(71,9,Costo_Cambio_Colectivo);
    g.agregar_arco(71,45,Costo_Cambio_Colectivo);
    g.agregar_arco(71,28,Costo_Cambio_Colectivo);
    g.agregar_arco(71,18,Costo_Cambio_Colectivo);
    g.agregar_arco(71,110,Costo_Cambio_Colectivo);

    g.agregar_arco(28,9,Costo_Cambio_Colectivo);
    g.agregar_arco(28,45,Costo_Cambio_Colectivo);
    g.agregar_arco(28,71,Costo_Cambio_Colectivo);
    g.agregar_arco(28,18,Costo_Cambio_Colectivo);
    g.agregar_arco(28,110,Costo_Cambio_Colectivo);

    g.agregar_arco(18,9,Costo_Cambio_Colectivo);
    g.agregar_arco(18,45,Costo_Cambio_Colectivo);
    g.agregar_arco(18,71,Costo_Cambio_Colectivo);
    g.agregar_arco(18,28,Costo_Cambio_Colectivo);
    g.agregar_arco(18,110,Costo_Cambio_Colectivo);

    g.agregar_arco(110,9,Costo_Cambio_Colectivo);
    g.agregar_arco(110,45,Costo_Cambio_Colectivo);
    g.agregar_arco(110,71,Costo_Cambio_Colectivo);
    g.agregar_arco(110,28,Costo_Cambio_Colectivo);
    g.agregar_arco(110,18,Costo_Cambio_Colectivo);


    g.agregar_arco(38,45,4);
    g.agregar_arco(45,38,4);

    g.agregar_arco(25,18,6);
    g.agregar_arco(18,25,6);

    g.agregar_arco(21,28,6);
    g.agregar_arco(28,21,6);


    g.agregar_arco(71,78,5);
    g.agregar_arco(78,71,5);

    g.agregar_arco(9,2,5);
    g.agregar_arco(2,9,5);



    g.agregar_arco(4,18,11);
    g.agregar_arco(18,4,11);

    g.agregar_arco(4,46,21);
    g.agregar_arco(46,4,21);

    g.agregar_arco(33,110,9);
    g.agregar_arco(110,33,9);


    g.agregar_arco(64,71,8);
    g.agregar_arco(71,64,8);

    g.agregar_arco(35,28,8);
    g.agregar_arco(28,35,8);

    g.agregar_arco(16,9,8);
    g.agregar_arco(9,16,8);



    g.agregar_arco(23,42,Costo_Cambio_Colectivo);

    g.agregar_arco(42,23,Costo_Cambio_Colectivo);

    g.agregar_arco(35,42,7);
    g.agregar_arco(42,35,7);

    g.agregar_arco(23,16,8);
    g.agregar_arco(16,23,8);


    g.agregar_arco(32,52,Costo_Cambio_Colectivo);

    g.agregar_arco(52,32,Costo_Cambio_Colectivo);

    g.agregar_arco(45,52,9);
    g.agregar_arco(52,45,9);

    g.agregar_arco(32,25,13);
    g.agregar_arco(25,32,13);



    g.agregar_arco(30,59,Costo_Cambio_Colectivo);

    g.agregar_arco(59,30,Costo_Cambio_Colectivo);

    g.agregar_arco(23,30,13);
    g.agregar_arco(30,23,13);

    g.agregar_arco(59,52,9);



    g.agregar_arco(80,37,Costo_Cambio_Colectivo);
    g.agregar_arco(80,39,Costo_Cambio_Colectivo);

    g.agregar_arco(37,80,Costo_Cambio_Colectivo);
    g.agregar_arco(37,39,Costo_Cambio_Colectivo);

    g.agregar_arco(39,80,Costo_Cambio_Colectivo);
    g.agregar_arco(39,37,Costo_Cambio_Colectivo);

    g.agregar_arco(37,30,4);
    g.agregar_arco(30,37,4);

    g.agregar_arco(39,32,9);
    g.agregar_arco(32,39,9);

    g.agregar_arco(52,80,12);



    g.agregar_arco(44,66,Costo_Cambio_Colectivo);

    g.agregar_arco(66,44,Costo_Cambio_Colectivo);

    g.agregar_arco(37,44,7);
    g.agregar_arco(44,37,7);

    g.agregar_arco(66,59,11);


    g.agregar_arco(73,66,13);
    g.agregar_arco(80,73,15);


    g.agregar_arco(44,51,8);
    g.agregar_arco(51,44,8);


    g.agregar_arco(78,85,15);
    g.agregar_arco(85,78,15);


    g.agregar_arco(42,49,7);
    g.agregar_arco(49,42,7);


    g.agregar_arco(49,56,16);
    g.agregar_arco(56,49,16);



    g.agregar_arco(58,103,Costo_Cambio_Colectivo);

    g.agregar_arco(103,58,Costo_Cambio_Colectivo);

    g.agregar_arco(2,58,7);
    g.agregar_arco(58,2,7);

    g.agregar_arco(110,103,11);
    g.agregar_arco(103,110,11);
    g.agregar_arco(103,117,9);



    g.agregar_arco(65,96,Costo_Cambio_Colectivo);

    g.agregar_arco(96,65,Costo_Cambio_Colectivo);

    g.agregar_arco(65,58,13);
    g.agregar_arco(58,65,13);

    g.agregar_arco(96,103,12);
    g.agregar_arco(103,96,12);





    //Grafo Nico:
    /*Vertices=new list<int>[17];
    //Vertice 1
	g.agregar_vertice(1);///azul
	//Vertice 2
	g.agregar_vertice(2);///azul
	g.agregar_vertice(3);///blanco
	g.agregar_arco(1,2,10); ///Conecto el colectivo azul del nodo 1 con el colectivo azul del nodo 2, con una cantidad de 12 cuadras de diferencia
	g.agregar_arco(2,1,12);
	//Vertice 3
	g.agregar_vertice(4);///amarrilo
	//vertice 4
	g.agregar_vertice(5);///azul
	g.agregar_vertice(6);///blanco
	g.agregar_vertice(7);///verde
	g.agregar_arco(3,6,7);
	g.agregar_arco(6,3,7);
	g.agregar_arco(5,2,9);
	g.agregar_arco(2,5,17);
	//vertice 5
    g.agregar_vertice(8);///amarillo
    g.agregar_arco(8,4,9);
    g.agregar_arco(4,8,9);
    //vertice 6
    g.agregar_vertice(9);///verde
    //vertice 7
    g.agregar_vertice(10);///marron
    //vertice 8
    g.agregar_vertice(11);///verde
    g.agregar_vertice(12);///azul
    g.agregar_arco(11,7,6);
    g.agregar_arco(7,11,6);
    g.agregar_arco(12,5,11);
    g.agregar_arco(5,12,13);
    //vertice 9
    g.agregar_vertice(14);///blanco
    g.agregar_vertice(15);///amarillo
    g.agregar_vertice(16);///rojo
    g.agregar_arco(14,6,17);
    g.agregar_arco(6,14,17);
    g.agregar_arco(15,8,7);
    g.agregar_arco(8,15,7);
    //vertice 10
    g.agregar_vertice(17);///verde
    g.agregar_arco(17,9,17);
    g.agregar_arco(9,17,17);
    //vertice 11
    g.agregar_vertice(18);///marron
    g.agregar_arco(18,10,12);
    g.agregar_arco(10,18,12);
    //vertice 12 Centro
    g.agregar_vertice(19);///marron
    g.agregar_vertice(20);///verde
    g.agregar_vertice(21);///azul
    g.agregar_vertice(22);///amarillo
    g.agregar_vertice(23);///blanco
    g.agregar_vertice(24);///rojo
    g.agregar_arco(19,18,12);
    g.agregar_arco(18,19,12);
    g.agregar_arco(20,11,19);
    g.agregar_arco(11,20,19);
    g.agregar_arco(20,17,15);
    g.agregar_arco(17,20,15);
    g.agregar_arco(21,12,14);
    g.agregar_arco(12,21,14);
    g.agregar_arco(22,15,7);
    g.agregar_arco(15,22,7);
    g.agregar_arco(23,14,9);
    g.agregar_arco(14,23,9);
    g.agregar_arco(24,16,8);
    g.agregar_arco(16,24,8);
    //vertice 13
    g.agregar_vertice(25);///rojo
    g.agregar_vertice(26);///marron
    g.agregar_arco(26,19,27);
    g.agregar_arco(19,26,27);
    //vertice 14
    g.agregar_vertice(27);///rojo
    g.agregar_arco(27,24,22);
    g.agregar_arco(24,27,22);
    //vertice 15
    g.agregar_vertice(28);///azul
    g.agregar_vertice(29);///amarillo
    g.agregar_arco(28,21,20);
    g.agregar_arco(21,28,20);
    g.agregar_arco(29,22,26);
    g.agregar_arco(22,29,26);
    //vertice 16
    g.agregar_vertice(30);///marron
    g.agregar_vertice(31);///rojo
    g.agregar_arco(31,16,22);
    g.agregar_arco(16,31,22);
    g.agregar_arco(30,19,28);
    g.agregar_arco(19,30,28);
    g.agregar_arco(31,25,16);
    g.agregar_arco(25,31,16);
    g.agregar_arco(30,26,20);
    g.agregar_arco(26,30,20);
    //vertice 17 Campus
    g.agregar_vertice(32);///azul
    g.agregar_vertice(33);///marron
    g.agregar_vertice(34);///rojo
    g.agregar_arco(32,28,32);
    g.agregar_arco(28,32,32);
    g.agregar_arco(33,26,26);
    g.agregar_arco(26,33,26);
    g.agregar_arco(34,25,28);
    g.agregar_arco(25,34,28);*/






    //Grafo cualquiera

    /*
    g.agregar_vertice(1);
	g.agregar_vertice(2);
	g.agregar_vertice(3);
	g.agregar_vertice(4);
	g.agregar_vertice(5);
	g.agregar_vertice(6);
	g.agregar_vertice(7);
    g.agregar_vertice(8);
    g.agregar_vertice(9);
    g.agregar_vertice(10);
    g.agregar_vertice(11);
    g.agregar_vertice(12);
    g.agregar_vertice(13);
    g.agregar_vertice(14);
    g.agregar_vertice(15);

    g.agregar_arco(1,11,2);
    g.agregar_arco(1,2,2);
    g.agregar_arco(1,10,2);
    g.agregar_arco(1,3,5);
    g.agregar_arco(1,4,7);

    g.agregar_arco(2,7,6);
    g.agregar_arco(2,3,2);

    g.agregar_arco(3,8,7);
    g.agregar_arco(3,4,1);

    g.agregar_arco(4,6,4);
    g.agregar_arco(4,5,1);

    g.agregar_arco(5,6,2);

    g.agregar_arco(6,12,5);

    g.agregar_arco(7,9,2);
    g.agregar_arco(7,12,5);

    g.agregar_arco(8,12,1);
    g.agregar_arco(9,12,2);

    g.agregar_arco(10,7,6);
    g.agregar_arco(11,7,6);
    */
}
void CrearNodosGenerales(array<list<int>, Cant_Nodos_Generales> & NodosGenerales){
    list<int> listAux;

    listAux.push_front(1);
    listAux.push_front(3);
    listAux.push_front(5);
    NodosGenerales[1]=listAux;

    listAux.clear();
    listAux.push_front(8);
    listAux.push_front(12);
    NodosGenerales[2]=listAux;

    listAux.clear();
    listAux.push_front(19);
    listAux.push_front(15);
    NodosGenerales[3]=listAux;

    listAux.clear();
    listAux.push_front(22);
    NodosGenerales[4]=listAux;

    listAux.clear();
    listAux.push_front(29);
    listAux.push_front(26);
    NodosGenerales[5]=listAux;

    listAux.clear();
    listAux.push_front(36);
    listAux.push_front(131);
    NodosGenerales[6]=listAux;

    listAux.clear();
    listAux.push_front(138);
    NodosGenerales[7]=listAux;

    listAux.clear();
    listAux.push_front(10);
    NodosGenerales[8]=listAux;

    listAux.clear();
    listAux.push_front(0);
    listAux.push_front(17);
    NodosGenerales[9]=listAux;

    listAux.clear();
    listAux.push_front(145);
    listAux.push_front(24);
    NodosGenerales[10]=listAux;

    listAux.clear();
    listAux.push_front(43);
    listAux.push_front(124);
    NodosGenerales[11]=listAux;

    listAux.clear();
    listAux.push_front(33);
    listAux.push_front(50);
    NodosGenerales[12]=listAux;

    listAux.clear();
    listAux.push_front(57);
    listAux.push_front(4);
    NodosGenerales[13]=listAux;

    listAux.clear();
    listAux.push_front(46);
    NodosGenerales[14]=listAux;

    listAux.clear();
    listAux.push_front(7);
    NodosGenerales[15]=listAux;

    listAux.clear();
    listAux.push_front(14);
    listAux.push_front(31);
    NodosGenerales[16]=listAux;

    listAux.clear();
    listAux.push_front(78);
    listAux.push_front(2);
    listAux.push_front(25);
    listAux.push_front(21);
    listAux.push_front(38);
    listAux.push_front(117);
    NodosGenerales[17]=listAux;

    listAux.clear();
    listAux.push_front(45);
    listAux.push_front(9);
    listAux.push_front(18);
    listAux.push_front(71);
    listAux.push_front(28);
    listAux.push_front(110);
    NodosGenerales[18]=listAux;

    listAux.clear();
    listAux.push_front(16);
    listAux.push_front(64);
    listAux.push_front(35);
    NodosGenerales[19]=listAux;

    listAux.clear();
    listAux.push_front(23);
    listAux.push_front(42);
    NodosGenerales[20]=listAux;

    listAux.clear();
    listAux.push_front(49);
    NodosGenerales[21]=listAux;

    listAux.clear();
    listAux.push_front(56);
    NodosGenerales[22]=listAux;

    listAux.clear();
    listAux.push_front(85);
    NodosGenerales[23]=listAux;

    listAux.clear();
    listAux.push_front(58);
    listAux.push_front(103);
    NodosGenerales[24]=listAux;

    listAux.clear();
    listAux.push_front(65);
    listAux.push_front(96);
    NodosGenerales[25]=listAux;

    listAux.clear();
    listAux.push_front(32);
    listAux.push_front(52);
    NodosGenerales[26]=listAux;

    listAux.clear();
    listAux.push_front(37);
    listAux.push_front(80);
    listAux.push_front(39);
    NodosGenerales[27]=listAux;

    listAux.clear();
    listAux.push_front(59);
    listAux.push_front(30);
    NodosGenerales[28]=listAux;

    listAux.clear();
    listAux.push_front(44);
    listAux.push_front(66);
    NodosGenerales[29]=listAux;

    listAux.clear();
    listAux.push_front(51);
    NodosGenerales[30]=listAux;
}


/*
void MostrarVisitados(Grafo<float> & g, bool Visitado[], int indirecciones[]){
    list<int> vertices;
    g.devolver_vertices(vertices);
    list<int>::const_iterator it;
    for(it=vertices.begin();it!=vertices.end();it++){
        cout<<"|"<<*it<<":"<<Visitado[indirecciones[*it]]<<"|";
    }
    cout<<endl;
}
*/

bool quedanAdyPorVisitar(Grafo<float> & g,int Origen,bool Visitado[],int indirecciones[]){
    list<Grafo<float>::Arco> adyacentes;
    g.devolver_adyacentes(Origen,adyacentes);
    list<Grafo<float>::Arco>::const_iterator it;
    for(it=adyacentes.begin();it!=adyacentes.end();it++){
        if(Visitado[indirecciones[it->devolver_adyacente()]]==false){
            return true;
        }
    }
    return false;
}
bool LlegoAlFinal(int NodoActual,list<int> & NodosFinal){
    list<int>::const_iterator it;
    for(it=NodosFinal.begin();it!=NodosFinal.end();it++){
        if (NodoActual==*it)
            return true;
    }
    return false;
}

void ConstruirSoluciones(Grafo<float> & g,int n,int Inicio,list<int> & NodosFinal,float ** CantFeromonas,bool Visitado[],int indirecciones[],list<Camino> & Soluciones)
{//CREA N SOLUCIONES Y LAS ALMACENA EN UNA Lista <CAMINO>, DONDE EL CAMINO REGISTRA EL COSTO Y EL RECORRIDO.
    int Hormiga=Inicio;
    int VerticeSig;
    int CostoCamino=0;
    bool NoHayCamino=false;
    Visitado[indirecciones[Hormiga]]=true;
    list<int> NodosVisitados;
    //list<Camino> Soluciones;
    for(int i=1;(i<=CANT_HORMIGAS) && (!NoHayCamino);i++){
        while(!LlegoAlFinal(Hormiga,NodosFinal) && !NoHayCamino){
            //cout<<"Bucando camino desde "<<Hormiga<<endl;
            //MostrarVisitados(g,Visitado,indirecciones);
            VerticeSig=SeleccionarEstado(g,Hormiga,CantFeromonas,Visitado,n,indirecciones);
            //cout<<"Nodo siguiente: "<<VerticeSig<<endl;
            //char m;
            //cin>>m;
            if(VerticeSig==-1){
                list<int>::iterator it=NodosVisitados.begin();
                if((*it!=Inicio) || ((*it==Inicio)&&(quedanAdyPorVisitar(g,Inicio,Visitado,indirecciones)))){
                    CostoCamino-=g.costo_arco(*it,Hormiga);
                    Hormiga=*it;
                    NodosVisitados.pop_front();
                }
                else{
                    cout<<"No hay camino"<<endl;
                    NoHayCamino=true;
                }
            }
            else{
                Visitado[indirecciones[VerticeSig]]=true;
                CostoCamino+=g.costo_arco(Hormiga,VerticeSig);
                NodosVisitados.push_front(Hormiga);
                Hormiga=VerticeSig;
            }
        }
        if(LlegoAlFinal(Hormiga,NodosFinal)){
            NodosVisitados.push_front(Hormiga);
            NodosVisitados.reverse();
            ActualizarFeromonasLocal(CantFeromonas,NodosVisitados,CostoCamino,indirecciones);
            //char t;
            //cin>>t;
            Camino aux;
            aux.Costo=CostoCamino;
            aux.Recorrido=NodosVisitados;
            Soluciones.push_front(aux);
            Hormiga=Inicio;
            Visitado[indirecciones[Hormiga]]=true;
        }
        //Esto estaba adentro del if Hormiga==Final
        NodosVisitados.clear();
        InicializarVisitados(Visitado,n);
        CostoCamino=0;
        Visitado[indirecciones[Inicio]]=true;
    }
}

void MostrarSolucion(Camino Solucion){
    list<int> aux=Solucion.Recorrido;
    list<int>::iterator itlist;
    cout<<"Costo:  "<<Solucion.Costo<< "  Camino: ";
    for(itlist=aux.begin();itlist!=aux.end();itlist++)
        cout<<*itlist<< "  ";
}
void MostrarCaminos(list<Camino> S){
    list<Camino>::iterator it;
    for(it=S.begin();it!=S.end();it++){
        Camino Aux=*it;
        cout<<"Costo: "<< Aux.Costo << " ";
        list<int> Camino=Aux.Recorrido;
        cout<<"Camino: ";
        list<int>::iterator itlist;
        for(itlist=Camino.begin();itlist!=Camino.end();itlist++)
            cout<<*itlist<< "  ";
        cout<<endl;
    }
}

void AlgoritmoColoniadeHormiga(Grafo<float> & g,int Inicio,list<int> & NodosFinal,int n)
{
    int * indirecciones;
    InicializarIndirecciones(indirecciones,g);
    float ** CantFeromonas;
    CrearMatriz(CantFeromonas,n,n);
    InicializarCantFeromonas(CantFeromonas,n,n);
    bool * Visitado=new bool[n];
    InicializarVisitados(Visitado,n);
    list<Camino> Soluciones;
    Camino MejorSolucionLocal;
    Camino MejorSolucionGlobal;
    for(int i=1; i<n; i++){
        ConstruirSoluciones(g,n,Inicio,NodosFinal,CantFeromonas,Visitado,indirecciones,Soluciones);
        //
        //MostrarCaminos(Soluciones);
        MejorSolucionLocal=CalcularMejorSolucion(Soluciones);
        if ((i==1) || (MejorSolucionLocal.Costo<=MejorSolucionGlobal.Costo)){
            MejorSolucionGlobal=MejorSolucionLocal;
        }
        ActualizarFeromonasGlobal(CantFeromonas,MejorSolucionGlobal,indirecciones,n);
        //cout<<"Mejor solucion local: ";
        //MostrarSolucion(MejorSolucionLocal);
        //cout<<endl;
        //char x; //BORRAR ESTO !!!!!!!!!
        //cin>>x;
    }
    MostrarSolucion(MejorSolucionGlobal);
    EliminarMatriz(CantFeromonas,n,n);
    delete [] Visitado;//
    delete [] indirecciones;
    cout << "llego";
}

void AgregarNodoInicial(Grafo<float> & g,int Inicio, array<list<int>, Cant_Nodos_Generales> & NodosGenerales){
    g.agregar_vertice(Origen_Nodos);
    list<int> Nodos=NodosGenerales[Inicio];
    list<int>::const_iterator it;
    for(it=Nodos.begin();it!=Nodos.end();it++){
        cout<<"Agregando arco de origen a "<<*it<<endl;
        g.agregar_arco(Origen_Nodos,*it,1);
    }
    /*char p;
    cin>>p;*/
}

int main()
{
    Grafo<float> g;
    array<list<int>, Cant_Nodos_Generales> NodosGenerales;

    InicializarMapa(g);
    CrearNodosGenerales(NodosGenerales);

    int Inicio=1;
    int Final=15;

    AgregarNodoInicial(g,Inicio,NodosGenerales);
    list<int> NodosFinal=NodosGenerales[Final];
    int n=g.devolver_longitud()+1;

    list<int>::const_iterator it;
    cout<<"Nodos del final: ";
    for(it=NodosFinal.begin();it!=NodosFinal.end();it++){
        cout<<" "<<*it<<" ";
    }
    /*cout<<endl;
    char l;
    cin>>l;*/
    AlgoritmoColoniadeHormiga(g,Origen_Nodos,NodosFinal,n);
    return 0;
}
