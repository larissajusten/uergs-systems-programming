#include <stdio.h>
#include <fstream>
#include <iostream> 
#include <string>
#include <vector>
using namespace std;

#define push  0
#define add   1
#define sub   2
#define mul   3
#define div   4
#define store 5
#define jmp   6
#define jeq   7
#define jgt   8
#define jlt   9
#define in    10
#define out   11
#define stp   12

typedef struct{
	int cod;
	int op;
}Memoria;
Memoria Mem[512]; 

int PC = 0;
int SP = 512;
int CS, DS;

void get_cod();
void MV();
/*void save_mem(); */
const vector<string> explode(const string& s, const char& c);

	
int main()
{	
	int i = 0;
	for(i=0; i < 512; i++){
		Mem[i].cod = -1;
		Mem[i].op = -1;
	}
	get_cod();
	MV();
	//save_mem();
}

void get_cod()
{
	cout << "Pegando arquivo e salvando na memoria" << endl;
	int tmp_PC = 0;
	string linha_f;
	vector<string> linha;
	ifstream leitura;
	
	leitura.open("arqout.txt");
	if(!leitura.is_open()){ //verifica se o arquivo pode ser aberto, se sim retorna 0
		cout<<"Nao foi possivel abrir arquivo! Programa sera terminado!" << endl;	
	}
	
	while(!leitura.eof()){
		
		getline(leitura,linha_f);

		cout << linha_f << endl;
		linha = explode(linha_f,' ');

		Mem[tmp_PC].cod = stoi(linha[0]);
		//cout << Mem[tmp_PC].cod << " ";
		
		Mem[tmp_PC].op = stoi(linha[1]);
		//cout << Mem[tmp_PC].op << endl;

		tmp_PC++;
	}
	cout << "" << endl;
}

void MV()
{
	int i = 0;
	cout << "Simulando o arquivo." << endl;
	while(PC >= 0){
		i = PC;
		cout << "\nPC:" << PC << ", cod:"<<Mem[i].cod << ", op:" << Mem[i].op<<endl;
		PC = PC +1;
		switch(Mem[i].cod){
			case push: // sp--; stack[sp] = mem[op];
				//cout << "push"<<endl;
				SP--;
				Mem[SP].cod = Mem[Mem[i].op].cod;
				break;	
			case add: // stack[sp] = stack[sp] + stack[sp+1];
				//cout << "Add"<<endl;
				Mem[SP].cod += Mem[SP+1].cod;
			break;
			case sub: // stack[sp]=stack[sp] - stack[sp+1];
				//cout << "Sub"<<endl;
				Mem[SP].cod -= Mem[SP+1].cod;
			break;
			case mul: // stack[sp]=stack[sp] * stack[sp+1];
				//cout << "mul"<<endl;
				Mem[SP].cod *= Mem[SP+1].cod;
			break;
			case div: // stack[sp]=stack[sp] / stack[sp+1];
				//cout << "Div"<<endl;
				Mem[SP].cod /= Mem[SP+1].cod;
			break;
			case store: // mem[op] = stack[sp];
				//cout << "store"<<endl;
				Mem[Mem[i].op] = Mem[SP];
			break;
			case jmp: // pc = op;
			 	//cout << "jmp"<<endl;
				PC = Mem[i].op;
			break;
			case jeq: // if (stack[sp] == 0) pc = op;
				//cout << "jeq"<<endl;
				if(Mem[SP].cod == 0){
					PC = Mem[i].op;
				}
			break;
			case jgt: //if (stack[sp] > 0) pc = op;
				//cout << "jgt"<<endl;
				if(Mem[SP].cod > 0){
					PC = Mem[i].op;
				}
			break;
			case jlt: //if (stack[sp] < 0) pc = op;
				//cout << "jlt"<<endl;
				if(Mem[SP].cod < 0){
					PC = Mem[i].op;
				}
			break;
			case in: //mem[op] armazena “dados lidos”
				cout << "Escreva o numero:" << endl;
				cin >> Mem[Mem[i].op].cod;
			break;
			case out: //mem[op] “contem dados a serem impressos”
				cout <<"Endr: " <<Mem[i].op <<" Dado: " <<Mem[Mem[i].op].cod << endl;
			break;
			case stp://stp "fim de execução"
				cout << "\nFim de execucao do programa!" << endl;
				PC = -1;	
			break;
			default: 
				cout << "ERRO" <<endl;
			break;
		}	
	}
}

/*void save_mem()
{
	cout << "salvando resultados" << endl;
	int tmp_PC = 0;
	ofstream escreve;
	
	escreve.open("MV_out.txt");
	if(!escreve.is_open()){ //verifica se o arquivo pode ser aberto, se sim retorna 0
		cout<<"Nao foi possivel abrir arquivo! Programa sera terminado!" << endl;	
	}
	
	while(tmp_PC < 512){
		if(Mem[tmp_PC].cod != -1){
			escreve << Mem[tmp_PC].cod << " ";
			if(Mem[tmp_PC].op != -1){
				escreve << Mem[tmp_PC].op << endl;
			}else{
				escreve << endl;
			}
		}else{
			escreve << endl;
		}
		tmp_PC++;
	}
}*/
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

/*
arquivo que tu vai ler

in a
in b
push a
push b
add
store c
out c
stp
*/



