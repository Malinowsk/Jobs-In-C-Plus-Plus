#include <iostream>


using namespace std;

int abs(int x,int y){
    if (x>y)
        return x-y;
    else
        return y-x;
}

bool valido(int solucion[],int k){
    for(int i=0; i< k; i++)
        if((solucion[i] == solucion[k]) || (abs(solucion[i],solucion[k]) == abs(i,k)))
            return false;
    return true;
}

void imprimir(int solucion[],int CantReinas)
{
    for (int i=0; i<CantReinas; i++)
        cout << solucion[i] << " ";
    cout << endl;
}

void Reinas(int CantReinas,int solucion[], int k)
{
    if(k == CantReinas){
        imprimir(solucion,CantReinas);
        break;
        }
    else
        for(int i=0;i < CantReinas; i++){
            solucion[k]=i+1;
            if(valido(solucion,k))
                if(k != CantReinas)
                    Reinas(CantReinas,solucion,k+1);
        }
}

int main()
{
    int CantReinas=4;
    int k=0;
    int solucion[4];
    Reinas(CantReinas,solucion,k);
    for (int i=0; i<CantReinas; i++)
        cout << solucion[i] << " ";
    return 0;
}
