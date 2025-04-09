#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define QTD_ARQS (40)
int PC = 0;
int SP = 511;
int CS;
int DS;
int ct;
int i = 0; // n linhas
int lpc = 0; //linhas q precisam de conversao
int TS = 0;


void reead(string *nomeArquivoIn, string nomeArquivoOut, int QuantidadeDeArquivos);
void getsimbol(string nomeArquivo, string nomeArquivoOut, int codArq);
void translate(string nomeArquivo, string nomeArquivoOut, int codArq);
void passaproarquivo(string nomeArquivo, string nomeArquivoOut, int codArq);


struct tablesymbols{
  string operador;
  int operando;
}table[512];

struct tableglobalsymbols{
  string operador;
  int operando;
}tableglobal[512];

struct tableexternsymbols{
  string operador;
  int operando;
}tableextern[512];

int cntrlts=200;
int cntrltg=250;
int cntrltx=300;

int linha[50];
int vptab[50];
int loop[50];
int conv[50];
int qtdlinhas = 0;
int qtdsimbolos = 0;
int k = 0;
int main(int argc, char const *argv[])
{
   string nomeArquivoIn[int(QTD_ARQS)];
   int qtdIn = 0;
   string nomeArquivoOut;

   if(argc >= 4){

    for (size_t i = 0; i < argc-2; i++) {
      nomeArquivoIn[i] = argv[i+1];
      cout << "Nome do " << qtdIn+1 << "º arquivo a ser lido: " << nomeArquivoIn[i] << endl;
      qtdIn++;
    }
    nomeArquivoOut = argv[argc-1];
    cout << "Nome do arquivo a ser escrito: " << nomeArquivoOut << endl;

    reead(nomeArquivoIn, nomeArquivoOut, int(qtdIn));
        k=0;

    cout << "\n \ntabela de simbolos final " << endl;
    for(k=200;k<cntrlts; k++){
      cout << "operador: "<< table[k].operador << " operando: " << table[k].operando << endl;
    }

        k=0;

    cout << "\n tabela de simbolos globais " << endl;
    for(k=250;k<cntrltg; k++){
      cout << "operador: "<< tableglobal[k].operador << " operando: " << tableglobal[k].operando << endl;
    }

        k=0;

    cout << "\ntabela de simbolos extern " << endl;
    for(k=300;k<cntrltx; k++){
      cout << "operador: "<< tableextern[k].operador << " operando: " << tableextern[k].operando << endl;
    }

    cout << "Arquivo gerado!" << endl;

   }else{
     cout << "Quantidade de paramentros isuficientes!"<< endl;
     cout << "Minimo de parametros esperados:" << endl;
     cout << "Param 1: Nome do arquivo que o ligador irá ler com o código assembly e ligar com o segundo" << endl;
     cout << "Param 2: Nome do arquivo que o ligador irá ler com o código assembly e ligar com o primeiro" << endl;
     cout << "Param 3: Nome do arquivo que o ligador irá salvar com o codigo decimal do assembly" << endl;
   }

   return 0;
}

void reead(string *nomeArquivoIn, string nomeArquivoOut, int QuantidadeDeArquivos){

  for (size_t i = 0; i < QuantidadeDeArquivos; i++) {
     cout << "reading... "<< i << " arquivo" << endl;
     cout << "nome: " << nomeArquivoIn[i] << endl;

     int ci = static_cast<int>(i);
     getsimbol(nomeArquivoIn[i], nomeArquivoOut, ci);
  }

}

