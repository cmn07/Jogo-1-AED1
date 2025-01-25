#include "tad_niveis.h"

int main(){
    Níveis N; CriarNíveis(N);

    Inserir(N.Atual, 6); Imprimir(N.Atual); cout << endl;
    Inserir(N.Atual, 4); Imprimir(N.Atual); cout << endl;
    Inserir(N.Atual, 8); Imprimir(N.Atual); cout << endl;

    for(int i = 3; i < 10; i += 2)
    {
        Inserir(N.Atual, i); Imprimir(N.Atual); cout << endl;
    }

    int Tentativas; /* só pra testar se ele faz certo */

    ImprimirAtual(N.Atual); cout << endl; /* Deve imprimir "6" */
    Tentativas = 63; /* Número mínimo da primeira fase (Nível 6) */
    PróximoNível(N.Atual, Tentativas);
    ImprimirAtual(N.Atual); cout << endl; /* Deve imprimir "8" */

    Tentativas = 500; /* Número acima de 50% da qntd mínima pro nível 8 */
    PróximoNível(N.Atual, Tentativas); 
    ImprimirAtual(N.Atual); cout << endl; /* Deve imprimir "7" */

    Tentativas = 180; /* Número que deve manter o jogador na mesma fase 7 */
    PróximoNível(N.Atual, Tentativas); 
    ImprimirAtual(N.Atual); cout << endl; /* Deve imprimir "7" */
}