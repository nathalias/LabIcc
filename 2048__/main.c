#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<windows.h>
#include<SDL.h>
#include<SDL_image.h>
#include"jogo.h"
/*
    Autores:
        Samuel de Oliveira Gamito,9266452
        Nathalia Dias do Santos,
*/

const int SCREEN_WIDTH = 436;
const int SCREEN_HEIGHT = 436;

struct Peca {
        int  x;
        int  y;
        SDL_Surface *img;
}pecas[4][4];

/****************************
    i,y -> linha da matriz
    j,x -> coluns da matriz
****************************/
int SDL_Init(Uint32 flags);

int main(int argc, char **argv){
    Jogo tabuleiro;
    char* ranking[10];
    //Declarar variaveis aqui:
    int change = FALSE ,running = TRUE, game = FALSE, iniciaTab=FALSE, carregaTab=FALSE, win=FALSE, telaAtual = HOME;

    //Criar elementos do SDL aqui:
    SDL_Surface *homeBg;
    SDL_Surface *jogoBg;
    SDL_Surface *winBg;
    SDL_Surface *loseBg;
    SDL_Surface *screen;
    SDL_Surface *imagens[12];
    SDL_Point mousePos;
    SDL_Window *window;
    SDL_Renderer *renderer;
    //Cria os retangulos das peças iniciais
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
    window = SDL_CreateWindow("2048 - Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    screen = SDL_GetWindowSurface(window);
    //Carregando Backgrounds
    homeBg = SDL_LoadBMP("home.bmp"); // Carrega o background da home (1)
    jogoBg = SDL_LoadBMP("jogo.bmp"); // Carrega o background do jogo (2)
    winBg = SDL_LoadBMP("win.bmp"); // Carrega o background de quando vence (3)
    loseBg = SDL_LoadBMP("lose.bmp"); // Carrega o background de quando perde (4)
    trocaTela(homeBg,screen);


    //Gameloop
    while(running == TRUE)
    {
        //Detecção de Evento
        SDL_Event event;
        while(SDL_PollEvent(&event) && game ==0 && win == 0){//Não quero q entre nesse loop se o jogo estiver começado
            if(telaAtual != HOME){
                trocaTela(homeBg,screen);
            }
            switch(event.type)
            {
            case SDL_QUIT: //Caso o usuário peça para fechar o jogo
                running = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(                    // Define as variaveis com a posição
                    &mousePos.x,                //Coordenadas    mouse (x)
                    &mousePos.y                 //            do        (y)
                );
                if(event.button.button == SDL_BUTTON_LEFT){
                    if(SDL_EnclosePoints(&mousePos,1,&iniciar, NULL)){

                    trocaTela(jogoBg,screen);
                    telaAtual = JOGO;
                    game = !game;//Inicia o jogo

                    }else if(SDL_EnclosePoints(&mousePos,1,&score, NULL)){
                        SDL_Log("SCORE");
                    }else if(SDL_EnclosePoints(&mousePos,1,&retomar, NULL)){
                        SDL_Log("RETOMA");
                        carregaTab = 1;
                        game = !game;
                    }
                }
                break;
            }
        }
        SDL_UpdateWindowSurface(window);

        if(game == 1){//A patir daque o jogo sera executado
                SDL_Delay(10);//Delay para melhorar o processamento do jogo
            if(iniciaTab == FALSE){//Verifica se ele ja foi inicializado
                if(criaTabuleiro(&tabuleiro, carregaTab) == -1){//Cria o tabuleiro
                        printf("erro ao criar tabuleiro");
                        return 0;
                }
                if (carregaTab == 1){
                    recuperaJogo(&tabuleiro);
                }else{
                    colocaPeca(&tabuleiro);//Coloca a primeira peça
                }
                criaPecas(imagens);//Crias as peças
                imprimeTabuleiro(&tabuleiro);//Imprime o tabuleiro
                iniciaTab = TRUE;//Finaliza a inicialização
                if (carregaImagens(&tabuleiro, imagens)){
                    atualizaTela(screen, window);
                } else {
                    printf("Erro no carregamento de imagens");
                }
            }else if(iniciaTab == ZERADO){
                change = FALSE;
                criaPecas(imagens);//Crias as peças
                imprimeTabuleiro(&tabuleiro);//Imprime o tabuleiro
                iniciaTab = TRUE;//Finaliza a inicialização
                if (carregaTab == 1){
                    recuperaJogo(&tabuleiro);
                }else{
                    colocaPeca(&tabuleiro);//Coloca a primeira peça
                }
                if (carregaImagens(&tabuleiro, imagens)){
                    atualizaTela(screen, window);
                } else {
                    printf("Erro no carregamento de imagens");
                }
            }

            while( SDL_PollEvent( &event ) != 0 )
            {
					//User requests quit
					if( event.type == SDL_QUIT )
					{
					    salvaJogo(&tabuleiro);
					    running = 0;
					}else if( event.type == SDL_KEYDOWN ){
						//Select surfaces based on key press
						switch( event.key.keysym.sym )
						{
							case SDLK_UP:
                                change = mudaPosicao(&tabuleiro, CIMA,screen,imagens,window);
                                SDL_Log("%d", change);
							break;

							case SDLK_DOWN:
                                change = mudaPosicao(&tabuleiro, BAIXO,screen,imagens,window);
                                SDL_Log("%d", change);
							break;

							case SDLK_LEFT:
                                change = mudaPosicao(&tabuleiro, ESQUERDA,screen,imagens,window);
                                SDL_Log("%d", change);
							break;

							case SDLK_RIGHT:
                                change = mudaPosicao(&tabuleiro, DIREITA,screen,imagens,window);
                                SDL_Log("%d", change);
							break;
						}
					}

            }
            if( change == FALSE && tabuleiro.movimentos > 0){
                SDL_Delay(600);
                win = TRUE;
                game = FALSE;
                trocaTela(winBg, screen);
                telaAtual = WIN;
                salvaScore(&tabuleiro);
                printf("Fim do jogo\n Movimento: %d", tabuleiro.movimentos);


            }else if(change == -3){
                printf("\n\n\tdeu ruim");
                trocaTela(loseBg, screen);
                game = FALSE;
                win=FALSE;
                telaAtual = LOSE;
                zeraTab(&tabuleiro);
                iniciaTab = ZERADO;//indica q no proximo jogo não precisa inicializar o tabuleiro mas precisa colocar as peças
                printf("não há mais movimento");

            }
        }

    }
    //Fechando
    SDL_Quit();

    return 0;

}
void salvaScore(Jogo* tabuleiro){
    FILE* arquivo;
    char nomeAtual[20];
    char* aux[100];

    arquivo = fopen("ranking.txt", "a");
    if (arquivo == NULL){
        printf("\nNão foi possível abrir o arquivo\n");
        exit(0);
    } else {
        printf("\nVocê Venceu!! Digite o seu nome(max 20 caract.):\n");
        scanf("%s", &nomeAtual);
    }
    //chamar a função que calcula a pontuação e passar aqui no lugar de 'movimentos'
    fprintf(arquivo,"%s...%d\n",nomeAtual,tabuleiro->movimentos);
    fclose(arquivo);
}

/**************************************************************
    Função para recuperar o jogo salvo no arquivo
        Entrada:Tabuleiro
**************************************************************/
void recuperaJogo(Jogo* tabuleiro){
    FILE* arquivo;
    int i, j;

    arquivo = fopen("jogoSalvo.txt","r");
    if (arquivo == NULL){
        printf("\nErro na leitura do Arquivo\n");
        exit(0);
    } else {
        printf("\nLendo arquivo...\n");
        for(i = 0; i < 4; i++){
          for(j = 0; j < 4; j++){
            if( !fscanf(arquivo,"%d",&tabuleiro->matriz[i][j])){
              printf("Erro a o ler a entrada (%d,%d) da matriz\n",i,j);
              break;
            } else {
                //Controle no console do que foi lido
                printf("[%d,%d] %d \n",i,j, tabuleiro->matriz[i][j]);
            }
          }
        }
        fscanf(arquivo,"%d",&tabuleiro->movimentos);//Recupera a ultima linha do arquivo
                                                    //com a qtde dos movimentos salvos
        printf("\nMovimentos: %d\n",tabuleiro->movimentos);

    }
    fclose(arquivo);
}

/*********************************************************
    Função para salvar o jogo qnd o programa for fechado
     Entrada: Tabuleiro
*********************************************************/
void salvaJogo(Jogo* tabuleiro){

    FILE *arquivo;
    int i=0,j=0;

    arquivo = fopen("jogoSalvo.txt","w");
    if (arquivo == NULL){
        printf("\nErro na abertura do Arquivo\n");
        exit(0);
    } else {
        printf("\nEscrevendo no Arquivo...");
        for (i=0; i<4; i++){
            for(j=0;j<4;j++){
                fprintf(arquivo, "%d\n", tabuleiro->matriz[i][j]);
            }
        }
    }
    fprintf(arquivo, "%d\n", tabuleiro->movimentos); //ultima linha do arquivo fica com
                                                     //os movimentos para cáculo de pontuação
    printf("\nMovimentos: %d\n", tabuleiro->movimentos);

    fclose(arquivo);
}
/*************************************
    -Função para zerar o tabuleiro e
    criar um novo tabuleiro
*************************************/
void zeraTab(Jogo* tabuleiro){
    int i,j;
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            tabuleiro->matriz[i][j] = 0;
        }
    }
    tabuleiro->movimentos = 0;

}
/*************************************
    -Função para carregar e colocar
    telas
*************************************/
void trocaTela(SDL_Surface* tela, SDL_Surface* screen){
    SDL_BlitSurface(tela, NULL, screen, NULL); // Coloca na tela

}
/*************************************
    -Função para criar o tabuleiro
**************************************/
int criaTabuleiro(Jogo* tabuleiro, int carregaTab){
    int i;
    //Define o tamanho do tabuleiro
    tabuleiro->tamanho = 4;
    //Zera os movimento
    tabuleiro->movimentos =0;
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
    tabuleiro->matriz[0][0] = tabuleiro->matriz[0][1] = 1024;
    return 0;
}
/************************************************************
    -Função que inicializa a matriz de Pecas, que vai controlar
    as imagens da tela. Ao final da execução coloca as coorde-
    nadas de cada imagens na janela, de acordo com cálculos
    que relacionam o tamanho das peças e da janela.
**************************************************************/
void criaPecas(SDL_Surface* imagens[12]) {
    int i, j;
    for (i=0; i<4; i++){
        for (j=0;j<4; j++){
            pecas[j][i].x = i*99 + i*14;
            pecas[j][i].y = j*99 + j*14;
        }
    }
    imagens[0] = SDL_LoadBMP("../2048__/0.bmp");
    imagens[1] = SDL_LoadBMP("../2048__/1.bmp");
    imagens[2] = SDL_LoadBMP("../2048__/2.bmp");
    imagens[3] = SDL_LoadBMP("../2048__/3.bmp");
    imagens[4] = SDL_LoadBMP("../2048__/4.bmp");
    imagens[5] = SDL_LoadBMP("../2048__/5.bmp");
    imagens[6] = SDL_LoadBMP("../2048__/6.bmp");
    imagens[7] = SDL_LoadBMP("../2048__/7.bmp");
    imagens[8] = SDL_LoadBMP("../2048__/8.bmp");
    imagens[9] = SDL_LoadBMP("../2048__/9.bmp");
    imagens[10] = SDL_LoadBMP("../2048__/10.bmp");
    imagens[11] = SDL_LoadBMP("../2048__/11.bmp");

}
/***************************************************
    -Função para imprimir o tabuleiro
    Entrada:Tabuleiro
***************************************************/

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