void getsimbol(string nomeArquivo, string nomeArquivoOut, int codArq){
  // montar tabela de simbolos
  // labels e space
  // passar pro txt 
  // se n for space a segunda palavra ou se n for palavra e instrução correta passa direto

  string temp;
  ifstream read;  
  char opandop[512], *word;
  int convert;
  int i = 0;
  k=0;
  //char arq;
  cout << "get simbol of: " << nomeArquivo << " number " << codArq+1 << endl;

  std::string arq = nomeArquivo;
  const char *carq = arq.c_str();

  read.open(carq);
  if(read.is_open()){
    while(!read.eof()){
      while(read.getline(opandop, 512)){

        int ct = 0;
        
        word = strtok(opandop, " ");
        while( word != NULL ) {

          // ver se é label de loop

          if(strcmp(word,"in") != 0  && strcmp(word,"out") != 0 && strcmp(word,"add") != 0 && strcmp(word,"sub") != 0 && 
                strcmp(word,"mul") != 0 && strcmp(word,"div") != 0 && strcmp(word,"store") != 0 && 
                  strcmp(word,"jeq") != 0 && strcmp(word,"jmp") != 0 && strcmp(word,"jgt") != 0 && 
                    strcmp(word,"jlt") != 0 && strcmp(word,"push") != 0 && strcmp(word,"stop") != 0 &&
                      strcmp(word,"a") != 0 && strcmp(word,"b") != 0 && strcmp(word,"c") != 0 && ct == 0){
            
                        cout << word << " (label de loop, vai p tabela)" << endl;
                        loop[i]=1;
                        vptab[i]=1;
                        qtdsimbolos++;
                        // linha do loop vai para a tabela (em int)
          }

          // ver se é definição de símbolo global/local/extern para botar na tabela

          if(strcmp(word,"space") == 0 && ct ==1){
            cout << word << " it's space, put into symbol table" << endl;
            // passar space pra tabela de simbolos
            // nao passar para arquivo
            vptab[i]=1;
            qtdsimbolos++;
          }

          if(strcmp(word,"global") == 0 && ct ==1){
            cout << word << " it's global, put into symbol table" << endl;
            // passar global p tabela de simbolos globais
            // nao passar para arquivo
            vptab[i]=2;
            qtdsimbolos++;
          }

          if(strcmp(word,"extern") == 0 && ct ==1){
            cout << word << " it's extern, put into symbol table" << endl;
            // passar global p tabela de simbolos
            // nao passar para arquivo
            vptab[i]=3;
            qtdsimbolos++;
          }

          if(strcmp(word,"a") == 0 && ct ==0){
            cout << word << " (define a)" << endl;
          }
          else if(strcmp(word,"b") == 0 && ct ==0){
            cout << word << " (define b)" << endl;
          }
          else if(strcmp(word,"c") == 0 && ct ==0){
            cout << word << " (define c)" << endl;
          }
          else if(strcmp(word,"jmp") == 0 && ct == 0){
            cout << word << " (loop) " << endl;
          }

          if(strcmp(word,"a") == 0 && ct ==1){
            cout << word << " é o operando " << endl;
          }
          else if(strcmp(word,"b") == 0 && ct ==1){
            cout << word << " é o operando " << endl;
          }
          else if(strcmp(word,"c") == 0 && ct ==1){
            cout << word << " é o operando " << endl;
          }

          if(strcmp(word,"a") == 0 && ct ==2){
            cout << word << " é o operando " << endl;
          }
          else if(strcmp(word,"b") == 0 && ct ==2){
            cout << word << " é o operando " << endl;
          }
          else if(strcmp(word,"c") == 0 && ct ==2){
            cout << word << " é o operando " << endl;
          }


          if(strcmp(word,"1") == 0 && ct ==2){
            cout << word << " tamanho: 1 " << endl;
          }
          else if(ct == 2 && strcmp(word,"2") == 0){
            cout << word << " tamanho: 2 " << endl;
          } 
          else if(ct == 2 && strcmp(word,"3") == 0){
            cout << word << " tamanho: 3 " << endl;
          }


          word = strtok( NULL, " " );
          ct = ct + 1;          
        } 
        linha[i] = ct; 
        cout << linha[i] << endl;
        cout << ct << "=ct" << endl;
        cout << i << "=i" << endl; 
        i++;
        qtdlinhas++;
        k = i;
      }
    }
    cout << "nlinhas: " << qtdlinhas << endl;
    cout << "nlinhas tabela simb: " << qtdsimbolos << endl;
    cout << "pos 1 tab simbolos " << cntrlts << endl;
    cout << "ultima pos tab simbolos " << cntrlts << endl;

  read.close();

  }else{
    cout << "we cannot open this file, sorry!" << endl;
  }
  cout << " reading completed" << endl;

    int j=0;
    for(j=0;j<=k-1;j++){
      cout << "linha "<< j <<": " << linha[j]   << endl;
      cout << "vai p tab? 1 local 2 global 3 extern 0 nao: " << vptab[j] << endl;
    }

    translate(nomeArquivo, nomeArquivoOut, codArq);
}

