#include<stdio.h>
#include<stdlib.h>
typedef struct{
    int tamanho, **matriz;
}Jogo;
typedef struct{
    char linkPeca[100];
    int valorPeca;
}Peca;

int main(){
    Jogo tabuleiro;
    int lado = 3;
    if(criaTabuleiro(&tabuleiro) == -1){
        printf("erro ao criar tabuleiro");
        return 0;
    }
    tabuleiro.matriz[2][0] = 2;
    tabuleiro.matriz[2][2] = 2;
    tabuleiro.matriz[1][1] = 2;

    imprimeTabuleiro(&tabuleiro);
    mudaPosicao(&tabuleiro, lado);
    imprimeTabuleiro(&tabuleiro);

}
int criaTabuleiro(Jogo* tabuleiro){
    int i;
    //Define o tamanho do tabuleiro
    tabuleiro->tamanho = 4;

    //Cria as colunas do tabuleiro
    tabuleiro->matriz = (int**) malloc(tabuleiro->tamanho * sizeof(int*));

    if(tabuleiro->matriz == NULL){
        return -1;
    }

    for(i=0; i<tabuleiro->tamanho; i++){
            //Cria linhas e preenche com 0
        tabuleiro->matriz[i] = (int*) calloc(tabuleiro->tamanho, sizeof(int*));
        if(tabuleiro->matriz[i] == NULL){
            return -1;
        }
    }
    return 0;
}

void imprimeTabuleiro(Jogo* tabuleiro){
    int i,j;
    for(i=0; i<tabuleiro->tamanho; i++){
        for(j=0; j<tabuleiro->tamanho; j++){
            printf(" [%d] ",tabuleiro->matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n\n");
}

void  mudaPosicao(Jogo* tabuleiro, int lado){
    int i,j,k, atual;
    for(i=0; i<tabuleiro->tamanho; i++){
        for(j=tabuleiro->tamanho-1; j>=0; j--){
            if(tabuleiro->matriz[i][j] != 0 && j<3){
                atual = j;
                for(k=j; k<tabuleiro->tamanho; k++){
                    if(atual<3){
                        if(tabuleiro->matriz[i][atual+1] == 0){
                            tabuleiro->matriz[i][atual+1] = tabuleiro->matriz[i][atual];
                            tabuleiro->matriz[i][atual]=0;
                            atual ++;
                        }else if(tabuleiro->matriz[i][atual+1] == tabuleiro->matriz[i][atual]){
                                tabuleiro->matriz[i][atual+1] *=2;
                                tabuleiro->matriz[i][atual] = 0;
                                atual ++;

                        }else{

                        }
                    }
                }
            }

        }
    }
}
