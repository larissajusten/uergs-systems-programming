#include <stdio.h>
#include <fstream>
#include <iostream> 
#include <string>
#include <vector>
using namespace std;

#define push  	"0" //2
#define add   	"1" //1
#define sub   	"2" //1
#define mul   	"3" //1
#define div   	"4" //1
#define store 	"5" //2
#define jmp   	"6" //2
#define jeq   	"7" //2
#define jgt   	"8" //2
#define jlt   	"9" //2
#define in    	"10" //2
#define out   	"11" //2
#define stp   	"12" //1
#define nop 	"13" //1 
#define endp 	"14" //1

#define TAMTAB 20

struct tab_sym{
	string palavra;
	int endr;
};

vector<tab_sym> tbsym;
int county = 0, f_erro = 0;
string arqin;
string arqout;

void criar_tab();
void gera_codigo();
int le_tab();
void le_arq(int op);

const vector<string> explode(const string& s, const char& c);

int main() /* int argc, char* argv[] ./exec arq_mont.txt arq_gera.txt */
{
	int op;
	/*if(argc != 3){
        cout << "Numero invalido de argumentos" << endl;
    }
    else{
        arqin = argv[1];
        arqout = argv[2];
    }*/
    while(op!=9){
	    cout << "Escolher op:" << endl;
		cout << "1 - Criar tabela." << endl;
		cout << "2 - Criar codigo." << endl;
		cout << "3 - Ler tabela." << endl;
		cout << "4 - Ler arquivo IN." << endl;
		cout << "5 - Ler arquivo OUT." << endl;
		cout << "9 - Fechar programa." << endl;
		cout << "OP: ";
		cin >> op;
		
		switch(op){
			case 1:
				criar_tab();
				break;
			case 2:
				gera_codigo();
				break;
			case 3:
				le_tab();
				cout << " " << endl;
				break;
			case 4:
				le_arq(op);
				break;
			case 5:
				le_arq(op);
				break;
			case 9:
				break;
			default:
				cout << " " << endl;
				cout << "Op invalida!" << endl;
				cout << " " << endl;
		}
	}
}

