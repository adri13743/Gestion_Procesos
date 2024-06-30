#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "queue.h"
int s,e,n,numero_act,q;
int turno_h = 0;
pthread_cond_t turno_api[100];
pthread_mutex_t mutex;

void *apilar(void *arg){
	int n_hilo;
	n_hilo =*(int *)arg;
	for(int i = s + n_hilo;i<=e;i=i+n)
	{
		pthread_mutex_lock(&mutex);
		while(n_hilo!=turno_h){
			pthread_cond_wait(&turno_api[n_hilo],&mutex);	
		}
		q_write(i);
		turno_h++;
		if(turno_h==n){
			turno_h=0;
		}
		pthread_cond_signal(&turno_api[turno_h]);
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(0);
}

int main(int argc,char *argv[]){
	if(argc!=4){
		printf("Faltan argumentos.\n");
		exit(-1);
	}
	n=atoi(argv[1]);
	s=atoi(argv[2]);
	e=atoi(argv[3]);
	int val;
	if((e-s)<n){
		printf("El numero de elementos que se escribiran en la cola es menor al numero de 			subprocesos que se crean.\n");
	exit(-1);
	}
	q_create((e-s)+1);
	int h_indice[n];
	pthread_t hilo[n];
	pthread_mutex_init(&mutex,NULL);
	for(int i=0;i<n;i++){
	pthread_cond_init(&turno_api[i],NULL);
	} 
	numero_act = s;
	for(int i = 0;i<n;i++){
		h_indice[i]=i;
		pthread_create(&hilo[i],NULL,apilar,(void *)&h_indice[i]);
	}
	for(int i = 0;i<n;i++){
		pthread_join(hilo[i],NULL);
	}
	for(int i=0;i<n;i++){
	pthread_cond_destroy(&turno_api[i]);
	} 
	for(int i = 0;i<(e-s)+1;i++){
		q_read(&val,i);
		printf("Leo de posicion %d del buffer: %d\n",i,val);
	}
	q_destroy();
	pthread_mutex_destroy(&mutex);
  	pthread_exit(0);
}
