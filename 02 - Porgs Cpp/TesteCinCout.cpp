#include <iostream> 
#include <string.h>
#include <time.h>
#include <cstdlib>

using namespace std;
int main () {
   int i, k; 
   float j ;
   string nome, nome1;
   srand(time(NULL));
	k = rand()%100 ;
   cout <<"Numero aleatorio: "<< k<< endl;
   cout <<"digite um valor inteiro: " << endl;
   cin >> i;
   cout << i << endl;
   cout <<"digite um valor com ponto flutuante:" << endl;
   cin >> j;
   cout <<"digite um nome:" << endl;
   cin >> nome;
   cout <<nome << endl ;
   nome1 = nome ;
   cout << "Variavel nome1:" << nome1 << endl ;
   cout << i << endl << j << endl ;
   system("PAUSE");  
}
   
