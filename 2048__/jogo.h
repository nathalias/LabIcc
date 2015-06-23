#ifndef JOGO_H_INCLUDED
#define JOGO_H_INCLUDED

#define ESQUERDA 1
#define DIREITA 3
#define CIMA 2
#define BAIXO 4

typedef struct{
    int tamanho, **matriz, movimentos;
}Jogo;

typedef struct{
     SDL_Rect bbox;
     int valor;
}Pecas;
int criaTabuleiro(Jogo* tabuleiro, Pecas* posiPecas);

void imprimeTabuleiro(Jogo* tabuleiro);

int  mudaPosicao(Jogo* tabuleiro, int lado);


void giraMatrizAnti(Jogo* tabuleiro, int ang);

void giraMatrizHor(Jogo* tabuleiro, int ang);

int colocaPeca(Jogo* tabuleiro);

int geraNum(void);


int veMaior(Jogo* tabuleiro);
int verificaMovimento(Jogo* tabuleiro);



#endif // JOGO_H_INCLUDED
