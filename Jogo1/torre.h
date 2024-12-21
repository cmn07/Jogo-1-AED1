#include <iostream>
#include "disco.h"
using namespace std;


class torre
{
private:
    disco* topo; /* ponteiro para o disco do topo da torre */
    int numeroDiscos; /* quantidade de discos da torre */
    int posicao;
    static int contagemPosicao;
public:
    torre();
    int getNumeroDiscos() const;
    int getPosicao() const;
    bool vazia() const;
    bool empilhar(disco*);
    bool desempilhar(disco*&);
    disco* getTopo() const;
};



