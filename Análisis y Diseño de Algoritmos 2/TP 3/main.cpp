#include <iostream>
#include <map>
#include <tgmath.h>
#include <stack>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>

#define PI 3.14159265

using namespace std;

class Punto {
public:
    Punto() {}
    Punto(int x, int y) { this->x = x; this->y = y; }
    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    void operator = (Punto & p) {
        x = p.x;
        y = p.y;
    }
    bool operator == (const Punto & p) const{
        if ((x == p.x) && ( y == p.y))
            return true;
        return false;
    }
private:
    int x, y;
};

ostream & operator << (ostream & stream, const Punto & punto) {
return stream <<punto.getX() <<","<< punto.getY();
}

double CalcularAngulo(Punto P0,Punto P)
{
    return atan2(P.getY()-P0.getY(),P.getX()-P0.getX())* 180 / PI;;
}

Punto MenorY(Punto Puntos[],int Cantidad)
{
    Punto P0=Puntos[0];
    for(int i=1; i<Cantidad; i++)
    {
        Punto P=Puntos[i];
        if (P.getY() < P0.getY())
            P0=P;
    }
    return P0;
}

void PuntosOrdAngulos(Punto Puntos[],Punto P0,map<double,Punto> & PuntoOrdenados,int cantidad)
{
    map<double,Punto>::iterator it;
    for(int i=0; i<cantidad; i++)
    {
        Punto P=Puntos[i];
        double AnguloP=CalcularAngulo(P0,P);
        if (!(P==P0)){
            it=PuntoOrdenados.find(AnguloP);
            if (it == PuntoOrdenados.end())
                PuntoOrdenados[AnguloP] = P;
            else
            {
            if(P.getY() > it->second.getY())
                PuntoOrdenados[AnguloP] = P;
            }
        }
    }
}

/*
void MostrarMapa(map<double,Punto> Q)
{
    map<double,Punto>::iterator itA;
    for(itA=Q.begin() ; itA!=Q.end() ;itA++)
    {
        Punto P=itA->second;
        cout << itA->first << " "<<  P.getX() << " " << P.getY() << endl;
    }
}*/

bool GiraAlaDerecha(Punto Next_to_top,Punto Top,Punto Pi) {
//Producto vectorial
    int Prod_Vectorial = (Top.getX() - Next_to_top.getX()) * (Pi.getY() - Next_to_top.getY()) - (Top.getY() - Next_to_top.getY()) * (Pi.getX() - Next_to_top.getX());
    if (Prod_Vectorial < 0)
        return true;
    return false;
}

stack<Punto> Graham(Punto Puntos[],int cantidad)
{
    Punto P0=MenorY(Puntos,cantidad);
    map<double,Punto> PuntoOrdenados;
    PuntosOrdAngulos(Puntos,P0,PuntoOrdenados,cantidad);
    stack<Punto> Pila;
    if (PuntoOrdenados.size()+1 >= 3) {
        Pila.push(P0);
        map<double,Punto>::iterator it=PuntoOrdenados.begin();
        Punto P=it->second;
        Pila.push(P);
        it++;
        P=it->second;
        Pila.push(P);
        it++;
        for (it ;it!=PuntoOrdenados.end() ;it++)
        {
            Punto top = Pila.top();
            Pila.pop();
            while(GiraAlaDerecha(Pila.top(), top, it->second)){
                top = Pila.top();
                Pila.pop();
            }
            Pila.push(top);
            Pila.push(it->second);
        }
    }
    return Pila;
}

double area_triangulo (Punto p0,Punto p1,Punto p2)
{
    double area;
    area = (p1.getX()-p0.getX())*(p2.getY()-p0.getY()) - (p1.getY()-p0.getY())*(p2.getX()-p0.getX());
    return area*0.5;
}

double Area(stack<Punto> Solucion)
{
    double Suma=0;
    Punto p0(0,0);
    Punto p,p1,p2;
    if (!Solucion.empty()){
        p1 = Solucion.top();
        p=p1;
        Solucion.pop();
    }
    while (!Solucion.empty())  {
        p2 = Solucion.top();
        Solucion.pop();
        Suma+= area_triangulo(p1,p2,p0);
        p1 = p2;
    }
    Suma+= area_triangulo(p1,p,p0);
    if(Suma < 0)
        return Suma*(-1);
    return Suma;
}

void CargarValores(int valores[],int Tam,ifstream & Arch)
{
    char *dato;
    char *Linea=new char;
    Arch >> Linea;
    dato = strtok (Linea,",");
    for(int i=0; i<Tam ; i++){
        valores[i]=atoi(dato);
        dato = strtok (NULL, ",");
    }
    delete Linea;
}

void CargarDatos(ifstream & Arch,Punto * & Puntos,int & cantidad)
{
    int valores[2];
    //Primera linea
    CargarValores(valores,1,Arch);
    cantidad = valores[0];
    Puntos=new Punto[cantidad];
    //Siguiente linea
    Punto P;
    for(int i=0;i<cantidad;i++){
        CargarValores(valores,2,Arch);
        P.setX(valores[0]);
        P.setY(valores[1]);
        Puntos[i]=P;
    }
}

int CantidadVertices(stack<Punto> Solucion)
{
    int cant=0;
    while(!Solucion.empty()){
        cant++;
        Solucion.pop();
    }
    return cant;
}

void GuardarDatos(ofstream & ArchS,stack<Punto> Solucion)
{
    if(Solucion.empty())
    {
        ArchS<<"Si no se encontró solución:"<<endl;
        ArchS<<-1;

    }
    else{
        Punto P;
        int cant=CantidadVertices(Solucion);
        double area=Area(Solucion);
        ArchS<<cant<<endl;
        ArchS<<area<<endl;
        while (!Solucion.empty()){
            P = Solucion.top();
            Solucion.pop();
            ArchS<<P.getX()<<","<<P.getY() <<endl;
        }
    }
}

int main()
{
    Punto * Puntos;
    int cantidad;
    ifstream ArchE("Entrada.txt");
    if (!ArchE.is_open())
        cout << "No se abrio el archivo..";
    else{
        CargarDatos(ArchE,Puntos,cantidad);
        }
    ArchE.close();
    stack<Punto> Solucion = Graham(Puntos,cantidad);
    ofstream ArchS("Salida.txt");
    if (!ArchS.is_open())
        cout << "No se abrio el archivo..";
    else{
        GuardarDatos(ArchS,Solucion);
        }
    ArchS.close();
    delete [] Puntos;
    return 0;
}
