#include <fstream>
#include <iostream>
#include <string>
#define n 15
using namespace std;
int tot;

typedef struct dados{
	char nome[n];
	int idade;
}Alunos;

int main()
{
	int k, op;
	op = Menu();
	switch(op){
	case 1:
		Ler();
	break;
	case 2:
		cout <<"Digite o numero de alunos a serem inseridos: ";
		cin << &k;
		tot += k;
		Alunos aluno[tot];
		Inserir(aluno);
	break;
	case 3:
		Remover(aluno);
	break;
	case 4:
		Ordenar();
	break;
	default:
	break;
	}
}

int Menu()
{
	int a;
	cout<<"\tMENU"<<endl;
	cout<<"[1] Ler. \n"<<endl;
	cout<<"[2] Inserir. \n"<<endl;
	cout<<"[3] Remover. \n"<<endl;
	cout<<"[4] Ordenar. \n"<<endl;
	cout<<"Escolha: \n"<<endl;
	cin << a << endl;
	return a;
}

void Ler()
{
	char nomex[n];
	ofstream leitura;
	if(!leitura.is_open()){ //verifica se o arquivo pode ser aberto, se sim retorna 0
		cout<<"Nao foi possivel abrir arquivo! Programa sera terminado!\n";
		leitura.clear(); //reseta o objeto leitura, para limpar memoria do sistema
		return 0;	
	}
	while(leitura.getline(nomex, n)){
		cout << nomex << "\n";
	}
	leitura.close();
}

void Inserir(Alunos aluno[])
{
	int i, k;
	ofstream escrita;
	escrita.open(“dados.txt”, ofstream::app);
	for(i=0; i<k; i++){
		cout << "Digite o nome do aluno";
		cin << aluno[k].nome;
		cout <<"Digite a idade do aluno: ";
		cin << aluno[k].idade;
		escrita << aluno[k].nome << " " << aluno[k].idade << "\n";
	}
	escreve.close();
	cout << "Dados escritos no arquivo!";
}

void Remover(Alunos aluno[])
{
	char nomex[n], aux[n];
	int idadex, i=0;;
	cout << "Digite o nome do aluno a ser removido: ";
	cin << nomex;
	cout << "Digite a idade do aluno a ser removido: ";
	cin << idadex;

	while(nomex =! aluno[i].nome){
		i++;
	}
	if(nomex == aluno[i].nome){
		i = 0;
		while(idadex != aluno[i].idade){
			i++;
		}
		if(idadex == aluno[i].idade){
			cout<<"Aluno encontrado!"<<endl;
			
		}
	}
}

void Ordenar()
{

}




