#ifndef JOGO_H_INCLUDED
#define JOGO_H_INCLUDED

#define ESQUERDA 1
#define DIREITA 3
#define CIMA 2
#define BAIXO 4
#define TBOX 1000
typedef struct{
    int tamanho, **matriz, movimentos;
}Jogo;

int criaTabuleiro(Jogo* tabuleiro);

void imprimeTabuleiro(Jogo* tabuleiro);

int  mudaPosicao(Jogo* tabuleiro, int lado );


void giraMatrizAnti(Jogo* tabuleiro, int ang);

void giraMatrizHor(Jogo* tabuleiro, int ang);

int colocaPeca(Jogo* tabuleiro);

int geraNum(void);

int veMaior(Jogo* tabuleiro);
int verificaMovimento(Jogo* tabuleiro);

bool carregaImagens(Jogo* tabuleiro);
void atualizaTela(SDL_Surface *screen, SDL_Window *window);
void criaPecas();
void salvaJogo(Jogo* tabuleiro);
#endif // JOGO_H_INCLUDED
