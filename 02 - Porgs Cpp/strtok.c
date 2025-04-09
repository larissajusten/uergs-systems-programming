#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
char sentence[500], *word;
int ct=0;
printf("Sentence: ");
gets(sentence);
word = strtok( sentence , " " );
printf( "%s \n", word );

while( word != NULL ) {
    printf( "%s \n", word );
    word = strtok( NULL, " " );
    ct = ct + 1 ;
    }
printf("\n");
puts(sentence);
printf( "Numero de Palavras: %d\n ", ct );
system("PAUSE");    
}
