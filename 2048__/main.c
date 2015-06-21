#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#define MAX tabuleiro->tamanho -1
/*
    Autores:
        Samuel de Oliveira Gamito,9266452
        Nathalia Dias do Santos,
*/

/****************************
    i,y -> linha da matriz
    j,x -> coluns da matriz
****************************/
typedef struct{
    int tamanho, **matriz, movimentos;
}Jogo;
typedef struct{
    char linkPeca[100];
    int valorPeca;
}Peca;

int main(){
    Jogo tabuleiro;
    int lado, change, inicioH,fimH,time;
    inicioH = GetTickCount();
    if(criaTabuleiro(&tabuleiro) == -1){
        printf("erro ao criar tabuleiro");
        return 0;
    }
    tabuleiro.matriz[0][0] = 1024;
    tabuleiro.matriz[0][1] = 1024;

    colocaPeca(&tabuleiro);
    imprimeTabuleiro(&tabuleiro);

    while(1){

        scanf("%d", &lado);
        change = mudaPosicao(&tabuleiro, lado);
        if( change == 0){
            fimH = GetTickCount();
            time = (fimH-inicioH)/1000;
            printf("Fim do jogo\n Tempo:  %d\n Movimento: %d",time, tabuleiro.movimentos);
            break;
        }else if(change == -3){
            printf("não há mais movimento");
            break;
        }


    }
    return 0;

}


/*************************************
    -Função para criar o tabuleiro
**************************************/
int criaTabuleiro(Jogo* tabuleiro){
    tabuleiro->movimentos = 0;
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
    system("cls");
    for(i=0; i<tabuleiro->tamanho; i++){
        for(j=0; j<tabuleiro->tamanho; j++){
            printf(" [%d] ",tabuleiro->matriz[i][j]);
        }
    printf("\n");
    }
}




/********************************************************
    -Função para mudar a posição dos valores da matriz
    Entrada:Tabuleiro e direção do movimento
    Saida:
        retorna 0 quando o jogo acaba
        retorna -1 para o jogo continuar
        retorna -2 quando o tabulerio esta cheio e tem
            pelo menos um movimento
        retorn -3 quando não tiver mais movimento
*********************************************************/
int  mudaPosicao(Jogo* tabuleiro, int lado){
    int i,j,k, atual, stop, fim, mudado = 0;
    /*
        <- 0
        ^  1
        -> 2
        V  3
    */
    //Chama a função que gira o tabuleiro
    giraMatrizAnti(tabuleiro, lado);
    if(lado >4){
        return;
    }

    for(i=0; i<tabuleiro->tamanho; i++){
        for(j=0; j<tabuleiro->tamanho ;j++){
            if(tabuleiro->matriz[i][j] != 0 && j>0){
                atual = j;
                stop = -1;
                for(k=j;k>0&& stop != 0; k--){
                    if(atual>0){
                        if(tabuleiro->matriz[i][atual-1] == 0){
                            tabuleiro->matriz[i][atual-1] = tabuleiro->matriz[i][atual];
                            tabuleiro->matriz[i][atual]=0;
                            atual--;
                            mudado++;
                        }else if(tabuleiro->matriz[i][atual-1] == tabuleiro->matriz[i][atual]){
                            tabuleiro->matriz[i][atual-1] *=2;
                            tabuleiro->matriz[i][atual] = 0;
                            atual--;
                            mudado++;

                        }else{
                            stop = 0;
                        }
                    }
                }
            }

        }
    }

    giraMatrizHor(tabuleiro);//Chama a função que gira o tabuleiro e em seguida imprime
    fim = veMaior(tabuleiro);
    if(mudado != 0){
        tabuleiro->movimentos++;
        if(fim == -1){
            fim = colocaPeca(tabuleiro);
        }
    }
    imprimeTabuleiro(tabuleiro);
    return fim;
}


/***********************************************
    -Funções para Girar a matriz
    Entrada:recebe o tabulero e qnts giros tem que dar
    +As funções abaixo giram o tabuleiro
        A primeira gira de modo q o movimento
        desejado fique da direita para esquerda
        sempre

        Ja a segunda volta o tabuleiro para a
        posição inicial
************************************************/

