#include <iostream>

using namespace std;

struct objeto{
    int peso;
    int valor;
};

void mochila(objeto x[],int solucion[],int n,int p)
{
  //  ordenar(x,n);
    for(int i=0;i<n;i++)
        solucion[i]=0;
    for(int i=0;i<n;i++)
        if(p>0)
            if(x[i].peso<=p){
                solucion[i]=1;
                p-=x[i].peso;
            }
            else{
                solucion[i]=x[i].valor*(x[i].valor/p);
                p-=x[i].peso*(x[i].valor/p);
            }
}

int main()
{
    objeto x[3];
    x[1].peso=10;
    x[1].valor=25;
    x[2].peso=24;
    x[2].valor=15;
    x[3].peso=23;
    x[3].valor=18;
    int solucion[3];
    mochila(x,solucion,3,20);
    for(int i=0;i<3;i++)
        cout<<solucion[i]<<" ";
    return 0;
}
