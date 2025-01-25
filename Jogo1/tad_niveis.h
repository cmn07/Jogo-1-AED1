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
};

typedef struct Nível* PtrNível;

struct Níveis {
    PtrNível Atual;
};

/* -------------- OPERAÇÕES PRIMITIVAS -------------- */

void CriarNíveis(Níveis& N){
    N.Atual = NULL;
}

PtrNível EncontraNível(PtrNível& Atual, int Dif){ // Dif é a dificuldade do nível que quero encontrar
    if (Atual == NULL)
        return NULL;
    else if (Atual->Dificuldade == Dif)
        return Atual;
    else if (Dif > Atual->Dificuldade)
        return EncontraNível(Atual->Seguinte, Dif);
    else
        return EncontraNível(Atual->Anterior, Dif);
}

/* 
    OBS: A ordem inicial de inserção dos níveis deve ser 6, 4, 8
    obrigatoriamente. Depois pode vir o 3, 5, 7, 9 em qualquer ordem.
*/

/* Vou usar pra criar, na main, a árvore bonitinha dos níveis */
bool Inserir(PtrNível& Atual, int Dif){ /* X sendo a dificuldade */
    if(Atual == NULL){
        PtrNível Aux = new Nível;
        Aux->Dificuldade = Dif;
        Aux->Seguinte = EncontraNível(Atual, Dif + 1);
        Aux->Anterior = EncontraNível(Atual, Dif - 1);
        Atual = Aux;
        Aux = NULL;
        return true;
    } else if (Atual->Dificuldade < Dif)
        return Inserir(Atual->Seguinte, Dif);
    else if (Atual->Dificuldade > Dif)
        return Inserir(Atual->Anterior, Dif);
    else 
        return false;
}

/* retorna True caso passe pro proxímo nível */
bool PróximoNível(PtrNível& Atual, int Tentativas){
    if(Tentativas <= 1.25 * min(Atual->Dificuldade)){
        Atual = Atual->Seguinte;
        return true;
    } else if (Tentativas <= 1.5 * min(Atual->Dificuldade)){
        return false;
    } else {
        Atual = Atual->Anterior;
        return false;
    }
}

/* -------------- OPERAÇÕES NÃO-PRIMITIVAS --------------- */

void Imprimir(PtrNível& Atual){
    if(Atual != NULL){
        Imprimir(Atual->Anterior);
        cout << Atual->Dificuldade << " ";
        Imprimir(Atual->Seguinte);
    }
}

void ImprimirAtual(PtrNível& Atual){
    cout << "O nível atual tem dificuldade " << Atual->Dificuldade << "!";
}