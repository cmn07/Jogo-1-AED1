#include <iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

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

/* acha que deve criar uma torre
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

bool desempilhar(torre *a, ptr_disco &e){ /* retorna true se consegue desempilhar */
    if(torreVazia(a))
        return false;
    else{
        e = a->topo;
        a->topo = a->topo->próx;
        a->numeroDiscos--;
        return true;
    }
}

bool clicarNaTorre(int mouseX, int mouseY, int torreX, int torreY, int largura, int altura) {
    return mouseX >= torreX && mouseX <= (torreX + largura) && mouseY >= torreY && mouseY <= (torreY + altura);
}

void desenharTorre(RenderWindow &window, int xPos, int altura, int largura, ptr_disco topo) {
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
    ptr_disco temp = topo;
    while (temp != nullptr) { // Conta o número de discos
        totalDiscos++;
        temp = temp->próx;
    }

    // Desenhar os discos na torre (do maior para o menor)
    int yBase = altura + 300; // Definindo a altura da base
    int yOffSet = yBase - (totalDiscos * 50);
    ptr_disco discoAtual = topo;  // Ponteiro para o topo da torre
    while (discoAtual != nullptr) {
        RectangleShape discoShape(Vector2f(discoAtual->tamanho * 50, 50)); // Largura proporcional ao tamanho
        discoShape.setTexture(&discoTexture);
        discoShape.setPosition(xPos - discoShape.getSize().x / 2, yOffSet);
        window.draw(discoShape);
        yOffSet += 50;  // Desloca para baixo o próximo disco (de cima para baixo)
        discoAtual = discoAtual->próx;  // Passa para o próximo disco
    }
}


int main(){

    RenderWindow window(VideoMode(1280,800), "Torre de Hanoi", sf::Style::Resize | sf::Style::Close);
  
    torre torre1, torre2, torre3;
    criarTorre(&torre1);
    criarTorre(&torre2);
    criarTorre(&torre3);

    ptr_disco d1 = new disco{1, nullptr};
    ptr_disco d2 = new disco{2, nullptr};
    ptr_disco d3 = new disco{3, nullptr};
    ptr_disco d4 = new disco{ 4, nullptr };
    ptr_disco d5 = new disco{ 5, nullptr };

    empilhar(&torre1, d5);
    empilhar(&torre1, d4);
    empilhar(&torre1, d3);
    empilhar(&torre1, d2);

    empilhar(&torre1, d1);

    //Separando a janela em três seções, cada seção terá o mesmo tamanho e uma torre
    float larguraSecao = window.getSize().x / 3.0f;

    //Definindo a posição da torre no eixo x
    float xTorre1 = larguraSecao / 2.0f;
    float xTorre2 = larguraSecao + larguraSecao / 2.0f;
    float xTorre3 = 2 * larguraSecao + larguraSecao / 2.0f;

    int alturaTorre = 300;
    int larguraTorre = 20;

    while (window.isOpen()){
        Event event;
        while (window.pollEvent(event)){
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear(sf::Color(135, 206, 235));

        desenharTorre(window, xTorre1, alturaTorre, larguraTorre, torre1.topo);
        desenharTorre(window, xTorre2, alturaTorre, larguraTorre, torre2.topo);
        desenharTorre(window, xTorre3, alturaTorre, larguraTorre, torre3.topo);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i posicaoMouse = sf::Mouse::getPosition(window);

            // Verificar se o clique foi na torre 1
            if (clicarNaTorre(posicaoMouse.x, posicaoMouse.y, 200, window.getSize().y - 400, 20, 400)) {
                ptr_disco discoSelect = nullptr;  // Aqui você define o ponteiro do disco a ser desempilhado
                if (desempilhar(&torre1, discoSelect)) {  // Passa o ponteiro como referência
                    std::cout << "Desempilhei o disco de tamanho " << discoSelect->tamanho << " da torre 1" << std::endl;
                }
                else {
                    std::cout << "A torre 1 está vazia!" << std::endl;
                }
            }
        }

        
        window.display();


    }

    delete d1;
    delete d2;
    delete d3;

    return 0;
}
