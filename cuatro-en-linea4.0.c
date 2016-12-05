#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#define FILAS 8
#define COLUMNAS 8
void imprimir(int pes[28][118]);
char tablero[FILAS][COLUMNAS];
void inicializar_tablero() {
  int i,j;

  for(i=0;i<FILAS;i++)
    for(j=0;j<COLUMNAS;j++)
      tablero[i][j]=' ';
}
int jugada_correcta(int fila, int col) {
  int jugada_correcta; //Guarda un 1 ó un 0 para indicar si la jugada es correcta o no. 1-Jugada correcta. 0-Jugada errónea: La fila y/o columna no son válidas. Se sale del tablero la jugada.
  jugada_correcta=1;
  if (fila>=FILAS || fila<0 || col>=COLUMNAS || col<0) jugada_correcta=0;
  if (jugada_correcta==1) {
    if (tablero[fila][col]=='0' || tablero[fila][col]=='X') jugada_correcta=0;
  }

  if (jugada_correcta==1) {
    if (fila!=FILAS-1 && tablero[fila+1][col]==' ') jugada_correcta=0;
  }

  return jugada_correcta;
}
int hacer_jugada(int jug) {
  int fila,col; //Para guardar la fila y columna en la que se introduce la ficha.
  int i; //Para el contador.
  char ficha; //Para guardar la ficha del jugador actual. 0- jug1, X- jug2.
  int resultado_jugada;
 
  resultado_jugada=1;
  if (jug==0) {
  color(10);
    ficha='0';
    printf("Jugador 1: \n");
    do {
      if (resultado_jugada==0) printf("Jugada incorrecta.\n");
      printf("Introduce la columna en la que quieres colocar tu ficha: ");
      scanf("%d",&col);
      i=FILAS-1;
      if (tablero[FILAS-1][col]!=' ') {
        while(i<FILAS && (tablero[i][col]=='X' || tablero[i][col]=='0'))
          i--;
      }
      fila=i;
      resultado_jugada=jugada_correcta(fila,col);
    } while(resultado_jugada==0);

  } else {
    do {
      col=hacer_jugada2();
      i=FILAS-1;
     
      if (tablero[FILAS-1][col]!=' ') {
        while(i<FILAS && (tablero[i][col]=='0' || tablero[i][col]=='X'))
		 i--;
      }
      fila=i;
      resultado_jugada=jugada_correcta(fila,col);
    } while(resultado_jugada==0);
  }

  if (resultado_jugada==1) {
  	tablero[fila][col]=ficha;
  }
  return resultado_jugada;
}
int hacer_jugada2(int jug) {
 int fila,col; //Para guardar la fila y columna en la que se introduce la ficha.
  int i; //Para el contador.
  char ficha; //Para guardar la ficha del jugador actual. 0- jug1, X- jug2.
  int resultado_jugada2;
 
  resultado_jugada2=1;

  if (jug==1) {
    ficha='X';
    color(14);
    printf("Jugador 2: \n");
    do {
      if (resultado_jugada2==0) printf("Jugada incorrecta.\n");
      printf("Introduce la columna en la que quieres colocar tu ficha: ");
      scanf("%d",&col);
      i=FILAS-1;
      if (tablero[FILAS-1][col]!=' ') {
        while(i<FILAS && (tablero[i][col]=='0' || tablero[i][col]=='X'))
          i--;
      }
      fila=i;
      resultado_jugada2=jugada_correcta(fila,col);
    } while(resultado_jugada2==0);
  
  } else {
    ficha='0';
    do {

      i=FILAS-1;
      if (tablero[FILAS-1][col]!=' ') {
        while(i<FILAS && (tablero[i][col]=='0' || tablero[i][col]=='X'))
          i--;
      }
      fila=i;
      resultado_jugada2=jugada_correcta(fila,col);
    } while(resultado_jugada2==0);
  }

  if (resultado_jugada2==1) tablero[fila][col]=ficha;
  return resultado_jugada2;
}
int mostrar_tablero() {
  int i,j;
  int ficha;

  system("cls");
	system("color 0F") ;
  printf("\n\t\t\t\t");
  for(j=0;j<COLUMNAS*5/2;j++) printf(" ");

  printf("CONECTA 4");
  printf("\n\t\t\t\t F -");
  for(j=0;j<COLUMNAS+1;j++) printf("----");
  printf("\n\t\t\t\t");

  for(i=0;i<FILAS;i++) {
    printf(" ");
    if (i==0)
      printf("I");
    else if (i==1)
      printf("A");
    else
      printf(" ");
     
    printf(" %d |",i);
   
    for(j=0;j<COLUMNAS;j++) {
      printf(" ");
      printf("%c",tablero[i][j]);
      printf(" |");
    }
    printf(" ");
    if (i==0) printf("\n\t\t\t\t L");
    else if (i==1) printf("\n\t\t\t\t S");
    else printf("\n\t\t\t\t  ");
   
    printf(" -");
    for(j=0;j<COLUMNAS+1;j++) printf("----");
    printf("\n\t\t\t\t");
  }
  
  printf("       ");
  for(j=0;j<COLUMNAS;j++) printf("%d   ",j);
  printf(" COLUMNAS\n\t");
  printf("\n\t\t\t\t");
}
int comprobar_fin() {
  int i,j; //Para el for, para recorrer el tablero
  int ganador; // -1: no gana nadie, 1: jug1, 0: jug2
  ganador=-1;

  //Comprobar si hay cuatro en línea en horizontal
  for(i=0;i<FILAS;i++) {
    for(j=0;j<COLUMNAS-3;j++) {
      if (tablero[i][j]=='X' && tablero[i][j+1]=='X' && tablero[i][j+2]=='X' && tablero[i][j+3]=='X'){
      	ganador=0;
      	printf("\t\tFue Horizontal");
      	printf("\n\t\tCoordenadas: \n\t\tInicia en:(%d,%d)",i,j);
      	printf("\n\t\tFinaliza en (%d,%d) ",i,j+3);
	  }
        
      else if (tablero[i][j]=='0' && tablero[i][j+1]=='0' && tablero[i][j+2]=='0' && tablero[i][j+3]=='0'){
      	ganador=1;
      	printf("\t\tFue Horizontal");
      	printf("\n\t\tCoordenadas: \n\t\tInicia en:(%d,%d)",i,j);
      	printf("\n\t\tFinaliza en (%d,%d) ",i,j+3);
	  }
        
    }
  }
  if (ganador==-1) {
    //Comprobar si hay cuatro en línea en vertical
    for(i=0;i<FILAS-3;i++) {
      for(j=0;j<COLUMNAS;j++) {
        if (tablero[i][j]=='X' && tablero[i+1][j]=='X' && tablero[i+2][j]=='X' && tablero[i+3][j]=='X'){
        ganador=0;	
        printf("\t\tFue Vertical");
      	printf("\n\t\tCoordenadas: \n\t\tInicia en:(%d,%d)",i,j);
      	printf("\n\t\tFinaliza en (%d,%d) ",i+3,j);
		}
          
        else if (tablero[i][j]=='0' && tablero[i+1][j]=='0' && tablero[i+2][j]=='0' && tablero[i+3][j]=='0'){
        	ganador=1;
        	printf("\t\tFue Vertical");
      	printf("\n\t\tCoordenadas: \n\t\tInicia en:(%d,%d)",i,j);
      	printf("\n\t\tFinaliza en (%d,%d) ",i+3,j);
		}
          
      }
    }
  }

  if (ganador==-1) {
    //Comprobar si hay cuatro en línea en diagonal 1
    for(i=0;i<FILAS;i++) {
      for(j=0;j<COLUMNAS;j++) {
        if (i+3<FILAS && j+3<COLUMNAS) {
          if (tablero[i][j]=='X' && tablero[i+1][j+1]=='X' && tablero[i+2][j+2]=='X' && tablero[i+3][j+3]=='X'){
          	ganador=0;
          	printf("\t\tFue Diagonal hacia la derecha");
      	printf("\n\t\tCoordenadas: \n\t\tInicia en:(%d,%d)",i,j);
      	printf("\n\t\tFinaliza en (%d,%d) ",i+3,j+3);
		  }
            
          else if (tablero[i][j]=='0' && tablero[i+1][j+1]=='0' && tablero[i+2][j+2]=='0' && tablero[i+3][j+3]=='0'){
          	ganador=1;
          	printf("\t\tFue Diagonal hacia la derecha");
      	printf("\n\t\tCoordenadas: \n\t\tInicia en:(%d,%d)",i,j);
      	printf("\n\t\tFinaliza en (%d,%d) ",i+3,j+3);
		  }
            
        }
      }
    }
  }

  if (ganador==-1) {
    //Comprobar si hay cuatro en línea en diagonal 2
    for(i=0;i<FILAS;i++) {
      for(j=0;j<COLUMNAS;j++) {
        if (i+3<FILAS && j-3>=0) {
          if (tablero[i][j]=='X' && tablero[i+1][j-1]=='X' && tablero[i+2][j-2]=='X' && tablero[i+3][j-3]=='X'){
          	ganador=0;
          	printf("\t\tFue Diagonal hacia la izquierda");
      	printf("\n\t\tCoordenadas: \n\t\tInicia en:(%d,%d)",i,j);
      	printf("\n\t\tFinaliza en (%d,%d) ",i+3,j-3);
		  }
            
          else if (tablero[i][j]=='0' && tablero[i+1][j-1]=='0' && tablero[i+2][j-2]=='0' && tablero[i+3][j-3]=='0'){
          	ganador=1;
          	printf("\t\tFue Diagonal hacia la izquierda");
      	printf("\n\t\tCoordenadas: \n\t\tInicia en:(%d,%d)",i,j);
      	printf("\n\t\tFinaliza en (%d,%d) ",i+3,j-3);
		  }
            
        }
      }
    }
  }
  
  return ganador;
}

