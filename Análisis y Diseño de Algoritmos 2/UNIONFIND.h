#ifndef AYDAII_UNIONFIND_H
#define AYDAII_UNIONFIND_H

class UNIONFIND {

    public:
        UNIONFIND(int tamanio);
        void unir(int i , int j);
        int buscar(int i) const;
        void mostrar();
        ~UNIONFIND();

    private:
        int*p;
        int tamanio;
        const int DISCERNIBLE = -1;
};


#endif //AYDAII_UNIONFIND_H
