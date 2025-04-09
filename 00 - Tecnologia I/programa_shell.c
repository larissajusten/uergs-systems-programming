#include<unistd.h>
#include<stdio.h>

int main(int argc, char *argv, char *envp){
char nome [20] ;
int i, j, pid, k;

for(i=0; i<3; i++) {
    printf(">>");
    scanf ("%s", nome ) ;
    pid = fork() ;
    if (pid != 0) {
       printf("Eu sou o pai, meu pid e: %d\n", getpid()) ;
       printf("Eu sou o pai, e vou dormir!!\n") ;
       sleep(5) ;
       pid = wait (0) ;
       printf("pid - retorno do wait: %d\n", pid) ;    
       } 
    else {
       printf("Eu sou o filho!!\n") ;
       printf("Eu sou o filho, meu pid e: %d\n", getpid()) ;
       printf("Vou executar o comando %s\n", nome) ;
       execve (nome, argv, envp);
       printf("Testando retorno exec\n");
       }
    }
   
}
