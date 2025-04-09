#include <stdio.h>
#include <pthread.h>

pthread_t tid1,tid2;

int lock = 0, key = 1, ZERO = 0; 
int a = 0; 


 void  mutex_begin () {
  
  asm ("ocupado:") ;
  asm ("         mov key, %eax") ;  
  asm ("         xchg lock, %eax") ;// se lock == 1, eax recebe 1 e lock recebe 1;
  				    //se lock == 0, eax recebe 0 e lock recebe 1;
  asm("          cmp %eax, ZERO") ;
  asm("          jne ocupado") ; //loop se lock == 1; caso contrario entra na SC

  }


int mutex_end () {

  lock = 0 ; //libera a SC
  }


void * thread2(){

  int i, k, key;
  
  for(i=0; i<10000000; i++) 
     {
      mutex_begin () ;
       a = a + 5;
       mutex_end () ;
     }
}
void * thread1(){

  int i ;

  for (i=0; i<10000000; i++) 
    {
       mutex_begin () ;
       a = a + 2;
       mutex_end () ;
    }
}


int main(){
    
      printf("Inicio \n") ;
      pthread_create(&tid2, NULL, thread2, NULL) ;
      pthread_create(&tid1, NULL, thread1, NULL) ;
      pthread_join(tid1,NULL);
      pthread_join(tid2,NULL);
      printf("Valor de a: %d\n", a) ;
      }


