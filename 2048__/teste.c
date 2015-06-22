#include<stdio.h>
#include<SDL.h>
#include<SDL_image.h>
int main(int argc, char* argv[]){
  SDL_Init(SDL_INIT_VIDEO); // Inicializa o SDL e o sistema de vídeo
  SDL_Surface * screen; // A janela principal
  SDL_Surface * image; // A imagem

  screen = SDL_SetVideoMode(640, 480, 16, SDL_SWSURFACE); // Cria a janela
  image = SDL_LoadBMP("ball.bmp"); // Carrega a imagem no formato BMP

  // Verifica se carregou a imagem
  if (image == NULL)
  {
     printf("Não foi possivel abrir ball.bmp\n");
     return 1;
  }

  int done = 0; // Variável de controle do loop
  while (done == 0) // Enquanto não concluir
  {
    SDL_BlitSurface(image, NULL, screen, NULL); // Joga a imagem inteira na tela
    SDL_Delay(60);
}
  SDL_Quit(); // Fecha o SDL

  return 0;
}
