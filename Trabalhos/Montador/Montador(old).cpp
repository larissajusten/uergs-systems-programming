#include <stdio.h>
#include <fstream>
#include <iostream> 
#include <string>
#include <vector>
using namespace std;

#define push  4 
#define add   5
#define sub   6
#define mul   7
#define div   8
#define store 9
#define jmp   10
#define jeq   11
#define jgt   12
#define jlt   13
#define in    14
#define out   15
#define stp   16

typedef struct tabsim{
	string palavra;
	int endereço;
}Tabela_Simbolos;

Tabela_Simbolos tab_sym[50];

void passo1();
const vector<string> explode(const string& s, const char& c);

int main() /* LINUX - int argc, char* argv[] */
{
	passo1();
	passo2();
}

void passo1() /* Ler arquivo fonte e cria tabela de simbolos */
{
	/* Abrir arquivo */
	int n = 0;
	string linha_f;
	vector<string> linha;
	ifstream leitura;
	
	leitura.open("arqfonte.txt");
	if(!leitura.is_open()){ /* Verifica se o arquivo pode ser aberto, se sim retorna 0 */
		cout<<"Nao foi possivel abrir arquivo! Programa sera terminado!" << endl;	
	}
	
	while(!leitura.eof()){
	
		getline(leitura,linha_f);

		cout << linha_f << endl;
		linha = explode(linha_f,' ');
		n = strtok (linha_f," ");
		
		switch(n){
			case 1: /* Uma palavra */
			break;
			case 2: /* Duas palavras */
			break;
			case 3: /* Tres palavras*/
			break;
			default:
		}

		tab_sym[i].palavra = linha[1];
			/*if(palavra != " "){
			cout << "Palavra:" << tab_sym[i].palavra << " ";
			tab_sym[i].end = i;
			cout << "End:" << tab_sym[i].end << " ";
			cout << "i:" << i << endl;
			i++;
		}*/
	}
	cout << " " << endl;
	/* Final passo 1 = END */
}

void passo2()
{


}

const vector<string> explode(const string& s, const char& c)
{
	string buff{""};
	vector<string> v;
	
	for(auto n:s)
	{
		if(n != c) buff+=n; else
		if(n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if(buff != "") v.push_back(buff);
	
	return v;
}
