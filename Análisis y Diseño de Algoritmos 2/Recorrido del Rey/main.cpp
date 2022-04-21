#include <iostream>

using namespace std;

void MostrarMatriz(int tablero[3][3],int n){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            cout << tablero[i][j]<< " ";
        cout <<endl;
    }
    cout <<endl;
}

void RecorridoRey(int k,int tablero[3][3],int x,int y,int movX[8],int movY[8],int n)
{
    if (k == n*n)
        MostrarMatriz(tablero,n);
    else{
        for (int orden=1;orden!=9;orden++){
            int u= x+movX[orden];
            int v= y+movY[orden];
            if((u>=0) && (u<n) && (v>=0) && (v<n) && (tablero[u][v]==0)){
                tablero[u][v]=k;
                if (k < n*n){
                    RecorridoRey(k+1,tablero,u,v,movX,movY,n);
                    tablero[u][v]=0;
                }
            }
        }
    }
}

void MovimientosRey(int movX[8], int movY[8]){
    movX[1]=0; movY[1]=1;
    movX[2]=-1; movY[2]=1;
    movX[3]=-1; movY[3]=0;
    movX[4]=-1; movY[4]=-1;
    movX[5]=0; movY[5]=-1;
    movX[6]=1; movY[6]=-1;
    movX[7]=1; movY[7]=0;
    movX[8]=1; movY[8]=1;
}


void InicializarMatriz(int n,int tablero[][3]){
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            tablero[i][j]=0;
}

int main()
{
    int movX[8];
    int movY[8];
  //  cout << "ingrese el tamaño del tablero : " <<endl ;
  //  cin >>n;
    int tablero[3][3];
    InicializarMatriz(3,tablero);
    tablero[1][1]=1;
    MovimientosRey(movX,movY);
    RecorridoRey(2,tablero,1,1,movX,movY,3);
    return 0;
}
