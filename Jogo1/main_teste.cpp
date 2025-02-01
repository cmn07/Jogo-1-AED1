#include "tad_niveis.h"

int main(){
    Níveis N; CriarNíveis(N);

    Inserir(N, N.Atual, 6); //Imprimir(N.Início); cout << endl;
    Inserir(N, N.Atual, 4); //Imprimir(N.Início); cout << endl;
    Inserir(N, N.Atual, 8); //Imprimir(N.Início); cout << endl;

    for(int i = 3; i < 10; i += 2)
    {
        Inserir(N, N.Atual, i); //Imprimir(N.Início); cout << endl;
    }

    N.Atual = N.Início;

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

    Tentativas = 128; /* Suficiente para passar de nível */
    PróximoNível(N.Atual, Tentativas);
    ImprimirAtual(N.Atual); cout << endl; /* Deve imprimir "8" */
}