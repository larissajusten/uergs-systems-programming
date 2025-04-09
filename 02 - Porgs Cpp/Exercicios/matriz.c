/*Considerando uma matriz de inteiros (10,10), que possui valores positivos e negativos, escreva um algoritmo para:
a. Ler a matriz;
b. Contar a quantidade de valores maiores que 20
existentes em cada linha da matriz;
c. Substituir todos os elementos negativos da segunda linha
pelo valor 5. */ 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#define n 2

main(){
int mat[n][n], i , j;	
for (i=0;i<n;i++)
	for (j=0;j<n;j++)
		scanf ("%d", &mat[i][j]); // linha - coluna
ler(mat);
contar(mat);
//substituir(mat);
//ler(mat);
}

int ler(int mat[n][n]){
	int a, b;
	for (a=0;a<n;a++){
		for (b=0;b<n;b++){
			printf("%i ~ ", mat[a][b]);	
		}
	printf("\n");
	}
}
int contar(int mat[n][n]){
	int count[n], a, b;
	
		for (a=0;a<n;a++){
			if(mat[a][0] >= 20){
			printf("1");
			count[b] +=1;
			}
		}
}
//int substituir(){	
//}
