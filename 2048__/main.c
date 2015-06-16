#include<stdio.h>
#include<stdlib.h>
typedef struct{
    int tamanho, **matriz;
}Tabuleiro;

int main(){
    Tabuleiro jogo;
    if(criaTabuleiro(&jogo) == -1){
        printf("erro ao criar tabuleiro");
        return 0;
    }


}
int criaTabuleiro(Tabuleiro* jogo){
    int i;
    //Define o tamanho do tabuleiro
    jogo->tamanho = 4;

    //Cria as colunas do tabuleiro
    jogo->matriz = (int**) malloc(jogo->tamanho * sizeof(int*));

    if(jogo->matriz == NULL){
        return -1;
    }

    for(i=0; i<jogo->tamanho; i++){
        jogo->matriz[i] = (int*) calloc(jogo->tamanho, sizeof(int*));
        if(jogo->matriz[i] == NULL){
            return -1;
        }
    }
    return 0;
}
