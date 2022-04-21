#include <iostream>
#include "Archivo.h"
#include "Diccionario.h"
#include "Lista.h"
#include "windows.h"
#include <stdlib.h>

using namespace std;

int Media(int n, int m, string X , string Y)
{
    int M[n+1][m+1];
    for (int i=0; i<= n ; i++)
        M[i][0] = i;
    for (int j=0; j<= m ; j++)
        M[0][j] = j;
    for (int i=1; i<= n ;i++){
        for (int j=1; j<= m ;j++){
            if (X[i-1] == Y[j-1])
                M[i][j] = M[i-1][j-1];
            else {
                M[i][j] = min (min(M[i-1][j], M[i][j-1]), M[i-1][j-1])+1;
                }
            }
        }
    return M[n][m];
}

string PalabraCorrecta(Archivo & Entrada,Diccionario & MiDiccionario, int i)
{
    string X=Entrada.ObtPalabra(i);
    int Long1=Entrada.ObtPalabra(i).length();
    for(int j=1; j <= MiDiccionario.Cantidad(); j++){
        int Long2=MiDiccionario.Palabra(j).length();
        string Y=MiDiccionario.Palabra(j);
        if (Media(Long1, Long2, X, Y) <= (Long1/2 + 1))
                return Y;
        }
    return X;
}

void EjecutarCorrector(Archivo & Entrada, Diccionario & MiDiccionario, Archivo & Salida)
{
    for (int i=1; i<= Entrada.Lineas(); i++)
        if (MiDiccionario.Existe(Entrada.ObtPalabra(i)))
            Salida.Agregar(Entrada.ObtPalabra(i));
          else
            Salida.Agregar(PalabraCorrecta(Entrada,MiDiccionario,i));
}

int main()
{
    Archivo Entrada;
    fstream Arch("entrada.txt");
    if (!Arch.is_open())
        cout << "No se abrio el archivo..";
    else{
        while (!Arch.eof()){
            string palabra;
            getline(Arch, palabra);
            Entrada.Agregar(palabra);
        }
    }
    Arch.close();
    Diccionario MiDiccionario;
    fstream Dicc("diccionario.txt");
    if (!Dicc.is_open())
        cout << "No se abrio el archivo..";
    else{
        while (!Dicc.eof()){
            string palabra;
            getline(Dicc, palabra);
            MiDiccionario.Agregar(palabra);
        }
    }
    Dicc.close();
    Archivo Salida;
    EjecutarCorrector(Entrada, MiDiccionario, Salida);
    Salida.Guardar();
    return 0;
}
