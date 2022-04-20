#include <iostream>
#include "arbus.h"

using namespace std;

int main(){
    arbus<int> A1;
    A1.agregar_arbus(9); //9
    A1.agregar_arbus(4); //4-9
    A1.agregar_arbus(25); //4-9-25
    A1.agregar_arbus(25); //4-9-25-25
    cout << "cantidad de elementos del arbol: "<<  A1.cant_elementos()<<endl; //4
    if (A1.vacio_arbus()) //false
        cout <<"el arbol esta vacio" << endl;
    else
        cout <<"el arbol tiene elementos"<<endl;
    A1.inorden();  //4-9-25-25
    int j = 0;
    cout <<" "<< endl;
    cout << "consulte un valor que pertenezca o no en el arbol"<<endl;
    cin >> j;
    if (A1.pertenece(j)){
        cout << "pertenece" << endl;
        cout << "costo: " << A1.costo() <<endl;
    }
    else{
        cout << "no pertenece"<< endl;
        cout << "costo: " << A1.costo() <<endl;
    }
    A1.inorden();
    return 0;
}