void criar_tab()
{
	int n = 0, i, tmp = 0, ins_end; 
	int countx = 0; 

	string linhax, strtmp, strtmp1;
	vector<string> linha;
	ifstream leitura;
	
	leitura.open("arqfont2.txt");
	if(!leitura.is_open()){ /* Verifica se o arquivo pode ser aberto, se sim retorna 0 */
		cout<<"Nao foi possivel abrir arquivo! Programa sera terminado!" << endl;	
	}

	ins_end = 0;
	while((!leitura.eof()) and (ins_end != 1)){
		
	getline(leitura,linhax);
	cout << " " << endl;
	cout << "Linha lida: ";
	cout << linhax << endl;
	linha = explode(linhax,' ');
	
	county++;
	n = linha.size();
		switch(n){
	 		case 1: /* Uma palavra - ADD; STOP; END */
				if((linha[0]) == "stp"){ //STP
					exit(0);
				}else if(linha[0] == "endp"){//ENDP
					ins_end = 1;
				}else{ //NOP - ADD
					cout << "ERRO Instrucao " << strtmp1 << " invalida!" << endl;
					f_erro = 1;
					break;
				}
			break;
			case 2: /* Duas palavras - INST|VAR; INST|LABEL; LABEL|INST */
				strtmp = linha[1];
				strtmp1 = linha[0];
				
				if((strtmp != "add") and (strtmp != "sub") and (strtmp != "mul") and (strtmp != "div")){ /* Excluindo caso: LABEL|INST */
					if((strtmp1 == "jmp") or (strtmp1 == "jeq") or (strtmp1 == "jgt") or (strtmp1 == "jlt")){ /* JUMP(strtmp1) LABEL(strtmp) */
						for(i=0; i < tbsym.size(); i++){	
							if(strtmp == tbsym[i].palavra){
								cout << "ERRO Label: " << strtmp << " ja esta na tabela." << endl;
								break;
							}
						}
						if(i == tbsym.size()){
							countx++;
							tab_sym n1;
							n1.palavra = strtmp;
							n1.endr = county;
							tbsym.push_back(n1);
						}
						
					}else{/* INST(strtmp1) VAR(strtmp) */
						if((strtmp1 == "in") or (strtmp1 == "out") or (strtmp1 == "push") or (strtmp1 == "store")){
							i = 0;
							while(i != tbsym.size()){
								if(strtmp == tbsym[i].palavra){
									break;
								}
								i++;
							}
							if(i == tbsym.size()){
								cout << "ERRO Variavel: " << strtmp << " nao encontrada! Adicionar variavel!" << endl;
								f_erro = 1;
							}
						}else{
							cout << "ERRO Instrucao " << strtmp1 << " invalida!" << endl;
							f_erro = 1;
						}
					}
			}else{/* LABEL(strtmp1) INST(strtmp) */
				for(i=0; i < tbsym.size(); i++){
					if(strtmp1 == tbsym[i].palavra){
							cout << "ERRO Label: " << strtmp1 << " repetida." << endl;
							f_erro = 1;
					}
				}
				if(i == tbsym.size()){
					countx++;
					tab_sym n1;
					n1.palavra = strtmp1;
					n1.endr = county;
					tbsym.push_back(n1);
				}
			break;
			case 3: /* Tres palavras - VAR|INST|X; LABEL|INST|VAR */
				if(linha[1] == "space"){
					strtmp = linha[0];
					strtmp1 = linha[2];
					tab_sym n1;
					n1.palavra = strtmp;
					tmp = stoi(strtmp1);
					n1.endr = countx + tmp;
					tbsym.push_back(n1);
					countx++;
					county--;
				}else{
					strtmp = linha[0]; /* Label */ 
					strtmp1 = linha[2]; /* Variavel */
					i = 0;
					
					/* Verifica se a LABEL(strtmp) ja esta na tabela de simbolos */
					if((linha[1] == "jmp") or (linha[1] == "jeq") or (linha[1] == "jgt") or (linha[1] == "jlt") or (linha[1] == "in") or (linha[1] == "out") or (linha[1] == "push") or (linha[1] == "store")){
						while(i != tbsym.size()){
							if(strtmp != tbsym[i].palavra){
								i++;
							}else{
								cout << "ERRO Label: " << strtmp << " ja utilizada" << endl;
								f_erro = 1;
							}
						}
						if(i==tbsym.size()){
							countx++;
							tab_sym n1;
							n1.palavra = strtmp;
							n1.endr = county;
							tbsym.push_back(n1);
						}
						
						/* Verifica se a VARIAVEL (strtmp1) ja esta na tabela de simbolos */
						for(i=0; i < tbsym.size(); i++){
							if(strtmp1 == tbsym[i].palavra){
								break;
							}else if(strtmp1 != tbsym[i].palavra){
								cout << "ERRO Variavel: " << strtmp1 << " nao encontrada! Adicionar variavel!" << endl;
								f_erro = 1;
							}
						}	
					}else{
						cout << "ERRO Instrucao invalida!" << endl;
						f_erro = 1;
					}
				}
			break;
			default:
				cout << "ERRO Instrucao nao encontrada" << endl;
				f_erro = 1;
			break;
		}
	}
	}
	cout << " " << endl;
	leitura.close();
}

