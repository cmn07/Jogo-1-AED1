#include <iostream>
#include "torre.h"
#include "disco.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;

// Função que cria e desenha a tela inicial com a escolha do nível de dificuldade
void desenharTelaInicial(RenderWindow& window) {
    window.clear(sf::Color(135, 206, 235));

    // Carregar a fonte para o texto
    sf::Font font;
    if (!font.loadFromFile("asap.ttf")) {
        cout << "Erro ao carregar a fonte!" << endl;
        return;  // Encerra caso não consiga carregar a fonte
    }

    // Criar o texto de "Bem-vindo"
    sf::Text welcomeText;
    welcomeText.setFont(font);
    welcomeText.setString("Bem-vindo(a) ao jogo da Torre de Hanoi!");
    welcomeText.setCharacterSize(30);
    welcomeText.setFillColor(sf::Color::Black);
    welcomeText.setPosition(window.getSize().x / 2.0f - welcomeText.getLocalBounds().width / 2.0f, 100);
    window.draw(welcomeText);

    // Criar o texto para as opções de dificuldade
    sf::Text easyText;
    easyText.setFont(font);
    easyText.setString("Facil (3 discos)");
    easyText.setCharacterSize(30);
    easyText.setFillColor(sf::Color::Green);
    easyText.setPosition(window.getSize().x / 2.0f - easyText.getLocalBounds().width / 2.0f, window.getSize().y / 2.0f - 50);
    window.draw(easyText);

    sf::Text mediumText;
    mediumText.setFont(font);
    mediumText.setString("Medio (5 discos)");
    mediumText.setCharacterSize(30);
    mediumText.setFillColor(sf::Color::Green);
    mediumText.setPosition(window.getSize().x / 2.0f - mediumText.getLocalBounds().width / 2.0f, window.getSize().y / 2.0f + 50);
    window.draw(mediumText);

    sf::Text difficultText;
    difficultText.setFont(font);
    difficultText.setString("Dificil (7 discos)");
    difficultText.setCharacterSize(30);
    difficultText.setFillColor(sf::Color::Green);
    difficultText.setPosition(window.getSize().x / 2.0f - mediumText.getLocalBounds().width / 2.0f, window.getSize().y / 2.0f + 150);
    window.draw(difficultText);

    window.display();
}

// Função que verifica qual nível de dificuldade foi selecionado
int verificarCliqueNivel(RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    // Posições para os botões
    float btnWidth = 200;
    float btnHeight = 50;
    float xPos = window.getSize().x / 2.0f - btnWidth / 2.0f;
    float yPosEasy = window.getSize().y / 2.0f - 50;
    float yPosMedium = window.getSize().y / 2.0f + 50;
    float yPosDifficult = window.getSize().y / 2.0f + 150;

    // Verifica se o clique foi no botão de "Facil"
    if (mousePos.x >= xPos && mousePos.x <= xPos + btnWidth &&
        mousePos.y >= yPosEasy && mousePos.y <= yPosEasy + btnHeight) {
        return 3; // 3 discos para o nível fácil
    }

    // Verifica se o clique foi no botão de "Medio"
    if (mousePos.x >= xPos && mousePos.x <= xPos + btnWidth &&
        mousePos.y >= yPosMedium && mousePos.y <= yPosMedium + btnHeight) {
        return 5; // 5 discos para o nível médio
    }

    // Verifica se o clique foi no botão de "Dificil"
    if (mousePos.x >= xPos && mousePos.x <= xPos + btnWidth &&
        mousePos.y >= yPosDifficult && mousePos.y <= yPosDifficult + btnHeight) {
        return 7; // 7 discos para o nível dificil
    }

    return 0; // Nenhuma opção clicada
}

bool moverDisco(torre& origem, torre& destino, disco* discoMovido) {
    if (!destino.empilhar(discoMovido)) {
        cout << "Erro: o disco é maior que a base." << endl;
        origem.empilhar(discoMovido); // Reempilha na origem
        return false;
    }
    return true;
}

bool voceGanhou(torre& a, torre& b, int dificuldade)
{
    if (a.getNumeroDiscos() == dificuldade || b.getNumeroDiscos() == dificuldade)
        return true;
    return false;
}

int clicarNaTorre(int mouseX, int mouseY, int xTorre1, int yTorre1, int largura1, int altura1, int xTorre2, int yTorre2, int largura2, int altura2, int xTorre3, int yTorre3, int largura3, int altura3) {
    if (mouseX >= (xTorre1 - largura1 / 2) && mouseX <= (xTorre1 + largura1 / 2) &&
        mouseY >= yTorre1 && mouseY <= (yTorre1 + altura1)) {
        cout << "Cliquei na torre 1" << endl;
        return 1; // Torre 1 clicada
    }

    // Para a Torre 2
    if (mouseX >= (xTorre2 - largura2 / 2) && mouseX <= (xTorre2 + largura2 / 2) &&
        mouseY >= yTorre2 && mouseY <= (yTorre2 + altura2)) {
        cout << "Cliquei na torre 2" << endl;
        return 2; // Torre 2 clicada
    }

    // Para a Torre 3
    if (mouseX >= (xTorre3 - largura3 / 2) && mouseX <= (xTorre3 + largura3 / 2) &&
        mouseY >= yTorre3 && mouseY <= (yTorre3 + altura3)) {
        cout << "Cliquei na torre 3" << endl;
        return 3; // Torre 3 clicada
    }
    return 0;
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
        yOffSet += 50;  // Desloca para baixo o próximo disco (de cima para baixo)
        discoAtual = discoAtual->getProximo();  // Passa para o próximo disco
    }
}

