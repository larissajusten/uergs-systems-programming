/* Considerando um vetor V[100] de inteiros, escreva um programa que leia o vetor e, a seguir, conte 
e imprima o numero de elementos divisiveis por tres e calcule a media aritmetica de todos os elementos do vetor */

#include <stdio.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#define n 100

main(){
	int vet[n], num[n];
	int i, a;
	float count = 0;
	
	srand(time(NULL));
	for(i=0; i<n; i++){
	vet[i] = rand() %n;
	}
	i = ler_vetor(vet, num);
	printf("Numero de elementos divisiveis por 3: %d", i);
	for(a=0; a<i; a++){
//	printf("\n ~%d~", num[a]); Lista dos numeros
	count = num[a] + count;	
	}
//	printf("\n ~ %d", count); Contagem antes de dividir
	count = count/i;
	printf("\nMedia Aritmetica: %0.1f", count);
}

int ler_vetor(int vet[], int *num){
	int a, i, j, count;
	i = 0;
	for(a=0; a<n; a++){
		j = vet[a] % 3; 
		if(j==0){
			num[i] = vet[a];
//			printf("%d - ", num[i]);
			i++;
		}
	}
	return i;
//	int m;
//	for(m=0; m<n; m++)
//	printf("%d - ", vet[m]);
}