void gera_codigo()
{	

	if(f_erro == 1){
		cout << "Impossivel gerar codigo! Codigo com ERRO!" << endl;
		return;
	}
	int n, i, j;
	string linhax, strtmp, strtmp1, strtmp2;
	vector<string> linha;
	ifstream leitura;
	ofstream escreve;
	
	if(le_tab() == 1){
		cout << "Crie a tabela primeiro" << endl;
		cout << " " << endl;
		return;	
	}
	
	/* Arquivo de ENTRADA */
	leitura.open("arqfont2.txt");
	if(!leitura.is_open()){ /* Verifica se o arquivo pode ser aberto, se sim retorna 0 */
		cout<<"Nao foi possivel abrir arquivo! Programa sera terminado!" << endl;	
	}

	/* Arquivo de SAIDA */
	escreve.open("arqout.txt");
	if(!escreve.is_open()){ /* Verifica se o arquivo pode ser aberto, se sim retorna 0 */
		cout<<"Nao foi possivel abrir arquivo! Programa sera terminado!" << endl;	
	}


	do{
		
	getline(leitura,linhax);
	cout << " " << endl;
	cout << "Linha lida: ";
	cout << linhax << endl;
	linha = explode(linhax,' ');

	n = linha.size();
	switch(n){
	 	case 1: /* Uma palavra - ADD; STOP; END */
	 		cout << "Entrou no CASE1" << endl;
			if(linha[0] == "stp"){ //STP
				escreve << stp << "\n";
			}else if(linha[0] == "endp"){//ENDP
				escreve << endp << "\n";
			}else if(linha[0] == "nop"){ //NOP
				escreve << nop << "\n";
			}else if(linha[0] == "add"){ //ADD
				escreve << add << "\n";
			}else if(linha[0] == "sub"){ //SUB
				escreve << sub << "\n";
			}else if(linha[0] == "mul"){ //MUL
				escreve << mul << "\n";
			}else if(linha[0] == "div"){ //DIV
				escreve << div << "\n";
			}
		break;
		case 2: /* Duas palavras - INST|VAR; INST|LABEL; LABEL|INST */
			cout << "Entrou no CASE2" << endl;
			strtmp = linha[1];
			strtmp1 = linha[0];
			
			if((strtmp != "add") and (strtmp != "sub") and (strtmp != "mul") and (strtmp != "div") and (strtmp != "nop") and (strtmp != "endp") and (strtmp != "stp")){ /* Excluindo caso: LABEL|INST */

				/*--------------------------- JUMP(strtmp1) LABEL(strtmp) */
				if(strtmp1 == "jmp"){
					for(i=0; i < tbsym.size(); i++){	
						if(strtmp == tbsym[i].palavra){
							escreve << jmp << " " << tbsym[i].endr << "\n";
							break;
						}
					}
				}else if(strtmp1 == "jeq"){
					for(i=0; i < tbsym.size(); i++){	
						if(strtmp == tbsym[i].palavra){
							escreve << jeq << " " << tbsym[i].endr << "\n";
							break;
						}
					}
				}else if(strtmp1 == "jgt"){
					for(i=0; i < tbsym.size(); i++){	
						if(strtmp == tbsym[i].palavra){
							escreve << jgt << " " << tbsym[i].endr << "\n";
							break;
						}
					}
				}else if(strtmp1 == "jlt"){
					for(i=0; i < tbsym.size(); i++){	
						if(strtmp == tbsym[i].palavra){
							escreve << jlt << " " << tbsym[i].endr << "\n";
							break;
						}
					}
				/*----------------------------- INST(strtmp1) VAR(strtmp) */
				}else if(strtmp1 == "push"){ //PUSH
					for(i=0; i < tbsym.size(); i++){	
						if(strtmp == tbsym[i].palavra){
							escreve << push << " " << tbsym[i].endr+county << "\n";
							break;
						}
					}
				}else if(strtmp1 == "store"){
					for(i=0; i < tbsym.size(); i++){	
						if(strtmp == tbsym[i].palavra){
							escreve << store << " " << tbsym[i].endr+county << "\n";
							break;
						}
					}
				}else if(strtmp1 == "in"){
					for(i=0; i < tbsym.size(); i++){	
						if(strtmp == tbsym[i].palavra){
							escreve << in << " " << tbsym[i].endr+county << "\n";
							break;
						}
					}
				}else if(strtmp1 == "out"){
					for(i=0; i < tbsym.size(); i++){	
						if(strtmp == tbsym[i].palavra){
							escreve << out << " " << tbsym[i].endr+county << "\n";
							break;
						}
					}
				}
			/*---------------------------- LABEL(strtmp1) INST(strtmp) */
			}else{
				if(strtmp == "add"){
					for(i=0; i < tbsym.size(); i++){	
						if(strtmp1 == tbsym[i].palavra){
							escreve << add << "\n";
							break;
						}
					}
				}else if(strtmp == "sub"){
					for(i=0; i < tbsym.size(); i++){	
						if(strtmp1 == tbsym[i].palavra){
							escreve << sub << "\n";
							break;
						}
					}
				}else if(strtmp == "div"){
					for(i=0; i < tbsym.size(); i++){	
						if(strtmp1 == tbsym[i].palavra){
							escreve << div << "\n";
							break;
						}
					}
				}else if(strtmp == "mul"){
					for(i=0; i < tbsym.size(); i++){	
						if(strtmp1 == tbsym[i].palavra){
							escreve << mul << "\n";
							break;
						}
					}
				}else if(strtmp == "endp"){
					for(i=0; i < tbsym.size(); i++){	
						if(strtmp1 == tbsym[i].palavra){
							escreve << endp << "\n";
							break;
						}
					}
				}else if(strtmp == "stp"){
					for(i=0; i < tbsym.size(); i++){	
						if(strtmp1 == tbsym[i].palavra){
							escreve << stp << "\n";
							break;
						}
					}
				}else if(strtmp == "nop"){
					for(i=0; i < tbsym.size(); i++){	
						if(strtmp1 == tbsym[i].palavra){
							escreve << nop << "\n";
							break;
						}
					}
				}
			}
		break;
		case 3: /* Tres palavras - VAR|INST|X; LABEL|INST|VAR */
			strtmp = linha[0];
			strtmp1 = linha[1]; 
			strtmp2 = linha[2];

			if(strtmp1 == "space"){
				break;
			}else if(strtmp1 == "store"){
				for(i=0; i < tbsym.size(); i++){
					if(strtmp == tbsym[i].palavra){ /* Label */
						for(j=0; j < tbsym.size(); j++){
							if(strtmp2 == tbsym[j].palavra){ /* Variavel */
								escreve << store << " " << tbsym[j].endr+county << "\n";
								break;
							}
						}
					}
				}
			}else if(strtmp1 == "in"){
				for(i=0; i < tbsym.size(); i++){
					if(strtmp == tbsym[i].palavra){ /* Label */
						for(j=0; j < tbsym.size(); j++){
							if(strtmp2 == tbsym[j].palavra){ /* Variavel */
								escreve << in << " " << tbsym[j].endr+county << "\n";
								break;
							}
						}
					}
				}
			}else if(strtmp1 == "out"){
				for(i=0; i < tbsym.size(); i++){
					if(strtmp == tbsym[i].palavra){ /* Label */
						for(j=0; j < tbsym.size(); j++){
							if(strtmp2 == tbsym[j].palavra){ /* Variavel */
								escreve << out << " " << tbsym[j].endr+county << "\n";
								break;
							}
						}
					}
				}
			}else if(strtmp1 == "jmp"){
				for(i=0; i < tbsym.size(); i++){
					if(strtmp == tbsym[i].palavra){ /* Label */
						for(j=0; j < tbsym.size(); j++){
							if(strtmp2 == tbsym[j].palavra){ /* Variavel */
								escreve << jmp << " " << tbsym[j].endr+county << "\n";
								break;
							}
						}
					}
				}
			}else if(strtmp1 == "jeq"){
				for(i=0; i < tbsym.size(); i++){
					if(strtmp == tbsym[i].palavra){ /* Label */
						for(j=0; j < tbsym.size(); j++){
							if(strtmp2 == tbsym[j].palavra){ /* Variavel */
								escreve << jeq << " " << tbsym[j].endr+county << "\n";
								break;
							}
						}
					}
				}
			}else if(strtmp1 == "jgt"){
				for(i=0; i < tbsym.size(); i++){
					if(strtmp == tbsym[i].palavra){ /* Label */
						for(j=0; j < tbsym.size(); j++){
							if(strtmp2 == tbsym[j].palavra){ /* Variavel */
								escreve << jgt << " " << tbsym[j].endr+county << "\n";
								break;
							}
						}
					}
				}
			}else if(strtmp1 == "jlt"){
				for(i=0; i < tbsym.size(); i++){
					if(strtmp == tbsym[i].palavra){ /* Label */
						for(j=0; j < tbsym.size(); j++){
							if(strtmp2 == tbsym[j].palavra){ /* Variavel */
								escreve << jlt << " " << tbsym[j].endr+county << "\n";
								break;
							}
						}
					}
				}
			}
		break;
		default:
			cout << "DEFAULT" << endl;
			return;
		break;
	} /*Switch*/
	}while((!leitura.eof()) and n!=0); /*While*/
	cout << " " << endl;
	leitura.close();
	escreve.close();
} 

int le_tab()
{
	if(tbsym.size() == 0){
		cout << " " << endl;
		cout << "Tabela vazia" << endl;
		return 1;
	}
	cout << " " << endl;
	int i;
	cout << "END | VAR" << endl;
    for(i=0;i<tbsym.size();i++){
        cout << tbsym[i].endr << " | " << tbsym[i].palavra << endl;
    }
    cout << " " << endl;
}

void le_arq(int opcao)
{
	string linhax, arq;
	vector<string> linha;
	ifstream leitura;
	char armazena;
	
	switch(opcao){
		case 4:
			arq = "arqfont2.txt";
			break;
		case 5:
			arq = "arqout.txt";
			break;
		default:
			return;
			break;
	}
	
	leitura.open(arq);
	if(!leitura.is_open()){ /* Verifica se o arquivo pode ser aberto, se sim retorna 0 */
		cout<<"Nao foi possivel abrir arquivo! Programa sera terminado!" << endl;	
	}

	while(leitura.get(armazena)){
		cout << armazena;
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
