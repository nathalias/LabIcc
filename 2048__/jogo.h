#ifndef JOGO_H_INCLUDED
#define JOGO_H_INCLUDED
typedef struct{
    int tamanho, **matriz, movimentos;
}Jogo;
typedef struct{
    char linkPeca[100];
    int valorPeca;
}Peca;

int criaTabuleiro(Jogo* tabuleiro);

void imprimeTabuleiro(Jogo* tabuleiro);

int  mudaPosicao(Jogo* tabuleiro, int lado);


void giraMatrizAnti(Jogo* tabuleiro, int ang);

void giraMatrizHor(Jogo* tabuleiro, int ang);

int colocaPeca(Jogo* tabuleiro);

int geraNum(void);


int veMaior(Jogo* tabuleiro);
int verificaMovimento(Jogo* tabuleiro);



#endif // JOGO_H_INCLUDED
