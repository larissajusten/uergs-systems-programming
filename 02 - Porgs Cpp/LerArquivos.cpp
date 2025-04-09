#include <stdio.h>
int main (){
  FILE * f ;
  int x, y ;
  char nomeArq [30] ;
    
    printf("digite o nome do arquivo\n") ;
    scanf("%s", nomeArq) ;
    f = fopen (nomeArq, "r") ;
    while (!feof(f)) {
        fscanf (f, "%d%d", &x, &y) ;
        printf(" x= %d   y= %d\n", x, y) ;
	}
}
 
