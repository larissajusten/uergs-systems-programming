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
#define nop   17

struct tab_sym{
	string palavra;
	int end;
};

vector<tab_sym> tbsym;

void ini_vars();
void criar_tab();
void gerar_cod();
const vector<string> explode(const string& s, const char& c);

int main() /* LINUX - int argc, char* argv[] */
{
	/*if(argc > 3 or argc < 2){
        cout << "Numero invalido de argumentos" << endl;
    }
    else{
        if(argc == 2){
            
            
        }else if(argc == 3){
            
        }
    }*/
    criar_tab();
    gerar_cod();
}

void criar_tab() /* Ler arquivo fonte e cria tabela de simbolos */
{
	/* Abrir arquivo */
	int n = 0, i = 0, countx = 0;
	char *word;

	string linhax, strtmp;
	vector<string> linha;
	ifstream leitura;
	
	leitura.open("arqfonte.txt");
	if(!leitura.is_open()){ /* Verifica se o arquivo pode ser aberto, se sim retorna 0 */
		cout<<"Nao foi possivel abrir arquivo! Programa sera terminado!" << endl;	
	}

	getline(leitura,linhax);
	cout << linhax << endl;
	linha = explode(linhax,' ');
		

	/*n = strtok (linhax," ");
	printf( "%s \n", word );
	while( word != NULL ) {
		printf( "%s \n", word );
		word = strtok( NULL, " " );
		n = n + 1 ;
	}*/
	
	while(!leitura.eof()){
		switch(n){
			case 1: /* Uma palavra - ADD; STOP; END */
				if((linha[0]) == "16"){ //END or STP?
					exit(1);
				}else{ //NOP - ADD
					break;
				}
			break;
			case 2: /* Duas palavras - INST|VAR; INST|LABEL */
				strtmp = linha[1];
				while((strtmp != tbsym[countx].palavra) && (countx != i)){
					countx++;
				}
				if(strtmp == tbsym[countx].palavra){
					cout << strtmp << "repetida" << endl;
				}else{
					tbsym[i].palavra = strtmp;
					tbsym[i].end = i;
					i++;
				}
			break;
			case 3: /* Tres palavras - VAR|INST|X; LABEL|INST|VAR */
				if(linha[1] == "space"){
					tbsym[i].palavra = linha[0];
					tbsym[i].end = i;
					i++;
				}else{
					while(countx!=2){
						tbsym[i].palavra = linha[0];
						tbsym[i].end = i;
						i++;
						countx++;
					}
				}
			break;
			default:
			break;
		}
	}
	cout << " " << endl;
	/* Final passo 1 = STP(inst) */
}

void gerar_cod()
{

}

void ini_vars()
{
   int i;
    for(i=0;i<20;i++){
        tbsym[i].palavra = "";
        tbsym[i].end = 0;
    }
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
