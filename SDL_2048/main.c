/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 632;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gBackGround = NULL;

struct Peca {
    int x;
    int y;
    int valor;
    SDL_Surface *img;
} tabuleiro[4][4];

bool init()
{
	//Initialization flag
	bool success = true;
	int i, j;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow( "2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			gScreenSurface = SDL_GetWindowSurface( gWindow );
		}
	}

    for (i=0; i<4; i++){
        for (j=0;j<4; j++){
            printf ("Inicializando o tabuleiro!\n");
            tabuleiro[i][j].valor = 0;
            tabuleiro[i][j].x = i*153 + i*10;
            tabuleiro[i][j].y = j*151 + j*10;
            printf("Peca %d %d com valor %d. \n", i, j, tabuleiro[i][j].valor);
        }
    }
	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;
	int i, j;

	//Load splash image
	gBackGround = SDL_LoadBMP( "../SDL_2048/Fundo.bmp" );
	if( gBackGround == NULL )
	{
		printf( "Unable to load image %s! SDL Error: %s\n", "Fundo", SDL_GetError() );
		success = false;
	}
	tabuleiro[3][3].valor = 2;

    for (i=0; i<4; i++){
        for (j=0; j<4; j++){
            switch (tabuleiro[i][j].valor){
                case 2:
                tabuleiro[i][j].img = SDL_LoadBMP("../SDL_2048/2.bmp");
                break;

                case 0:
                tabuleiro[i][j].img = SDL_LoadBMP("../SDL_2048/0.bmp");
                break;
            }
            if (tabuleiro[i][j].img == NULL && tabuleiro[i][j].valor != 0){
                printf("Não foi possível carregar a peça");
            }
        }
    }
	return success;
}

void atualizaTela(){
    int i, j;
    //Apply the image
    SDL_BlitSurface( gBackGround, NULL, gScreenSurface, NULL );

    SDL_Rect posicao;
    for (i=0; i<4; i++){
        for (j=0; j<4; j++){
            posicao.x = tabuleiro[i][j].x;
            posicao.y = tabuleiro[i][j].y;

            SDL_BlitSurface(tabuleiro[i][j].img, NULL, gScreenSurface, &posicao);
        }
    }

    SDL_UpdateWindowSurface( gWindow );
}


void close()
{
	//Deallocate surface
	SDL_FreeSurface( gBackGround );
	gBackGround = NULL;

    //TODO: free cada peça do tabuleiro

	//Destroy window
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
		    bool exit = false;
		    atualizaTela();

			while (!exit){
			    SDL_Event event;
			    while(SDL_PollEvent(&event))
                {
                   if (event.type == SDL_QUIT){
                     exit = true;
                     break;
                   } else if (event.type == SDL_KEYDOWN){
						switch( event.key.keysym.sym )
						{
						    //esquerda
							case SDLK_a:
                            tabuleiro[2][3].valor = 2;
							printf("Apertou a! \n");
							break;

                            //direita
							case SDLK_d:
                            tabuleiro[2][3].valor = 4;
							printf("Apertou d! \n");
							break;

                            //baixo
							case SDLK_s:
							tabuleiro[2][2].valor =4;
							printf("Apertou s! \n");
							break;

                            //cima
							case SDLK_w:
                            tabuleiro[2][2].valor = 2;
                            printf("Apertou w! \n");
							break;
						}
                   }
                 }

                 if( loadMedia() ){
                    atualizaTela();
                 }


			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
