#ifndef JOGO_H_INCLUDED
#define JOGO_H_INCLUDED

#define HOME 1
#define JOGO 2
#define WIN 3
#define LOSE 4

#define ESQUERDA 1
#define DIREITA 3
#define CIMA 2
#define BAIXO 4

#define ZERADO 2
#define TRUE 1
#define FALSE 0
typedef struct{
    int tamanho, **matriz, movimentos, score;
}Jogo;

int criaTabuleiro(Jogo* tabuleiro, int carregaTab);

void imprimeTabuleiro(Jogo* tabuleiro);

int  mudaPosicao(Jogo* tabuleiro, int lado,SDL_Surface* screen, SDL_Surface* imagens[12], SDL_Window* window );

void giraMatrizAnti(Jogo* tabuleiro, int ang);

void giraMatrizHor(Jogo* tabuleiro, int ang);

int colocaPeca(Jogo* tabuleiro);

int geraNum(void);

int veMaior(Jogo* tabuleiro);
int verificaMovimento(Jogo* tabuleiro);

bool carregaImagens(Jogo* tabuleiro,SDL_Surface* imagens[12]);

void atualizaTela(SDL_Surface *screen, SDL_Window *window);

void salvaJogo(Jogo* tabuleiro);

void recuperaJogo(Jogo* tabuleiro);

void criaPecas(SDL_Surface* imagens[12]);

void trocaTela(SDL_Surface* tela, SDL_Surface* screen);

void zeraTab(Jogo* tabuleiro);

void salvaScore(Jogo* tabuleiro);

#endif // JOGO_H_INCLUDED
