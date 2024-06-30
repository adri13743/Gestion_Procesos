#include <pthread.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <wait.h>
#include <time.h>
#include <unistd.h>
#define NUM 10 //CANTIDAD HILOS

pthread_mutex_t mutex;
pthread_cond_t turno_a; 
pthread_cond_t turno_b;
pthread_cond_t turno_ab;
int ocupadoA=0;
int ocupadoB=0;
int ocupadoAB=0;

void *A(void *arg){
  int num=*(int *)arg;
  pthread_mutex_lock(&mutex);
    while(ocupadoA==1){ /* Si buffer lleno */
    pthread_cond_wait(&turno_a, &mutex);  
  }
  printf("Thread h1 number %d (id.%lu) accessing resource A\n",num,pthread_self());
  ocupadoA=1;
  pthread_mutex_unlock(&mutex);
  sleep(random ()% 3);
  pthread_mutex_lock(&mutex);
    printf("Thread h1 number %d (id.%lu) relesing resource A\n",num,pthread_self());
    ocupadoA=0;
    pthread_cond_signal(&turno_a);
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}
void *B(void *arg){
  int num=*(int *)arg;
  pthread_mutex_lock(&mutex);
  while(ocupadoB==1){ /* Si buffer lleno */
    pthread_cond_wait(&turno_b, &mutex);
    
  }
    printf("Thread h2 number %d (id.%lu) accessing resource B\n",num,pthread_self());
    ocupadoB=1;
    pthread_mutex_unlock(&mutex);
    sleep (random ()% 3);
    pthread_mutex_lock(&mutex);
    ocupadoB=0;
    printf("Thread h2 number %d (id.%lu) relesing resource B\n",num,pthread_self());
    pthread_cond_signal(&turno_b);
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}
void *AB(void *arg){
  int num=*(int *)arg;
     pthread_mutex_lock(&mutex);
  while(ocupadoA==1){ /* Si buffer lleno */
    pthread_cond_wait(&turno_a, &mutex);
}
  while(ocupadoB==1){
    pthread_cond_wait(&turno_b, &mutex);
}
    printf("Thread h3 number %d (id.%lu) accessing resource AB\n",num,pthread_self());
    ocupadoA=1;
    ocupadoB=1;
    pthread_mutex_unlock(&mutex);
    sleep (random ()% 3);
    pthread_mutex_lock(&mutex);
    ocupadoA=0;
    ocupadoB=0;
    printf("Thread h3 number %d (id.%lu) relesing resource AB\n",num,pthread_self());
    pthread_cond_signal(&turno_a);
    pthread_cond_signal(&turno_b);
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}

int main (){
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&turno_a, NULL);
    pthread_cond_init(&turno_b, NULL);
    pthread_cond_init(&turno_ab, NULL);
    int indice[NUM];
    int i=0 ;
    pthread_t hilosA[NUM];
    pthread_t hilosB[NUM];
    pthread_t hilosAB[NUM];
    
      for (i=0; i<NUM; i++){
      indice[i]=i;
      pthread_create(&hilosA[i], NULL, A, (void *)&indice[i]);
      pthread_create(&hilosAB[i], NULL, AB, (void *)&indice[i]);
      pthread_create(&hilosB[i], NULL, B, (void *)&indice[i]);
      }
      for (i=0; i<NUM; i++) {
      pthread_join(hilosA[i], NULL);
      }
      for (i=0; i<NUM; i++) {
      pthread_join(hilosB[i], NULL);
      }
      for (i=0; i<NUM; i++) {
      pthread_join(hilosAB[i], NULL);
      }
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&turno_a);
    pthread_cond_destroy(&turno_b);
    pthread_cond_destroy(&turno_ab);
    
    
    exit (0);
}


