#include <iostream>
#include "torre.h"
#include "disco.h"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

/* agora as funções globais */

/*void encherEsquerda(torre& T, int dificuldade)
{
    disco* D;
    for (int i = dificuldade; i > 0; i--)
    {
        D = new disco;
        D->setTamanho(i);
        T.empilhar(D);
    }
}*/

bool moverDisco(torre& origem, torre& destino)
{
    disco* D;
    if (!origem.desempilhar(D))
    {
        cout << "Erro ao desempilhar torre vazia." << endl;
        return false;
    }
    if (!destino.empilhar(D))
    {
        cout << "Erro: o disco é maior que a base." << endl;
        origem.empilhar(D);
        return false;
    }
    return true;
}

bool vocêGanhou(torre& a, torre& b, int dificuldade)
{
    if (a.getNumeroDiscos() == dificuldade || b.getNumeroDiscos() == dificuldade)
        return true;
    return false;
}


int clicarNaTorre(int mouseX, int mouseY, int xTorre1, int yTorre1, int largura1, int altura1, int xTorre2, int yTorre2, int largura2, int altura2, int xTorre3, int yTorre3, int largura3, int altura3) {
    if (mouseX >= xTorre1 && mouseX <= (xTorre1 + largura1) && mouseY >= yTorre1 && mouseY <= (yTorre1 + altura1)) {
        return 1; // Torre 1 clicada
        cout << "Cliquei na torre 1";
    }
    if (mouseX >= xTorre2 && mouseX <= (xTorre2 + largura2) && mouseY >= yTorre2 && mouseY <= (yTorre2 + altura2)) {
        return 2; // Torre 2 clicada
        cout << "Cliquei na torre 2";
    }
    if (mouseX >= xTorre3 && mouseX <= (xTorre3 + largura3) && mouseY >= yTorre3 && mouseY <= (yTorre3 + altura3)) {
        return 3; // Torre 3 clicada
        cout << "Cliquei na torre 3";
    }
    return 0; // Nenhuma torre clicada
}


void desenharTorre(RenderWindow& window, int xPos, int altura, int largura, disco* topo) {
    sf::Texture torreTexture;
    sf::Texture discoTexture;
    discoTexture.loadFromFile("bolopx.png");
    discoTexture.setRepeated(true);

    // Desenhar a torre (um retângulo para representar a torre)
    RectangleShape baseShape(Vector2f(largura * 15, 30));
    RectangleShape torreShape(Vector2f(20, altura)); // Corpo da torre
    torreShape.setFillColor(Color::White);
    torreShape.setPosition(xPos - largura / 2, 300); // Centralizar a torre no ponto xPos
    baseShape.setFillColor(Color::White);
    baseShape.setPosition(xPos - largura * 7.5, altura + 300); //Definindo posição da base da torre
    window.draw(torreShape);
    window.draw(baseShape);


    // Calcular o número total de discos na torre
    int totalDiscos = 0;
    disco* temp = topo;
    while (temp != nullptr) { // Conta o número de discos
        totalDiscos++;
        temp = temp->getProximo();
    }

    // Desenhar os discos na torre (do maior para o menor)
    int yBase = altura + 300; // Definindo a altura da base
    int yOffSet = yBase - (totalDiscos * 50);
    disco* discoAtual = topo;  // Ponteiro para o topo da torre
    while (discoAtual != nullptr) {
        RectangleShape discoShape(Vector2f(discoAtual->getTamanho() * 50, 50)); // Largura proporcional ao tamanho
        discoShape.setTexture(&discoTexture);
        discoShape.setPosition(xPos - discoShape.getSize().x / 2, yOffSet);
        window.draw(discoShape);
        yOffSet += 50;  // Desloca para baixo o proximo disco (de cima para baixo)
        discoAtual = discoAtual->getProximo();  // Passa para o proximo disco
    }
}

void desenharDiscoDesempilhado(RenderWindow& window, disco* disco) {
    sf::Texture discoTexture;
    discoTexture.loadFromFile("bolopx.png");
    RectangleShape discoShape(Vector2f(disco->getTamanho() * 50, 50));
    discoShape.setTexture(&discoTexture);
    discoShape.setPosition(window.getSize().x / 2, 50);
    window.draw(discoShape);
}

int main() {

    RenderWindow window(VideoMode(1280, 800), "Torre de Hanoi", sf::Style::Resize | sf::Style::Close);

    torre torre1;
    torre torre2;
    torre torre3;

    disco d1(1);
    disco d2(2);
    disco d3(3);
    disco d4(4);
    disco d5(5);

    torre1.empilhar(&d5);
    torre1.empilhar(&d4);
    torre1.empilhar(&d3);
    torre1.empilhar(&d2);
    torre1.empilhar(&d1);

    //Separando a janela em três seções, cada seção terá o mesmo tamanho e uma torre
    float larguraSecao = window.getSize().x / 3.0f;

    //Definindo a posição da torre no eixo x
    float xTorre1 = larguraSecao / 2.0f;
    float xTorre2 = larguraSecao + larguraSecao / 2.0f;
    float xTorre3 = 2 * larguraSecao + larguraSecao / 2.0f;

    int alturaTorre = 300;
    int larguraTorre = 20;

    int status = 1;
    disco* discoSelect = nullptr;

    torre torreOrigem;
    torre torreDestino;


    while (window.isOpen()) {
        Event event;
        window.clear(sf::Color(135, 206, 235));

        desenharTorre(window, xTorre1, alturaTorre, larguraTorre, torre1.getTopo());
        desenharTorre(window, xTorre2, alturaTorre, larguraTorre, torre2.getTopo());
        desenharTorre(window, xTorre3, alturaTorre, larguraTorre, torre3.getTopo());

        if (status == 2 && discoSelect != nullptr) {
            desenharDiscoDesempilhado(window, discoSelect);
        }

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i posicaoMouse = sf::Mouse::getPosition(window);
                
                int torreClicada = clicarNaTorre(posicaoMouse.x, posicaoMouse.y,
                    xTorre1, 300, larguraSecao, alturaTorre,
                    xTorre2, 300, larguraSecao, alturaTorre,
                    xTorre3, 300, larguraSecao, alturaTorre);
                if (status == 1) {
                    if (torreClicada == 1) {
                        status = 2;
                        torreOrigem = torre1;
                        discoSelect = torreOrigem.getTopo();
                        torreOrigem.desempilhar(discoSelect);
                    }
                    else if (torreClicada == 2) {
                        status = 2;
                        torreOrigem = torre2;
                        discoSelect = torreOrigem.getTopo();
                        torreOrigem.desempilhar(discoSelect);
                    }
                    else if (torreClicada == 3) {
                        status = 2;
                        torreOrigem = torre3;
                        discoSelect = torreOrigem.getTopo();
                        torreOrigem.desempilhar(discoSelect);
                    }
                }
                else if (status == 2) {
                    if (torreClicada == 1) {
                        torreDestino = torre1;
                    }
                    else if (torreClicada == 2) {
                        torreDestino = torre2;
                    }
                    else if (torreClicada == 3) {
                        torreDestino = torre3;
                    }
                    if (moverDisco(torreOrigem, torreDestino)) {
                        status = 1;
                        discoSelect = nullptr;
                    }
                    

                }
            }

        }

        window.display();


    }

    return 0;
}