/***************************************************
    -Função para colocar as imagens de acordo com
     o valor da matriz principal
    Entrada:Tabuleiro, as posiçoes das peças
    Saída: true, se a função conseguir carregar as imagens

           false, se alguma imagens não foi carregada
***************************************************/
bool carregaImagens(Jogo* tabuleiro, SDL_Surface* imagens[12]){
    int i,j;
    bool success = true;

    for (i=0; i<4; i++){
        for (j=0; j<4; j++){
            switch (tabuleiro->matriz[i][j]){
                case 0:
                    pecas[i][j].img = imagens[0];
                break;

                case 2:
                    pecas[i][j].img = imagens[1];
                break;

                case 4:
                    pecas[i][j].img = imagens[2];
                break;

                case 8:
                    pecas[i][j].img = imagens[3];
                break;

                case 16:
                    pecas[i][j].img = imagens[4];
                break;

                case 32:
                    pecas[i][j].img = imagens[5];
                break;

                case 64:
                    pecas[i][j].img = imagens[6];
                break;

                case 128:
                    pecas[i][j].img = imagens[7];
                break;

                case 256:
                    pecas[i][j].img =imagens[8];
                break;

                case 512:
                    pecas[i][j].img = imagens[9];
                break;

                case 1024:
                    pecas[i][j].img = imagens[10];
                break;

                case 2048:
                    pecas[i][j].img = imagens[11];
                break;
            }

            if (pecas[i][j].img == NULL && tabuleiro->matriz[i][j] != 0){
                success = false;
                printf("A matriz está com valor %d\n",tabuleiro->matriz[i][j]);
                printf("Não foi possível carregar a peca. Erro %s: \n",  SDL_GetError());
            }
        }
    }
    return success;
}


