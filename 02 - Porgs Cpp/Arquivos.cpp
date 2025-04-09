#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main(){
	string frase;
	char armazena;
	cout << "Escreva uma frase para ser escrita no arquivo teste.txt";
	getline(cin, frase);
	cout << "Obrigado. Escrevendo dados no arquivo teste.txt...\n";
	ofstream escreve;
	if(!escreve.is_open()){ //verifica se o arquivo pode ser aberto, se sim retorna 0
		cout<<"Nao foi possivel abrir arquivo! Programa sera terminado!\n";
		escreve.clear(); //reseta o objeto leitura, para limpar memoria do sistema
		return 0;	
	}
	escreve.open("teste.txt");
	escreve << "Utilizamos os objetos ofstream para escrever em arquivos\n";
	escreve << "Note que podemos utlizar os caracteres \\n para quebrar linha, como faziamos em cout\n";
	int numero = 100;
	escreve << "Podemos escrever o valor de variaveis numericas" << numero << "\n";
	int matriz[3] = {42,19,99};
	escreve << "Podemos também escrever matrizes!";
	for(int i=0; i<3; i++){
		escreve.width(6);
		escreve << matriz[i]<<" ";
	}
	escreve << "\n";
	escreve << "Finalmente, podemos receber dados via cin e escrever estes dados no arquivo!\n";
	escreve << "A frase que você digitou durante a execução do programa: "<<frase<<"\n";
	escreve.close(); //fechar arquivo
	cout << "Dados escritos no arquivo. Fim do Programa!";
	//leitura do arquivo
	ifstream leitura;
	leitura.open("teste.txt");
	if(!leitura.is_open()){ //verifica se o arquivo pode ser aberto, se sim retorna 0
		count<<"Nao foi possivel abrir arquivo! Programa sera terminado!\n";
		leitura.clear(); //reseta o objeto leitura, para limpar memoria do sistema
		return 0;	
	}
	while(leitura.get(armazena)){
		cout << letra;
	}
	/*
	Ler uma palavra inteira: 
	char matriz_chars[80];
	leitura >> matriz_chars;

	Ler uma linha inteira:
	char matriz_chars[80];
	leitura.getline(matriz_chars, 80);
	*/
	leitura.close();
	system("PAUSE");
	return 0;
}