int main (int argc,char **argv) {
  int jugador; //Indica el jugador al que le toca jugar. 0-jug1 1-jug2
  int total_jugadas,partida=0,contadorjugador1=0,contadorjugador2=0,empate=0,partidas1=0,partidas2=0; //Indica el total de jugadas que se están haciendo. En las jugadas pares juega el 1, en las impares el 2.
  total_jugadas=0;

  char nombre1[20],nombre2[20],jugador1[20],jugador2[20];
  int jugadas=0,dados=0;
  system("color 0F");
  	int mapa[28][118]={

{32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32},
{32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32},
{32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32},
{32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32},
{32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32},
{32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32},
{32,32,32,32,32,32,32,32,178,178,178,178,178,32,178,32,32,32,32,178,32,178,178,178,178,178,32,178,178,178,178,178,32,178,178,178,178,178,32,178,178,178,178,178,178,32,32,32,32,178,178,178,178,178,32,178,178,178,32,178,32,32,32,32,178,32,32,32,32,32,178,32,178,178,178,32,178,32,178,178,178,178,178,32,178,178,178,178,178,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32},
{32,32,32,32,32,32,32,32,178,32,32,32,32,32,178,32,32,32,32,178,32,178,32,32,32,178,32,32,32,178,32,32,32,178,32,32,32,178,32,178,32,32,32,32,178,32,32,32,32,178,32,32,32,32,32,178,32,178,32,178,32,32,32,32,178,32,32,32,32,32,32,32,178,32,178,32,178,32,178,32,32,32,32,32,178,32,32,32,178,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32},
{32,32,32,32,32,32,32,32,178,32,32,32,32,32,178,32,32,32,32,178,32,178,32,32,32,178,32,32,32,178,32,32,32,178,32,32,32,178,32,178,32,32,32,32,178,32,32,32,32,178,32,32,32,32,32,178,32,178,32,178,32,32,32,32,178,32,32,32,32,32,178,32,178,32,178,32,178,32,178,32,32,32,32,32,178,32,32,32,178,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32},
{32,32,32,32,32,32,32,32,178,32,32,32,32,32,178,32,32,32,32,178,32,178,178,178,178,178,32,32,32,178,32,32,32,178,178,178,178,178,32,178,32,32,32,32,178,32,32,32,32,178,32,32,32,32,32,178,32,178,32,178,32,32,32,32,178,32,32,32,32,32,178,32,178,32,178,32,178,32,178,32,32,32,32,32,178,178,178,178,178,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32},
{32,32,32,32,32,32,32,32,178,32,32,32,32,32,178,32,32,32,32,178,32,178,32,32,32,178,32,32,32,178,32,32,32,178,32,32,32,32,32,178,32,32,32,32,178,32,32,32,32,178,178,178,178,178,32,178,32,178,32,178,32,32,32,32,178,32,32,32,32,32,178,32,178,32,178,32,178,32,178,178,178,178,178,32,178,32,32,32,178,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32},
{32,32,32,32,32,32,32,32,178,32,32,32,32,32,178,32,32,32,32,178,32,178,32,32,32,178,32,32,32,178,32,32,32,178,178,178,178,178,32,178,32,32,32,32,178,32,32,32,32,178,32,32,32,32,32,178,32,178,32,178,32,32,32,32,178,32,32,32,32,32,178,32,178,32,178,32,178,32,178,32,32,32,32,32,178,32,32,32,178,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32},
{32,32,32,32,32,32,32,32,178,32,32,32,32,32,178,32,32,32,32,178,32,178,32,32,32,178,32,32,32,178,32,32,32,178,32,32,32,178,32,178,32,32,32,32,178,32,32,32,32,178,32,32,32,32,32,178,32,178,32,178,32,32,32,32,178,32,32,32,32,32,178,32,178,32,178,32,178,32,178,32,32,32,32,32,178,32,32,32,178,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32},
{32,32,32,32,32,32,32,32,178,32,32,32,32,32,178,32,32,32,32,178,32,178,32,32,32,178,32,32,32,178,32,32,32,178,32,32,32,178,32,178,32,32,32,32,178,32,32,32,32,178,32,32,32,32,32,178,32,178,32,178,32,32,32,32,178,32,32,32,32,32,178,32,178,32,178,32,178,32,178,32,32,32,32,32,178,32,32,32,178,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32},
{32,32,32,32,32,32,32,32,178,178,178,178,178,32,178,178,178,178,178,178,32,178,32,32,32,178,32,32,32,178,32,32,32,178,32,32,32,178,32,178,178,178,178,178,178,32,32,32,32,178,178,178,178,178,32,178,32,178,178,178,32,32,32,32,178,178,178,178,178,32,178,32,178,32,178,178,178,32,178,178,178,178,178,32,178,32,32,32,178,32,32,32,32,205,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,196,205,32,32,32,32,32},
{32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,205,196,196,196,196,196,196,196,191,218,196,196,196,196,196,196,196,205,32,32,32,32,32,32},
{32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,205,196,196,196,196,196,191,179,179,218,196,196,196,196,196,205,32,32,32,32,32,32,32},
{32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,205,196,196,196,191,179,179,179,179,218,196,196,196,205,32,32,32,32,32,32,32,32},
{32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,186,186,186,186,186,186,32,32,32,32,32,32,32,32,32,32,32,32},
{32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,186,219,219,219,219,219,219,186,32,32,32,32,32,32,32,32,32,32,32},
{32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,186,179,219,219,219,219,219,219,179,186,32,32,32,32,32,32,32,32,32,32},
{32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,186,179,179,219,219,219,219,219,219,179,179,186,32,32,32,32,32,32,32,32,32},
{32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,186,179,179,192,196,196,196,196,196,196,217,179,179,186,32,32,32,32,32,32,32,32},
{32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,186,179,179,192,196,196,196,196,196,196,196,196,217,179,179,186,32,32,32,32,32,32,32},
{32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,179,179,192,196,196,196,196,196,196,196,196,196,196,217,179,179,32,32,32,32,32,32,32},
{32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,179,192,196,196,196,196,196,196,196,196,196,196,196,196,217,179,32,32,32,32,32,32,32},
{184,32,74,111,115,130,32,65,108,101,106,97,110,100,114,111,32,86,97,108,100,117,122,32,67,111,110,116,114,101,114,97,115,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,192,196,196,196,196,196,196,196,196,196,196,196,196,196,196,217,32,32,32,32,32,32,32},
{32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,85,78,69,84,32,32,32,32,32,32,32,32,32,32,32,32}
 };
	imprimir(mapa);
		printf("\n");
	system("PAUSE");
	system("cls");
	int continuar=0;
	do{	
	color(15);
		printf("\t\t\t\t\t\tCuatro en Linea");
		printf("\n\n\t\tSe trata de un juego compuesto por un tablero, situado en posicion vertical, \n\tEl objetivo de este juego consiste en colocar cuatro fichas en una fila continua vertical, horizontal \n\to diagonalmente. Se juega sobre un tablero de 8x8 casillas que al empezar esta vacio. ");
		color(6);
		printf("\n\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",179,95,179,95,179,95,179,95,179,95,179,95,179,95,179,95,179);
		printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",179,95,179,95,179,95,179,95,179,95,179,95,179,95,179,95,179);
		printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",179,95,179,95,179,95,179,95,179,95,179,95,179,95,179,95,179);
		printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",179,95,179,95,179,95,179,95,179,95,179,95,179,95,179,95,179);
		printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",179,95,179,95,179,95,179,95,179,95,179,95,179,95,179,95,179);
		printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",179,95,179,95,179,95,179,95,179,95,179,95,179,95,179,95,179);
		printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",179,95,179,95,179,95,179,95,179,95,179,95,179,95,179,95,179);
		printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",179,95,179,95,179,95,179,95,179,95,179,95,179,95,179,95,179);
		color(15);
		printf("\n\n\t\tComo jugar:\n\t Ambos jugadores sit%can sus fichas (una por movimiento) en el tablero. La regla para colocarlas consiste\n\t en que estas siempre %ccaen hasta abajo%c.Se muestra un ejemplo de la posici%cn de una\n\tpartida en curso donde las cruces señalan las casillas donde el jugador puede colocar una nueva ficha",163,34,34,162); 
		color(10);
		printf("\n\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",179,95,179,95,179,95,179,95,179,95,179,95,179,95,179,95,179);
		printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",179,95,179,95,179,95,179,95,179,95,179,95,179,95,179,95,179);
		printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",179,95,179,95,179,95,179,95,179,95,179,95,179,95,179,95,179);
		printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",179,95,179,95,179,95,179,206,179,95,179,95,179,95,179,95,179);
		printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",179,95,179,95,179,206,179,79,179,95,179,95,179,95,179,95,179);
		printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",179,95,179,206,179,79,179,88,179,95,179,95,179,95,179,95,179);
		printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",179,206,179,88,179,79,179,79,179,95,179,95,179,95,179,95,179);
		printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",179,79,179,88,179,88,179,88,179,206,179,206,179,206,179,206,179);
		printf("\n\n");
		color(15);
		system("PAUSE");
		system("cls");
		fflush(stdin);
		color(15);
		printf("\t\t\t\t\t\tCuatro en Linea");
		printf("\n\n\t\t\t\tNombre Jugador 1: ");
		fflush(stdin);	
		gets(nombre1);
		printf("\n\t\t\t\tNombre Jugador 2: ");
		fflush(stdin);
		gets(nombre2);
			int l,a,lanzamiento=0;
		while(lanzamiento==0||l==a){
			dados=0;
			dados++;
		color(11);
			fflush(stdin);
			printf("\n\t\t\t\tDecidiremos quien sera el jugador 1:");
			printf("\n\t\t %s Lanza los dados: ",nombre1);
			getch(l);
			fflush(stdin);
			srand(time(NULL));
			l=rand()%103;
			
			if(l>=0&&l<=17){
				l=1;
			printf("1");
			}
			if(l>17&&l<=34){
				l=2;
			printf("2");
			}
			if(l>34&&l<=51){
				l=3;
				printf("3");
			}
			if(l>51&&l<=68){
				l=4;
				printf("4");
			}
			if(l>68&&l<=85){
				l=5;
				printf("5");
			}
			if(l>85&&l<=102){
				l=6;
				printf("6");
			}
			printf("\n\t\t %s Arroja los dados: ",nombre2);
			getch(a);
			fflush(stdin);
			srand(time(NULL));
			a=rand()%104;
			if(a>=0&&a<=17){
				a=1;
			printf("1");
			}
			if(a>17&&a<=34){
				a=2;
			printf("2");
			}
			if(a>34&&a<=51){
				a=3;
				printf("3");
			}
			if(a>51&&a<=68){
				a=4;
				printf("4");
			}
			if(a>68&&a<=85){
				a=5;
				printf("5");
			}
			if(a>85&&a<=103){
				a=6;
				printf("6");
			}			
			if(l==a){
				printf("\n\n\t\tlanzaran los dados denuevo");
				printf("\n\n");
				dados++;
			}
			if(l<a){
				color(10);
				printf("\n\n\t\t\t\t ---%s Eres el jugador 1---",nombre2);
				strcpy(jugador1,nombre2);
				strcpy(jugador2,nombre1);
				
			}
			if(l>a){
				color(10);
				printf("\n\n\t\t\t\t ---%s Eres el jugador 1---",nombre1);
				strcpy(jugador1,nombre1);
				strcpy(jugador2,nombre2);
			}
			printf("\n\n");
			color(4);		
			system("PAUSE");
	
			
			lanzamiento=1;
		}
		partida=0;
		while(partida<4){
		inicializar_tablero();	
		
		 do {
	    if (total_jugadas % 2 == 0){
	    	jugador=0;
	    	partidas1++;
		}
	      
	    else{
	    	jugador=1;
	    	partidas2++;
		}
	      
	      
	    total_jugadas++;
	    mostrar_tablero();
	   
	    if (hacer_jugada(jugador)==0) {
	      printf("Jugada incorrecta.\n\n");
	      system("pause");
	    }
	    jugadas++;
	  } while(comprobar_fin()==-1);
	
	  mostrar_tablero();
		if (comprobar_fin()==1){
			color(10);
		printf("\n\t%s ha ganado la partida!!\n\n",jugador1);
		contadorjugador1++;	
		}
	    
	  else{
	  	color(14);
	  	printf("\n\t%s ha ganado la partida!!\n\n",jugador2);
	  	contadorjugador2++;
	  }
	  if(contadorjugador1>=3&&contadorjugador2<=1){
	  	
	  	printf("\t\tGanador Indiscutible: ");
	  	color(10);
	  	printf("\n\tJugador 1: %s",jugador1);
	
	  }
	    if(contadorjugador2>=3&&contadorjugador1<=1){
	  	printf("\t\tGanador Indiscutible: ");
	  	color(14);
	  	printf("\n\tJugador 2: %s",jugador2);
	
	  }
	  if(contadorjugador1==2&&contadorjugador2==2){
	  	partida=2;
	  	empate++;
	  }
	  printf("\n\n");
	  system("PAUSE");
	  getchar();
	  system("cls");
	  partida++;	
		}
		partida=partida+empate;
		color(15);
		printf("\t\t\t\t\t\tCuatro en Linea");
		printf("\n\t\tPartidas Jugadas: %d ",partida);
		printf("\n\t\tTotal de Jugadas durante el juego: %d",total_jugadas), color(10);
		printf("\n\n\t\t%s:",jugador1);
		printf("\n\t\tJugadas: %d",partidas1);
	printf("\n\t\tPartidas Ganadas: %d",contadorjugador1),color(14);
		printf("\n\n\t\t%s:",jugador2);
		 printf("\n\t\tJugadas: %d",partidas2);
	printf("\n\t\tPartidas Ganadas: %d",contadorjugador2),color(15);
	
	printf("\n\n\t\tGanador Lanzamiento de Dados: %s",jugador1);
	printf("\n\t\tSe lanzaron los dados, en la(s) partida(s) 1");
	printf("\n\t\tEmpates: %d",empate);
	if(empate>=1){
		int empatess=0;
	empatess=100*empate;
	empatess=empatess/partida;
	printf("\n\t\tPorcentaje de empates en juego %d%c",empatess,37);
	}
	 if(contadorjugador1>=3&&contadorjugador2<=2){
	  	color(10);
	  	printf("\n\t\tGanador Indiscutible: ");
	  	printf("\n\t\t%s\n\t\t victorias: %d\n\t\t Derrotas:%d ",jugador1,contadorjugador1,contadorjugador2);
	
	  }
	    if(contadorjugador2>=3&&contadorjugador1<=2){
	    color(14);	
	  	printf("\n\t\tGanador Indiscutible: ");
	  	printf("\n\t\t%s\n\t\t victorias: %d\n\t\t Derrotas:%d",jugador2,contadorjugador2,contadorjugador1);
	
	  }
	  
	
	 
	  color(15);
	printf("\n\n\t\tSi desea Volver a Jugar presione (0)\n\t\tSi no, presione (1): ");
	scanf("%d",&continuar);
	system("cls");
	}while(continuar==0);
		printf("\n\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",179,95,179,95,179,95,179,95,179,95,179,95,179,95,179,95,179);
		printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",179,95,179,95,179,95,179,95,179,95,179,95,179,95,179,95,179);
		printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",179,95,179,72,179,65,179,83,179,84,179,65,179,95,179,95,179);
		printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",179,95,179,95,179,95,179,95,179,95,179,95,179,95,179,95,179);
		printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",179,95,179,76,179,85,179,69,179,71,179,79,179,95,179,95,179);
		printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",179,95,179,95,179,95,179,95,179,95,179,95,179,95,179,95,179);
		printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",179,95,179,95,179,95,179,95,179,95,179,95,179,95,179,95,179);
		printf("\n\t\t\t\t%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",179,95,179,95,179,95,179,95,179,95,179,95,179,95,179,95,179);
		printf("\n\n\t\t\tPara mas informacion:");
		printf("\n\t\t\t%c Jos%c Alejandro Valduz Contreras",184,130);
		printf("\n\t\t\tjose.valduz%cunet.edu.ve",64);
		printf("\n");
		system("PAUSE");
}
void  color(int c){

	HANDLE consol;
	consol = GetStdHandle
		(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute
		(consol, c);
}
void imprimir(int pes[28][118]){
	int fi,co;
	for(fi=0;fi<28;fi++){
		printf("\n");
		for(co=0;co<118;co++){
			printf("%c",pes[fi][co]);
		}
	}
}

