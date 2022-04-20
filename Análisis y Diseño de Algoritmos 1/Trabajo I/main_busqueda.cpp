#include <iostream>
#include <fstream>
#include <conio.h>
#include "../arbusTDA/arbus.h"
#include "../listaTDA/lista.h"


using namespace std;

void cargar_coleccion(string path, lista<string> &L1, arbus<string> &A1, int q);
void buscar_palabra(string pathBusqueda, string pathResultado, lista<string> &L1, arbus<string> &A1, int q);

int main()
{
    lista<string> L1;
    lista<string> L2;
    lista<string> L3;
    arbus<string> A1;
    arbus<string> A2;
    arbus<string> A3;
    int q = 0;
    while ((q != 1) && (q != 2)){
        cout << "Que estructura desea analizar?" <<endl;
        cout << "1 - Lista" <<endl;
        cout << "2 - Arbol binario de busqueda"<<endl;
        cin >> q;
    }
    cout << "-----------------------------------------------"<<endl;
    cargar_coleccion("Datasets\\Coleccion_1.txt", L1, A1, q);
    cout << "Cargando coleccion_1 ..."<<endl;
    buscar_palabra("Datasets\\Busqueda_1.txt", "Resultado_1.txt", L1, A1, q);
    cout << "-----------------------------------------------"<<endl;
    cargar_coleccion("Datasets\\Coleccion_2.txt", L2, A2, q);
    cout << "Cargando coleccion_2 ..."<<endl;
    buscar_palabra("Datasets\\Busqueda_2.txt", "Resultado_2.txt", L2, A2, q);
    cout << "-----------------------------------------------"<<endl;
    cargar_coleccion("Datasets\\Coleccion_3.txt", L3, A3, q);
    cout << "Cargando coleccion_3 ..."<<endl;
    buscar_palabra("Datasets\\Busqueda_3.txt", "Resultado_3.txt", L3, A3, q);
    getch();
    return 0;
}

void cargar_coleccion(string path, lista<string> &L1, arbus<string> &A1, int q) {
    ifstream origen(path.c_str());
    if (!origen.is_open())
        cout << "No se pudo abrir el archivo: " << path << endl;
    else {
        if (q == 1){
            while (!origen.eof()) {
                string palabra;
                origen >> palabra;
                L1.Agregar_prin(palabra);
            }
        }
        else{
            if (q == 2){
                while (!origen.eof()) {
                    string palabra;
                    origen >> palabra;
                    A1.agregar_arbus(palabra);
                }
            }
        }
    }
}

void buscar_palabra(string pathBusqueda, string pathResultado, lista<string> &L1, arbus<string> &A1, int q){
    ifstream busqueda(pathBusqueda.c_str());
    if (!busqueda.is_open())
        cout << "No se pudo abrir el archivo: " << pathBusqueda << endl;
    else {
        ofstream resultado(pathResultado.c_str(), ios::trunc);
        if (q == 1){
            while (!busqueda.eof()) {
                string palabra;
                busqueda >> palabra;
                string existe = "No existe";
                if (L1.pertenece(palabra))
                    existe = "Existe";
                cout << palabra <<", "<< existe <<", costo: "<< L1.costo() <<endl;
                resultado << palabra <<","<< existe <<","<< L1.costo() << endl;
            }
        }
        else{
            while (!busqueda.eof()) {
                string palabra;
                busqueda >> palabra;
                string existe = "No existe";
                if (A1.pertenece(palabra))
                    existe = "Existe";
                int k = A1.costo();
                cout << palabra <<", "<< existe <<", costo: "<< k <<endl;
                resultado << palabra <<","<< existe <<","<< k << endl;
            }
        }
    }
}