void translate(string nomeArquivo, string nomeArquivoOut, int codArq){




  cout << endl << " starting conversion... "<< endl;
  cout  << " lines: "<< k << endl;

  int l = 0;
  int j=0;


  for(j=0;j<=k-1;j++){
      
      if(vptab[j]!=0){    //se vai pra tabela de simbolos e n vai p arquivo

          if(linha[j]==2 && vptab[j]==2){     // se 2 linhas e vai p global

              cout << "linha "<< j <<" conversion not necessary! going to globals table" << linha[j] << endl;    
              conv[j]=0;  //conv == flag de conversão

          }
          else if(linha[j]==2 && vptab[j]==3){     // se 2 linhas e vai p extern

              cout << "linha "<< j <<" conversion not necessary! going to extern table" << linha[j] << endl;
              // aqui o numero da linha vai p tabela de simbolos
              // porém só vai pro arquivo a segunda e terceira palavras!      
              conv[j]=0;

          }  
          else if(linha[j]==3 && vptab[j]==1){     // se 3 linhas e space e vai pra local

              cout << "linha "<< j <<" conversion not necessary! going to locals table" << linha[j] << endl;
              // aqui o numero da linha vai p tabela de simbolos
              // porém só vai pro arquivo a segunda e terceira palavras!      
              conv[j]=0;

          } 
          else{

              cout << "line "<< j <<": conversion error. sorry :( " << linha[j] << endl;

          }
      }
      else{
          if(linha[j]!=3){    // se 1 ou 2, conversao sempre necessaria

              cout << "linha "<< j <<": required conversion! number of words: " << linha[j] << endl;  
              conv[j]=1;

          }
          else if(linha[j]==3 && loop[j]==1){     // se 3 linhas e a primeira é label de loop

              cout << "linha "<< j <<": !loop! required conversion! number of words: " << linha[j] << endl;
              // aqui o numero da linha vai p tabela de simbolos
              // porém só vai pro arquivo a segunda e terceira palavras!      
              conv[j]=1;

          }
      }
  }

  // as linhas que precisam de conversão são as que vptab é != 1 || 2 || 3
  // numero de palavras das linhas está em linha!

  passaproarquivo(nomeArquivo, nomeArquivoOut, codArq);
}

