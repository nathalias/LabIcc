#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<SDL.h>
#include<SDL_image.h>
#include"jogo.h"
/*
    Autores:
        Samuel de Oliveira Gamito,9266452
        Nathalia Dias do Santos,
*/

/****************************
    i,y -> linha da matriz
    j,x -> coluns da matriz
****************************/


int main(int argc, char **argv){
    Jogo tabuleiro;
    int lado, change, inicioH,fimH,time, running = 1;
    SDL_Surface *homeBg;
    SDL_Surface *screen;
    SDL_Point mousePos;
    SDL_Rect iniciar;
        iniciar.x =50;
        iniciar.y =110;
        iniciar.h =111;
        iniciar.w =110;
    SDL_Rect score;
        score.x =277;
        score.y =129;
        score.h =111;
        score.w =110;
    SDL_Rect retomar;
        retomar.x =135;
        retomar.y =274;
        retomar.h =111;
        retomar.w =110;
    //Iniciando modo de video.
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDL_Log("Can't init %s", SDL_GetError());
        return 1;
    }
    //Criação da janela
    SDL_Window *window = SDL_CreateWindow("2048 - Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 434.30, 428.15, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    screen = SDL_GetWindowSurface(window);

    homeBg = SDL_LoadBMP("home.bmp"); // Carrega o background da home
    SDL_BlitSurface(homeBg, NULL, screen, NULL); // Coloca na tela
    SDL_FreeSurface(homeBg);

    //Gameloop
    while(running == 1)
    {
        //Detecção de Evento
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT: //Caso o usuário peça para fechar o jogo
                running = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(                    //    Sets mouse_position to...
                    &mousePos.x,                // ...mouse arrow coords on window
                    &mousePos.y
                );
                if(event.button.button == SDL_BUTTON_LEFT){
                    if(SDL_EnclosePoints(&mousePos,1,&iniciar, NULL)){
                        inicioH = GetTickCount();
                        if(criaTabuleiro(&tabuleiro) == -1){
                            printf("erro ao criar tabuleiro");
                            return 0;
                        }
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
                    }else if(SDL_EnclosePoints(&mousePos,1,&score, NULL)){
                        SDL_Log("SCORE");
                    }else if(SDL_EnclosePoints(&mousePos,1,&retomar, NULL)){
                        SDL_Log("RETOMA");
                    }
                }
                break;
            }
        }
        SDL_UpdateWindowSurface(window);
        SDL_Delay(10); //Isso causa algo como 60 quadros por segundo.
    }

    //Fechando
    SDL_Quit();

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
        retorna -3 quando não tiver mais movimento
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
        return 33;//Apenas para sair da função, nada acontece
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

    giraMatrizHor(tabuleiro, lado);//Chama a função que gira o tabuleiro e em seguida imprime
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
     int i,j,k, suporte[tabuleiro->tamanho][tabuleiro->tamanho];

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
int geraNum(void){
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




////Carregando imagem

void DrawImage( SDL_Surface *surface, char *image_path, int x_pos, int y_pos )
{
   SDL_Surface *image = IMG_Load ( image_path );
   if ( !image )
   {
      SDL_Log ( "IMG_Load: %s\n", IMG_GetError () );
   }

   // Draws the image on the screen:
   SDL_Rect rcDest = { x_pos, y_pos, 0, 0 };
   SDL_BlitSurface ( image, NULL, surface, &rcDest );

   // something like SDL_UpdateRect(surface, x_pos, y_pos, image->w, image->h); is missing here

   SDL_FreeSurface ( image );
}
