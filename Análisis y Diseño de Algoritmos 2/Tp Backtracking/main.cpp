#include <iostream>
#include <list>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <cstdlib>

using namespace std;

class Punto {
public:
    Punto(int x, int y) { this->x = x; this->y = y; }
    int getX() const { return x; }
    int getY() const { return y; }
    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    bool operator = (const Punto & p) const{
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


void Movimientos(int MovX[],int MovY[]){
    MovX[0]=0;     MovY[0]=-1;
    MovX[1]=0;      MovY[1]=1;
    MovX[2]=-1;      MovY[2]=0;
    MovX[3]=1;      MovY[3]=0;
}

bool ConPoda(int Energia,int Costo,Punto Inicial,Punto Final)
{
    if (Energia-Costo < 0)
        return true;
    if( (abs(Inicial.getX()-Final.getX()) + abs(Inicial.getY()-Final.getY())+2) > Energia)
       return true;
    return false;
}


bool SinPoda(int Energia)
{
    if (Energia < 0)
        return true;
    return false;
}

bool Visitado(list<Punto> Puntos,int x,int y)
{
    Punto Nuevo(x,y);
    list<Punto>::iterator it=Puntos.begin();
    for(it ; it != Puntos.end() ; it ++){
        if ( *it = Nuevo)
            return true;
    }
}

void back(Punto Inicial,Punto Final,list<Punto> & Puntos,int ** matriz,int & Energia,int MovX[],int MovY[],int ancho,int alto,bool & encontrado,int & estados)
{
    estados+=1;
    if (Inicial=Final){
        if(Energia>=0)
                encontrado = true;
        }
    else{
        for(int i=0; i<4 && !encontrado; i++){
            int x=Inicial.getX()+MovX[i];
            int y=Inicial.getY()+MovY[i];
            if((x>=0) && (x<alto) && (y>=0) && (y<ancho) )
                if (!Visitado(Puntos,x,y)){
                    if (!ConPoda(Energia,matriz[x][y],Inicial,Final)){
                   // if (!SinPoda(Energia)){
                        Energia-=matriz[x][y];
                        Punto Siguiente(x,y);
                        Puntos.push_back(Siguiente);
                        back(Siguiente,Final,Puntos,matriz,Energia,MovX,MovY,ancho,alto,encontrado,estados);
                        if (!encontrado){
                            Puntos.pop_back();
                            Energia+=matriz[x][y];
                        }
                    }
                }
            }
        }
}

void CrearMatriz(int ** & matriz, int ancho, int alto) {
    matriz = new int*[alto];
    for (int f = 0; f < alto; f++)
        matriz[f] = new int[ancho];
}

void EliminarMatriz(int ** & matriz, int ancho, int alto) {
    for (int f = 0; f < alto; f++)
        delete [] matriz[f];
    delete [] matriz;
    matriz = 0;
}

void MostrarMatriz(int ** matriz, int ancho, int alto) {
    for (int f = 0; f < alto; f++) {
        for (int c = 0; c < ancho; c++)
            cout << matriz[f][c] << " ";
        cout << "\n";
    }
}

void CargarValores(int valores[],int Tam,ifstream & Arch)
{
    char *dato;
    char *Linea=new char;
    Arch>>Linea;
    dato = strtok (Linea,",");
    for(int i=0; i<Tam ; i++){
        valores[i]=atoi(dato);
        dato = strtok (NULL, ",");
    }
    delete Linea;
}

void CargarDatos(ifstream & Arch,int & Energia,Punto & Inicial,Punto & Final,int ** & matriz,int & ancho,int & alto)
{
   int valores[3];
    //Primera linea
    CargarValores(valores,3,Arch);
    Energia=valores[0];
    alto=valores[1];
    ancho=valores[2];
    CrearMatriz(matriz,ancho,alto);
    //Segunda linea
    CargarValores(valores,2,Arch);
    Inicial.setX(valores[0]);
    Inicial.setY(valores[1]);
    //Tercera linea
    CargarValores(valores,2,Arch);
    Final.setX(valores[0]);
    Final.setY(valores[1]);
    //Cargar Matriz
    int * ArrEnergias=new int[ancho];
    for(int i=0;i<alto;i++){
        CargarValores(ArrEnergias,ancho,Arch);
            for(int j=0;j<ancho;j++){
                matriz[i][j]=ArrEnergias[j];
            }
    }
    delete [] ArrEnergias;
}

void GuardarDatos(ofstream & ArchS,int estados,int Energia,bool encontrado,list<Punto> Puntos,int ** matriz)
{
    ArchS<<estados<<endl;
    ArchS<<Energia<<endl;
    if(!encontrado)
       ArchS<<-1;
    else{
        list<Punto>::iterator it;
        for (it=Puntos.begin() ; it != Puntos.end(); it++){
            Punto Nuevo=*it;
            ArchS<< *it<<","<<matriz[Nuevo.getX()][Nuevo.getY()]<<endl;
        }
    }
}

int main()
{
    //Inicializo los puntos con cualquier valor
    Punto Inicial(0,0);
    Punto Final(0,0);
    //Lista solucion
    list<Punto> Puntos;
    //Movimientos Posibles
    int MovX[4];
    int MovY[4];
    Movimientos(MovX,MovY);
    //Tablero
    int ** Matriz = 0;
    int Ancho,Alto,Energia;
    ifstream ArchE("Entrada.txt");
    if (!ArchE.is_open())
        cout << "No se abrio el archivo..";
    else{
        CargarDatos(ArchE,Energia,Inicial,Final,Matriz,Ancho,Alto);
        }
    ArchE.close();
    Puntos.push_back(Inicial);
    bool Encontrado =false;
    int estados=0;
    Energia-=Matriz[Inicial.getX()][Inicial.getY()];
    back(Inicial,Final,Puntos,Matriz,Energia,MovX,MovY,Ancho,Alto,Encontrado,estados);
    ofstream ArchS("Salida.txt");
    if (!ArchS.is_open())
        cout << "No se abrio el archivo..";
    else{
        GuardarDatos(ArchS,estados,Energia,Encontrado,Puntos,Matriz);
        }
    ArchS.close();
    EliminarMatriz(Matriz,Ancho,Alto);
    return 0;
}