void passaproarquivo(string nomeArquivo, string nomeArquivoOut, int codArq){

  // le novamente o arquivo
  // transforma em assembly
  // passa as instruções para o txt
  ifstream read;
  std::string arq3 = nomeArquivo;
  const char *carq3 = arq3.c_str();

  std::string arq1 = nomeArquivoOut;
  const char *carq1 = arq1.c_str();

 cout << endl << "starting..." << endl;
  char palavra[512], *word, *word3, *word1, *word2;
  read.open(carq3);
  int h=0;
  int t = 0;
  ofstream write;
  write.open(carq1,std::ofstream::app);
  if(read.is_open()){
    while(!read.eof()){
        
        while(read.getline(palavra, 512) && h < qtdlinhas){
          cout << "h= "<< h << endl;
          cout << linha[h] << endl;
            if(linha[h]==3){
              cout << "entro aq" << endl;
              cout << palavra << endl;
              word = strtok( palavra , " " );
              cout << word << endl;
              word1 = strtok( NULL ," ");
              cout << word1 << endl;
              word2 = strtok( NULL , " " );
              cout << word2 << endl;
              // se word1 == space
              // word vai para table.operador
              // word 2 define quanto de increvento o controlador de table vai ter

              // se word1 == instrução
              // convert e passa pro arquivo
              if (strcmp(word1,"space")==0){  // nao escreve!
                cout << "space " << word << " vai p tabela ";
                table[cntrlts].operador = word; // operador recebe variavel
                cout << cntrlts <<endl;
                cntrlts++;
                cout << cntrlts <<endl;
              }
              else{ // escreve!
                // endereco de loop!!
                // if das instruções
                cout << "loop " << word << " vai p tabela ";
                table[cntrlts].operador = word; // operador recebe a 
                cout << "pc : "<< PC;
                table[cntrlts].operando = PC-2;
                cntrlts++;


                if(strcmp(word1,"in")==0){

                   // word 2 deve ser endereço da tabela de simbolos
                    for(t=0; t< cntrlts; t++){
                        char *temp = new char[table[t].operador.length() + 1];
                        memcpy(temp, table[t].operador.c_str(), table[t].operador.length() + 1);

                        if(strcmp(word2,temp) == 0){
                          write<<"10"<< " "<< t << endl;
                        }
                    }
                } 

                if(strcmp(word1,"out")==0){
                    for(t=0; t< cntrlts; t++){
                        char *temp = new char[table[t].operador.length() + 1];
                        memcpy(temp, table[t].operador.c_str(), table[t].operador.length() + 1);
                        
                        if(strcmp(word2,temp) == 0){
                          write<<"11"<< " "<< t << endl;
                        }
                    }
                }

                if(strcmp(word1,"add")==0){
                  write<<"01"<< " "<< word2 << endl;
                }
                if(strcmp(word1,"sub")==0){
                  write<<"02"<< " "<< word2 << endl;
                }
                if(strcmp(word1,"mul")==0){
                  write<<"03"<< " "<< word2 << endl;
                }
                if(strcmp(word1,"div")==0){
                  write<<"04"<< " "<< word2 << endl;
                }
                if(strcmp(word1,"store")==0){
                    for(t=0; t< cntrlts; t++){
                        char *temp = new char[table[t].operador.length() + 1];
                        memcpy(temp, table[t].operador.c_str(), table[t].operador.length() + 1);
                        
                        if(strcmp(word2,temp) == 0){
                          write<<"05"<< " "<< t << endl;
                        }
                    }
                }
                if(strcmp(word1,"jmp")==0){
                  write<<"06"<< " "<< table[cntrlts-1].operando << endl;
                }
                if(strcmp(word1,"jeq")==0){
                  write<<"07"<< " "<< table[cntrlts-1].operando << endl;
                }
                if(strcmp(word1,"jgt")==0){
                  write<<"08"<< " "<< table[cntrlts-1].operando << endl;
                }
                if(strcmp(word1,"jlt")==0){
                  write<<"09"<< " "<< table[cntrlts-1].operando << endl;
                }
                if(strcmp(word1,"push")==0){
                    for(t=0; t< cntrlts; t++){
                        char *temp = new char[table[t].operador.length() + 1];
                        memcpy(temp, table[t].operador.c_str(), table[t].operador.length() + 1);
                        
                        if(strcmp(word2,temp) == 0){
                          write<<"00"<< " "<< t << endl;
                        }
                    }
                } 
              } // fim else
            }// fim if
            else if(linha[h]==2){  // pc ++

              int gg,kk=0;
              cout << "entro aq 2" << endl;
              PC++;
              cout << palavra << endl;
              word1 = strtok( palavra , " " );
              cout << word1 << endl;
              word2 = strtok( NULL ," ");
              cout << word2 << endl;

              if (strcmp(word2,"global")==0){  // nao escreve!
                cout << "global " << word << " vai p tabela ";
                table[cntrlts].operador = word; // operador recebe variavel
                tableglobal[cntrltg].operador = word;
                cout << cntrlts <<endl;
                cntrlts++;
                cntrltg++;
                cout <<"ts "<< cntrlts <<endl;
                cout << "tg"<<cntrltg <<endl;
              }          
              if (strcmp(word2,"extern")==0){  // nao escreve!
                      //table[cntrlts].operador = word; // operador recebe variavel
                      cout << "É EXTEEEEEEEEEEEEEEEEEERN " << endl;
                        for(kk=250;kk < cntrltg; kk++){
                          cout <<"op"<< tableglobal[kk].operador <<endl;
                          if(tableglobal[kk].operador == word1){
                            cout << "extern " << word1 << " vai p tabela " << endl;
                            tableextern[cntrltx].operador = word1; // operador recebe variavel
                            cntrltx++;
                            cout << cntrltx <<endl;
                          }
                          else{
                            cout << "\n problem with extern variable! " << endl;
                            exit(1);
                          }

                        }
                      
                      
              } 
              // converte instrução
              // se a end a, se b end b, se c end c e etc
              if (strcmp(word1,"in")==0 || strcmp(word1,"out") == 0 || strcmp(word1,"add") == 0 || strcmp(word1,"sub") == 0 || 
                strcmp(word1,"mul") == 0 || strcmp(word1,"div") == 0 || strcmp(word1,"store") == 0 || 
                  strcmp(word1,"jeq") == 0 || strcmp(word1,"jmp") == 0 || strcmp(word1,"jgt") == 0 ||
                    strcmp(word1,"jlt") == 0 || strcmp(word1,"push") == 0 || strcmp(word1,"stop") == 0 ||
                      strcmp(word1,"a") != 0 || strcmp(word1,"b") != 0 || strcmp(word1,"c") != 0){
                      
                        cout << "instrução " << word1 <<  " operando "<< word2 <<" vai p arquivo " << endl;

                    if(strcmp(word1,"in")==0){
                        for(t=0; t< cntrlts; t++){
                          char *temp = new char[table[t].operador.length() + 1];
                          memcpy(temp, table[t].operador.c_str(), table[t].operador.length() + 1);

                          if(strcmp(word2,temp) == 0){
                            write<<"10"<< " "<< t << endl;
                          }
                        }
                    } 
                    if(strcmp(word1,"out")==0){
                        for(t=0; t< cntrlts; t++){
                          char *temp = new char[table[t].operador.length() + 1];
                          memcpy(temp, table[t].operador.c_str(), table[t].operador.length() + 1);

                          if(strcmp(word2,temp) == 0){
                            write<<"11"<< " "<< t << endl;
                          }
                        }
                    }
                    if(strcmp(word1,"add")==0){
                      write<<"01"<< " 0" << endl;
                    }
                    if(strcmp(word1,"sub")==0){
                      write<<"02"<< " 0" << endl;
                    }
                    if(strcmp(word1,"mul")==0){
                      write<<"03"<< " 0" << endl;
                    }
                    if(strcmp(word1,"div")==0){
                      write<<"04"<< " 0" << endl;
                    }
                    if(strcmp(word1,"store")==0){
                        for(t=0; t< cntrlts; t++){
                          char *temp = new char[table[t].operador.length() + 1];
                          memcpy(temp, table[t].operador.c_str(), table[t].operador.length() + 1);

                          if(strcmp(word2,temp) == 0){
                            write<<"05"<< " "<< t << endl;
                          }
                        }
                    }
                    if(strcmp(word1,"jmp")==0){
                      write<<"06"<< " "<< table[cntrlts-1].operando << endl;
                    }
                    if(strcmp(word1,"jeq")==0){
                      write<<"07"<< " "<< table[cntrlts-1].operando << endl;
                    }
                    if(strcmp(word1,"jgt")==0){
                      write<<"08"<< " "<< table[cntrlts-1].operando << endl;
                    }
                    if(strcmp(word1,"jlt")==0){
                      write<<"09"<< " "<< table[cntrlts-1].operando << endl;
                    }
                    if(strcmp(word1,"push")==0){
                        for(t=0; t< cntrlts; t++){
                          char *temp = new char[table[t].operador.length() + 1];
                          memcpy(temp, table[t].operador.c_str(), table[t].operador.length() + 1);

                          if(strcmp(word2,temp) == 0){
                            write<<"00"<< " "<< t << endl;
                          }
                        }
                    }
               }                         
            }
            else if(linha[h]==1){ // pc ++
              cout << "entro aq 3" << endl;
              PC++;
              cout << palavra << endl;
              word1 = strtok( palavra , " " );
              cout << word1 << endl;

              // converte instrucao e poe no arquivo
              if (strcmp(word1,"in")==0 || strcmp(word1,"out") == 0 || strcmp(word1,"add") == 0 || strcmp(word1,"sub") == 0 || 
                strcmp(word1,"mul") == 0 || strcmp(word1,"div") == 0 || strcmp(word1,"store") == 0 || 
                  strcmp(word1,"jeq") == 0 || strcmp(word1,"jmp") == 0 || strcmp(word1,"jgt") == 0 ||
                    strcmp(word1,"jlt") == 0 || strcmp(word1,"push") == 0 || strcmp(word1,"stop") == 0 ||
                      strcmp(word1,"a") == 0 || strcmp(word1,"b") == 0 || strcmp(word1,"c") == 0)
                  cout << "instrução " << word1 << " operando "<< word2 <<" vai p arquivo ";

              if(strcmp(word1,"add")==0){
                write<<"01"<< " 0" << endl;
              }
              if(strcmp(word1,"sub")==0){
                write<<"02"<< " 0" << endl;
              }
              if(strcmp(word1,"mul")==0){
                write<<"03"<< " 0" << endl;
              }
              if(strcmp(word1,"div")==0){
                write<<"04"<< " 0" << endl;
              }
              if(strcmp(word1,"stop")==0){
                write<<"12"<< " 0" << endl;
              }
            }
            else{
              cout << "error" << endl;
            }
            h++;
        }

    }
  }
  else{
    cout << "we cannot open this file, sorry!" << endl;
  }
  read.close();
  write.close();

}