#include <iostream>


struct disco{
    int tamanho; /* tamanho do disco */
    struct disco *próx; /* ponteiro para o próximo disco */
};

typedef struct disco *ptr_disco; /* tipo ponteiro para disco */

typedef struct{
    ptr_disco topo;
    int numeroDiscos; /* usada pra depois verificar se uma
    torre, sem ser a da direita, está cheia, indicando, assim,
    jogo concluído */
}torre;

void criarTorre(torre *a){
    a->topo = NULL;
    a->numeroDiscos = 0;
}

/* acho que deve criar uma torre
   já cheia... talvez só na main??? */

bool torreVazia(torre *a){
    if(a->topo == NULL)
        return true;
    else
        return false;
}

bool empilhar(torre *a, ptr_disco d){ /* retorna true se consegue empilhar */
    if(torreVazia(a)){
        a->topo = d;
        d->próx = NULL;
        a->numeroDiscos++;
        return true;
    } else {
        if(d->tamanho > a->topo->tamanho)
            return false; /* tamanho do disco é maior que o disco de baixo */
        else{
            d->próx = a->topo; 
            a->topo = d;
            a->numeroDiscos++;
            return true;
        }
    }
}

bool desempilhar(torre *a, ptr_disco *e){ /* retorna true se consegue desempilhar*/
    if(torreVazia(a))
        return false;
    else{
        *e = a->topo;
        a->topo = a->topo->próx;
        a->numeroDiscos--;
        return true;
    }
} /* preciso armazenar o ponteiro do antigo topo para colocar esse disco em outro lugar */