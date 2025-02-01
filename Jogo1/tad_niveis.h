#include <iostream>
#include <cmath>
#define min(i) (pow(2, i) - 1)
using namespace std;

/*  O objetivo é fazer um sistema de níveis usando árvore 
    Uma pontuação baixa decresce a dificuldade do jogo, enquanto
    uma pontuação alta aumenta o nível do jogo. 
    A "pontuação" é baseada no número de jogadas que o jogador 
    levou para acabar com o jogo.
    Vou estabelecer um padrão de:
        0% - 25% de jogadas a mais: permite ir para a próxima fase;
        25% - 50% de jogadas a mais: repete a fase;
        50%+ de jogadas a mais: volta uma fase;
*/

struct Nível{
    int Dificuldade; /* informação armazenada */
    struct Nível* Seguinte; /* mesmo que PtrNode Dir */
    struct Nível* Anterior; /* mesmo que PtrNode Esq */
    int Estilo; /* Aí teria uma tabela para dizer 1- Bolo de chocolate, 2- Rosquinhas, etc. */
};

typedef struct Nível* PtrNível;

struct Níveis {
    PtrNível Início;
    PtrNível Atual;
};

/* -------------- OPERAÇÕES PRIMITIVAS -------------- */

void CriarNíveis(Níveis& N){
    N.Início = NULL;
    N.Atual = NULL;
}

PtrNível EncontraNível(Níveis& N, int Dif) { /* Dif é a dificuldade que quero encontrar */
    PtrNível atual = N.Início; 
    while (atual != NULL) {
        if (atual->Dificuldade == Dif) {
            return atual;
        }
        /* Avanço na árvore dependendo da dificuldade */
        if (Dif > atual->Dificuldade) {
            atual = atual->Seguinte;
        } else {
            atual = atual->Anterior;
        }
    }
    return NULL;
}

/* 
    OBS: A ordem inicial de inserção dos níveis deve ser 6, 4, 8
    obrigatoriamente. Depois pode vir o 3, 5, 7, 9 em qualquer ordem.
*/

/* Vou usar pra criar, na main, a árvore bonitinha dos níveis */
bool Inserir(Níveis& N, PtrNível& Atual, int Dif){ /* X sendo a dificuldade */
    if(Atual == NULL){
        PtrNível Aux = new Nível;
        Aux->Dificuldade = Dif;
        Aux->Seguinte = EncontraNível(N, Dif + 1);
        Aux->Anterior = EncontraNível(N, Dif - 1);
        Atual = Aux;
        Aux = NULL;
        if(N.Início == NULL)
            N.Início = Atual;
        return true;
    } else if (Atual->Dificuldade < Dif)
        return Inserir(N, Atual->Seguinte, Dif);
    else if (Atual->Dificuldade > Dif)
        return Inserir(N, Atual->Anterior, Dif);
    else 
        return false;
}

/* retorna True caso passe pro proxímo nível */
bool PróximoNível(PtrNível& Atual, int Tentativas){
    int minTentativas = min(Atual->Dificuldade);
    if(Tentativas <= 1.25 * minTentativas){
        Atual = Atual->Seguinte;
        return true;
    } else if (Tentativas <= 1.5 * minTentativas){
        return false;
    } else {
        Atual = Atual->Anterior;
        return false;
    }
}

void SetEstilo(Níveis& N, int Dif, int _Estilo){
    PtrNível Atual = EncontraNível(N, Dif);
    Atual->Estilo = _Estilo;
}

/* -------------- OPERAÇÕES NÃO-PRIMITIVAS --------------- */

/*void Imprimir(PtrNível& Atual){
    if(Atual != NULL){
        Imprimir(Atual->Anterior);
        cout << Atual->Dificuldade << " ";
        Imprimir(Atual->Seguinte);
    }
}*/

void ImprimirAtual(PtrNível& Atual){
    if(Atual != NULL)
        cout << "O nível atual tem dificuldade " << Atual->Dificuldade << "!";
    else
        cout << "O nível atual é nulo";
}