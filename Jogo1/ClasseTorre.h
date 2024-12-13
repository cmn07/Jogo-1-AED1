#include <iostream>
using namespace std;

struct disco
{
    int tamanho; /* tamanho do disco */
    struct disco *próximo; /* ponteiro para o próximo disco */
};

typedef struct disco *ptrDisco;

class torre
{
    private:
        ptrDisco topo; /* ponteiro para o disco do topo da torre */
        int numeroDiscos; /* quantidade de discos da torre */
        int posição;
        static int contagemPosição;
    public:
        torre();
        int getNumeroDiscos() const;
        int getPosição() const;
        bool vazia() const;
        bool empilhar(ptrDisco);
        bool desempilhar(ptrDisco&);
};

torre::torre()
{
    topo = NULL;
    numeroDiscos = 0;
    posição = ++contagemPosição;
}

int torre::getNumeroDiscos() const
{
    return numeroDiscos;
}

int torre::getPosição() const
{
    return posição;
}

bool torre::vazia() const
{
    if(topo == NULL)
        return true;
    else
        return false;
}

bool torre::empilhar(ptrDisco D)
{
    if(vazia())
    {
        topo = D;
        D->próximo = NULL;
        numeroDiscos++;
        return true;
    } 
    else
    {
        if(D->tamanho > topo->tamanho)
            return false;
        else
        {
            D->próximo = topo;
            topo = D;
            numeroDiscos++;
            return true;
        }
    }
}

bool torre::desempilhar(ptrDisco& D)
{
    if(vazia())
        return false;
    else
    {
        D = topo;
        topo = topo->próximo;
        numeroDiscos--;
        return true;
    }
}

/* agora as funções globais */

void encherEsquerda(torre& T, int dificuldade)
{
    ptrDisco D;
    for(int i = dificuldade; i > 0; i--)
    {
        D = new disco;
        D->tamanho = i;
        T.empilhar(D);
    }
}

bool moverDisco(torre& origem, torre& destino)
{
    ptrDisco D;
    if(!origem.desempilhar(D))
    {
        cout << "Erro ao desempilhar torre vazia." << endl;
        return false;
    }
    if(!destino.empilhar(D))
    {
        cout << "Erro: o disco é maior que a base." << endl;
        origem.empilhar(D);
        return false;
    }
    return true;
}

bool vocêGanhou(torre& a, torre& b, int dificuldade)
{
    if(a.getNumeroDiscos() == dificuldade || b.getNumeroDiscos() == dificuldade)
        return true;
    return false;
}