/***************************************************
    -Função para atualizar as imagens da tela de
    acordo com as mudanças do tabuleiro
    Entrada: Tabuleiro
*****************************************************/
void atualizaTela(SDL_Surface *screen, SDL_Window *window){
    int i, j;

    SDL_Surface* jogoBg = SDL_LoadBMP("jogo.bmp"); // Carrega o background do jogo
    SDL_BlitSurface(jogoBg, NULL, screen, NULL); // Coloca na tela

    SDL_FreeSurface(jogoBg);

    SDL_Rect posicao;
    for (i=0; i<4; i++){
        for (j=0; j<4; j++){
            posicao.x = pecas[i][j].x;
            posicao.y = pecas[i][j].y;

            SDL_BlitSurface(pecas[i][j].img, NULL, screen, &posicao);

        }
    }
    SDL_UpdateWindowSurface(window);
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
int  mudaPosicao(Jogo* tabuleiro, int lado,SDL_Surface* screen, SDL_Surface* imagens[12], SDL_Window* window ){
    int i,j,k, atual, stop,  mudado = 0,x;
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

    giraMatrizHor(tabuleiro, lado);//Chama a função que gira o tabuleiro

    if(mudado != 0){
        tabuleiro->movimentos++;//Soma movimento
        colocaPeca(tabuleiro);
        imprimeTabuleiro(tabuleiro);
        if (carregaImagens(tabuleiro, imagens)){//Atualiza as imagens da tela
            atualizaTela(screen, window);
        } else {
            printf("Erro no carregamento de imagens");
        }

        if(veMaior(tabuleiro) == -1){
            x = verificaMovimento(tabuleiro);
           return x;
        }else{
            return 0;
        }
    }else{
        x = verificaMovimento(tabuleiro);
        printf("topx:%d\n",x);
        return x;
    }
    return -3;
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

    int i, j;
    for(i=0; i<tabuleiro->tamanho; i++){
        for(j=0; j<tabuleiro->tamanho; j++){
            if(tabuleiro->matriz[i][j] == 2048){//Verifica se o valor maximo foi alcançado;
                return 0;

            }
        }
    }
    return -1;
}


/*****************************************************
    -Função para verficar se ainda existem movimento
    Entrada:Tabulerio
    Saida:
        retorna -1 se encontrar algum 0
        retorna -2 quando tiver movimento
        retorna -3 quando não tiver movimento
*****************************************************/
int verificaMovimento(Jogo* tabuleiro){
    int i, j , m;
    for(i=0; i<tabuleiro->tamanho; i++){//Verifica se ainda possui zeros
        for(j=0; j<tabuleiro->tamanho; j++){
            if(tabuleiro->matriz[i][j] == 0){
                return -1;
            }
        }
    }
    for(i=0;i<tabuleiro->tamanho; i++){//Verifica se ainda possui movimentos
        for(j=0;j<tabuleiro->tamanho; j++){
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
