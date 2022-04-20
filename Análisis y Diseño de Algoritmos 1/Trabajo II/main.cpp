#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include "lista.h"
#include "matriz.h"
#include "arbus.h"

using namespace std;

void MOSTRA_MATRIZ(matriz &M,int n);
void buscar_palabra(string pathBusqueda, string pathResultado, arbus &A);
void cargar_coleccion(string path, lista &L);
void calcular_datos_celda(string &palab_raiz, float &complejidad , matriz &M , lista &L , int fil , int col);
void buscar_costo_minimo_y_raiz(int fila,int col,matriz &M1,float &costo, string &raiz, int n);
float suma ( int fila, int columna, lista &L);
void cargar_resultado(string pathResultado, matriz &M, int n);

int main(){
    arbus A1;
    arbus A2;
    lista L1;
    lista L2;
    cargar_coleccion("Datasets\\Claves_1.txt", L1);
    cargar_coleccion("Datasets\\Claves_2.txt", L2);
    int n2 = L2.longitud();
    int n1 = L1.longitud();
    matriz M1(n1+1);
    matriz M2(n2+1);

    //diagonal matriz 1
    for (int indice = 1 ; indice <=n1 ; indice ++)
        M1.agregar(indice,indice,L1.frecuencia_de_posicion(indice), L1.palabra_de_posicion(indice));

    //diagonal matriz 2
    for (int indice = 1 ; indice <=n2 ; indice ++)
        M2.agregar(indice,indice,L2.frecuencia_de_posicion(indice), L2.palabra_de_posicion(indice));

    //matriz de arbol optimo para lista de claves 1
    for (int k = 1; k <= n1; k++){
        for (int fil = 1; fil <= n1; fil++){
            for(int col = fil+k-1; col<= fil+k; col++){
                if ((fil<col)&&(col <= n1)){
                    string palab_raiz;
                    float complejidad=0;
                    calcular_datos_celda(palab_raiz,complejidad ,M1 ,L1 ,fil ,col);
                    M1.agregar(fil, col, complejidad, palab_raiz);
                }
            }
        }
    }

    //cargar_resultado("Matriz_1.txt", M1, n1);

    //matriz de arbol optimo para lista de claves 2
    for (int k = 1; k <= n2; k++){
        for (int fil = 1; fil <= n2; fil++){
            for(int col = fil+k-1; col<= fil+k; col++){
                if ((fil<col)&&(col <= n2)){
                    string palab_raiz;                 // string raiz;
                    float complejidad=0;
                    calcular_datos_celda(palab_raiz,complejidad ,M2 ,L2 ,fil ,col);
                    M2.agregar(fil, col, complejidad, palab_raiz);
                }
            }
        }
    }
    //cargar_resultado("Matriz_2.txt", M2, n2);

    A1.crear_arbol_optimo(M1, L1);
    A2.crear_arbol_optimo(M2, L2);

    cout << "costo de arbol binario de busqueda optimo para la lista de claves 1: " << M1.obtener_frecuencia(1, n1) << endl;
    cout << "arbol optimo 1: " <<endl;
    cout << "--------------------------------" <<endl;
    A1.imprimir_por_niveles();
    cout <<endl;
    cout << "costo de arbol binario de busqueda optimo para la lista de claves 2: " << M2.obtener_frecuencia(1, n2) << endl;
    cout << "arbol optimo 2: " <<endl;
    cout << "--------------------------------" <<endl;
    A2.imprimir_por_niveles();
    cout <<endl;
    cout << "busqueda arbol 1: " <<endl;
    buscar_palabra("Datasets\\Busqueda_1.txt", "Resultado_1.txt", A1);
    cout <<endl;
    cout << "busqueda arbol 2: " <<endl;
    buscar_palabra("Datasets\\Busqueda_2.txt", "Resultado_2.txt", A2);

    return 0;
}

void MOSTRA_MATRIZ(matriz &M,int n){
    int i, j;
    for ( i=1; i <= n; i++){
        for ( j=1; j<=n; j++)
            cout << M.obtener_frecuencia(i, j) << "\t";
        cout << endl;
    }
}

void cargar_resultado(string pathResultado, matriz &M, int n){
    int i, j;
    ofstream resultado(pathResultado.c_str(), ios::trunc);
    for ( i=1; i <= n; i++){
        for ( j=1; j<=n; j++){
            string palabra = M.obtener_palabra(i, j);
            ostringstream frecuencia;
            frecuencia << M.obtener_frecuencia(i, j);
            resultado << palabra << ", " << frecuencia.str() <<  "\t";
        }
        resultado << endl;
    }
}

void buscar_palabra(string pathBusqueda, string pathResultado, arbus &A){
    ifstream busqueda(pathBusqueda.c_str());
    if (!busqueda.is_open())
        cout << "No se pudo abrir el archivo: " << pathBusqueda << endl;
    else {
        ofstream resultado(pathResultado.c_str(), ios::trunc);
        while (!busqueda.eof()) {
            string palabra;
            busqueda >> palabra;
            string existe = "No existe";
            int k = 0;
            if (A.pertenece(palabra, k))
                existe = "Existe";
            cout << palabra <<", "<< existe <<", costo: "<< k <<endl;
            resultado << palabra <<","<< existe <<","<< k << endl;
        }
    }
}

void cargar_coleccion(string path, lista &L) {
    ifstream origen(path.c_str());
    if (!origen.is_open())
        cout << "No se pudo abrir el archivo: " << path << endl;
    else {
        while (!origen.eof()) {
            char palabra[50];
            origen >> palabra;
            char *aux = strtok(palabra, ",");
            double frecuencia = atof(aux+strlen(palabra)+1);
            L.insertar_ordenado(palabra, frecuencia);
        }
    }
}

void calcular_datos_celda(string &palab_raiz, float &complejidad , matriz &M , lista &L , int fil , int col){
    float costo = 0;
    string raiz;
    int n = L.longitud();
    buscar_costo_minimo_y_raiz(fil,col,M,costo,raiz,n);
    complejidad = (costo + suma(fil,col,L));
    palab_raiz=raiz;
}

void buscar_costo_minimo_y_raiz(int fila,int col,matriz &M,float &costo, string &raiz, int n){
    int k = fila;
    float costo_aux;
    costo = M.obtener_frecuencia(fila,k-1) + M.obtener_frecuencia(k+1,col);
    raiz = M.obtener_palabra(k,k);
    for (k = fila+1 ; k<=col ; k++){
        if (k!=n){
            costo_aux = M.obtener_frecuencia(fila,k-1) + M.obtener_frecuencia(k+1,col);
            string raiz_aux = M.obtener_palabra(k,k);
            if (costo>costo_aux){
                costo = costo_aux;
                raiz = raiz_aux;
            }
        }
    }
}

float suma ( int fila, int columna, lista &L){
        float contador = 0;
        for (int k=fila; k<=columna; k++)
            contador += L.frecuencia_de_posicion(k);
        return contador;
}
