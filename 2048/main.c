#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void imprimeMatriz(int l, int c, int** matriz[4][4]){
    int i, j;

    for (i=0; i<l; i++){
        for (j=0;j<c;j++){
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int geraPosicao(){
    int p = rand() % 4;
    printf("\nPosicao gerada: %d \n", p);
    return p;
}

int** novoNumero(int** matriz[4][4]){
    int x, y;
    x = geraPosicao();
    y = geraPosicao();

    if (matriz[x][y] == 0) {
        matriz[x][y] = 2;
        return &matriz;
    } else {
        return novoNumero(matriz);
    }
}
int verificaCasa (int coluna[4],int x, int stop) {
	int t;
	if (x == 0) {
		return x;
	}
	for(t= x-1; t>=0; t--) {
		if (coluna[t]!=0) {
			if (coluna[t]!= coluna[x]) {
				return t+1;
			}
			return t;
		} else {
			if (t == stop) {
				return t;
			}
		}
	}
	return x;
}

int movimento(int** matriz [4]){
	int i, t , stop = 0;

	for (i=0; i<4; i++) {
		if (matriz[i]!=0) {
			t = verificaCasa(matriz,i,stop);
			if (t!=i) {
				if (matriz[t]==0) {
					matriz[t]=matriz[i];
				} else
				  if (matriz[t]==matriz[i]) {
					matriz[t]++;
					stop = t+1;
				}
				matriz[i]=0;
			}
		}
	}
	return &matriz;
}

void paraCima (int* matriz[4]) {
    int i = 0;

    for (i=0; i<4; i++){
        movimento(&matriz[i]);
    }
}

void rotateMatriz(int** matriz[4][4]) {
	int i, j, n = 4;
	int tmp;
	for (i=0; i<n/2; i++) {
		for (j=i; j<n-i-1; j++) {
			tmp = matriz[i][j];
			matriz[i][j] = matriz[j][n-i-1];
			matriz[j][n-i-1] = matriz[n-i-1][n-j-1];
			matriz[n-i-1][n-j-1] = matriz[n-j-1][i];
			matriz[n-j-1][i] = tmp;
		}
	}
}

int main()
{
      int i,j;
      int* matriz[4][4];
      int x, y;

      for (i=0; i<4; i++){
          for (j=0;j<4;j++){
            matriz[i][j] = 0;
          }
      }

      for (i=0; i<4; i++){
          for (j=0;j<4;j++){
            printf("%d ", matriz[i][j]);
          }
          printf("\n");
      }

      printf("\nInicio: \n");
      imprimeMatriz(4,4,&matriz);

      printf("\nPrimeiras 2 posicoes geradas:\n \n");

      novoNumero(&matriz);
      novoNumero(&matriz);
      imprimeMatriz(4,4,&matriz);



      paraCima(&matriz);



      novoNumero(&matriz);
      printf("\nmovimento\n");

      imprimeMatriz(4,4,&matriz);

      //rotateMatriz(&matriz);

      return 0;
}
