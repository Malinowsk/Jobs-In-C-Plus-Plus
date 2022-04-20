#include <iostream>
#include "lista.h"

using namespace std;

int main(){

    lista<int> L1;
    L1.Agregar_prin(4); // 4
    cout << L1.longitud() <<endl; //1
    L1.Agregar_final(5); // 4 5
    cout << L1.longitud() << endl; //2
    L1.Agregar_pos(1, 2); // 4 1 5
    cout << L1.longitud() << endl; //3
    if (L1.pertenece(4)) //true
        cout << "Existe ";
    else
        cout << "No existe ";
    cout << "costo: " << L1.costo() <<endl; //1
    if (L1.pertenece(3)) //false
        cout << "Existe ";
    else
        cout << "No existe ";
    cout << "costo: " << L1.costo() <<endl; //3
    L1.imprimir(); //4 1 5
    L1.Elimina_elem(1); // true
    L1.imprimir(); // 4 5
    cout << L1.longitud() << endl; //2
    L1.Elimina_elem(7); //false
    L1.imprimir(); // 4 5
    cout << L1.longitud() << endl; // 2
    L1.Elimina_lista();
    L1.imprimir();
    cout << L1.longitud() << endl;

    return 0;
}
