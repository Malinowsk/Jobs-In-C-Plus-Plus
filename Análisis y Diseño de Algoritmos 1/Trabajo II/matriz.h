#ifndef MATRIZ_H_INCLUDED
#define MATRIZ_H_INCLUDED
#include <string>

using namespace std;

class matriz{


private:
    float **matriz_frecuencia;
    string **matriz_string;
    int n;
public:
    matriz (int n);          //CB
    ~matriz();           //Destructora
    void agregar (int fila,int columna,float frecuencia, string palabra); //CB
    int obtener_tam () const; //OBS
    float obtener_frecuencia (int fila, int columna) const;
    string obtener_palabra (int fila, int columna) const;

};

#endif // MATRIZ_H_INCLUDED