void desenharDiscoDesempilhado(RenderWindow& window, disco* disco) {
    sf::Texture discoTexture;
    discoTexture.loadFromFile("bolopx.png");
    RectangleShape discoShape(Vector2f(disco->getTamanho() * 50, 50));
    discoShape.setTexture(&discoTexture);
    discoShape.setPosition(window.getSize().x / 2 - discoShape.getSize().x / 2, 50);
    window.draw(discoShape);
}

int main() {

    RenderWindow window(VideoMode(1280, 800), "Torre de Hanoi", sf::Style::Resize | sf::Style::Close);

    sf::Music musica;
    if (!musica.openFromFile("musica.ogg")) { 
        cout << "Erro ao carregar a música!" << endl;
        return -1;
    }
    musica.setLoop(true);  // Faz a música tocar em loop
    musica.play();  // Começa a tocar a música

    torre torre1;
    torre torre2;
    torre torre3;

    disco d1(1);
    disco d2(2);
    disco d3(3);
    disco d4(4);
    disco d5(5);
    disco d6(6);
    disco d7(7);

    // Separando a janela em três seções, cada seção terá o mesmo tamanho e uma torre
    float larguraSecao = window.getSize().x / 3.0f;

    // Definindo a posição da torre no eixo x
    float xTorre1 = larguraSecao / 2.0f;
    float xTorre2 = larguraSecao + larguraSecao / 2.0f;
    float xTorre3 = 2 * larguraSecao + larguraSecao / 2.0f;

    int alturaTorre = 300;
    int larguraTorre = 20;

    int status = 1;
    disco* discoSelect = nullptr;

    torre* torreOrigem = nullptr;
    torre* torreDestino = nullptr;

    // Tela inicial
    bool jogoIniciado = false;
    int dificuldade = 0;

    while (window.isOpen()) {
        Event event;

        if (!jogoIniciado) {
            // Tela inicial
            desenharTelaInicial(window);

            while (window.pollEvent(event)) {
                if (event.type == Event::Closed)
                    window.close();
                if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    dificuldade = verificarCliqueNivel(window);
                    if (dificuldade > 0) {
                        jogoIniciado = true; // Começar o jogo
                        // Inicializa as torres com a dificuldade selecionada
                        if (dificuldade == 3) {
                            torre1.empilhar(&d3);
                            torre1.empilhar(&d2);
                            torre1.empilhar(&d1);
                        } else if (dificuldade == 5) {
                            torre1.empilhar(&d5);
                            torre1.empilhar(&d4);
                            torre1.empilhar(&d3);
                            torre1.empilhar(&d2);
                            torre1.empilhar(&d1);
                        }
                        else if (dificuldade == 7) {
                            torre1.empilhar(&d7);
                            torre1.empilhar(&d6);
                            torre1.empilhar(&d5);
                            torre1.empilhar(&d4);
                            torre1.empilhar(&d3);
                            torre1.empilhar(&d2);
                            torre1.empilhar(&d1);
                        }
                    }
                }
            }
        } else {
            // Jogo da Torre de Hanoi
            window.clear(sf::Color(135, 206, 235));

            desenharTorre(window, xTorre1, alturaTorre, larguraTorre, torre1.getTopo());
            desenharTorre(window, xTorre2, alturaTorre, larguraTorre, torre2.getTopo());
            desenharTorre(window, xTorre3, alturaTorre, larguraTorre, torre3.getTopo());

            if (status == 2) {
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
                            torreOrigem = &torre1;
                        }
                        else if (torreClicada == 2) {
                            torreOrigem = &torre2;
                        }
                        else if (torreClicada == 3) {
                            torreOrigem = &torre3;
                        }
                        if (torreOrigem != nullptr && torreOrigem->getTopo() != nullptr) {
                            discoSelect = torreOrigem->getTopo();
                            torreOrigem->desempilhar(discoSelect);
                            status = 2;
                        }
                    }

                    else if (status == 2 && discoSelect != nullptr) {
                        if (torreClicada == 1) {
                            torreDestino = &torre1;
                        }
                        else if (torreClicada == 2) {
                            torreDestino = &torre2;
                        }
                        else if (torreClicada == 3) {
                            torreDestino = &torre3;
                        }
                        if (torreDestino != nullptr) {
                            moverDisco(*torreOrigem, *torreDestino, discoSelect);
                            discoSelect = nullptr;
                            status = 1;
                            torreDestino = nullptr;
                            torreOrigem = nullptr;
                        }
                    }
                    if (voceGanhou(torre2, torre3, dificuldade)) {
                        // Exibir a mensagem de vitória
                        sf::Font font;
                        if (!font.loadFromFile("asap.ttf")) {
                            cout << "Erro ao carregar a fonte!" << endl;
                            return -1; // Encerra o programa caso a fonte não seja carregada
                        }

                        sf::Text victoryText;
                        victoryText.setFont(font);
                        victoryText.setString("Parabéns!");
                        victoryText.setCharacterSize(50);
                        victoryText.setFillColor(sf::Color::Magenta);

                        sf::FloatRect textRect = victoryText.getLocalBounds();
                        victoryText.setOrigin(textRect.width / 2, textRect.height / 2);
                        victoryText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

                        window.clear(sf::Color(135, 206, 235));
                        window.draw(victoryText);
                        window.display();

                        sf::sleep(sf::seconds(3));
                        window.close();
                    }
                }
            }

            window.display();
        }
    }

    return 0;
}