void giraMatrizAnti(Jogo* tabuleiro, int ang){
    int i,j,k, suporte[tabuleiro->tamanho][tabuleiro->tamanho];
    for(k=ang; k>1; k--){
        for(i=0; i<tabuleiro->tamanho; i++){
            for(j=0; j<tabuleiro->tamanho; j++){
                suporte[j][i] = tabuleiro->matriz[i][3-j];
            }
        }
        for(i=0; i<tabuleiro->tamanho; i++){
            for(j=0; j<tabuleiro->tamanho; j++){
                tabuleiro->matriz[i][j] = suporte[i][j];
            }
        }
    }

}
void giraMatrizHor(Jogo* tabuleiro, int ang){
     int i,j,k, suporte[tabuleiro->tamanho][tabuleiro->tamanho], fim=-1;

    for(k=ang; k>1; k--){
        for(i=0; i<tabuleiro->tamanho; i++){
            for(j=0; j<tabuleiro->tamanho; j++){
                suporte[j][3-i] = tabuleiro->matriz[i][j];
            }
        }
        for(i=0; i<tabuleiro->tamanho; i++){
            for(j=0; j<tabuleiro->tamanho; j++){
                tabuleiro->matriz[i][j] = suporte[i][j];
            }
        }
    }

}
/********************************************
    -Função para criar peças aletoriamente
    Entrda:Tabuleiro
    Saida:
        retorna -1 qnd a peça for adicionada
        retorna -2 qnd o ultimo espaço for
            preenchido e tiver pelo menos
            um movimento
        retorn -3 qnd o ultimo espaço for
            preenchido e não tiver mais nem
            um movimento
*********************************************/
int colocaPeca(Jogo* tabuleiro){
       int A, i, X,Y;
       A = tabuleiro->tamanho*tabuleiro->tamanho;
       for(i=1; i<=A; i++){
            X = geraNum();
            Y = geraNum();
            if(tabuleiro->matriz[Y][X] == 0){
                tabuleiro->matriz[Y][X] = 2;
                break;
            }
       }

       if(i==17){
           return verificaMovimento(tabuleiro);
       }
        return -1;
}


/************************************************
    -Função para gerar numeros aleatórios
    Saida:
        retorna um numero entre 0 e 3(0<=X<=3)
*************************************************/
int geraNum(){
    int a;
    a= rand()%10;
    if(a<4){
        return a;

    }else{
        return geraNum();
    }
}


/********************************************
    -Função para verificar a maior peça
    Entrada:tabulerio
    Saida:
        retorn 0 se a maior for 2048
        retorn -1 se tds foram menor q 2048
*********************************************/
int veMaior(Jogo* tabuleiro){
    int i, j, fim=-1;
    for(i=0; i<tabuleiro->tamanho; i++){
        for(j=0; j<tabuleiro->tamanho; j++){
            if(tabuleiro->matriz[i][j] == 2048){//Verifica se o valor maximo foi alcançado;
                fim=0;
            }
        }
    }
    return fim;
}


/*****************************************************
    -Função para verficar se ainda existem movimento
    Entrada:Tabulerio
    Saida:
        retorna -2 quando tiver movimento
        retorna -3 quando não tiver movimento
*****************************************************/
int verificaMovimento(Jogo* tabuleiro){
    int i, j;
    for(i=0;i<4; i++){
        for(j=0;j<4; j++){
            if(i!=3){
                if( j!= 3){
                    if(tabuleiro->matriz[i][j] == tabuleiro->matriz[i][j+1] || tabuleiro->matriz[i][j] == tabuleiro->matriz[i+1][j]){
                        return -2;
                    }
                }else{
                    if(tabuleiro->matriz[i][j] == tabuleiro->matriz[i+1][j]){
                        return -2;
                    }
                }
            }else{
                if(j != 3){
                    if(tabuleiro->matriz[i][j] == tabuleiro->matriz[i][j+1]){
                        return -2;
                    }
                }
            }
        }
    }
    return -3;

}
