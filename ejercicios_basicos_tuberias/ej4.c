#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
//EJ 4 
//Adian Rubio Henandez y Saül Cervera Ferrer

int main( int argc, char *argv[]) { 
if(argc!=2){
	printf("Se espera un argumento.\n");
	exit(-1);
}
int t1[2],t2[2],t3[2],t4[2],numero,numero2 ,numero3,impar ,par ,suma,i;
int dato = atoi(argv[1]);
int vector1[dato];
int vector2[dato];
i = 0;
impar = 0;
par = 0;
suma = 0;
numero = 0;

pipe(t1);
pipe(t2);
pipe(t3);
pipe(t4);

if (fork()==0){//P1
  	close(t1[0]);
	close(t2[0]);
  	close(t3[0]); 
  	close(t3[1]);
  	close(t4[1]);
  	while(i<dato){ 
    	printf("Dame un numero: ");
    	scanf("%d",&numero);
    	if(numero%2==0){
	write(t1[1],&numero,sizeof(numero));
    	}else { 
	write(t2[1],&numero,sizeof(numero));
    	}
    	i = i + 1; 
  	}
    	close(t1[1]);
  	close(t2[1]);
  	while(read(t4[0],&numero,sizeof(numero))>0){
    	printf("P1: Suma de todos los numeros: %d\n",numero);
    	close(t4[0]);
  	}
  	close(t4[0]);
  	exit(0);
}

if (fork()==0){//P2
 	close(t1[1]);
      	close(t3[1]);
      	close(t4[0]);
      	while(read(t1[0],&numero2, sizeof(numero2))>0){
	    	par = par + numero2;
      	}
      	close(t1[0]);     
      	printf("P2: Suma de los numeros pares: %d\n",par);
      	close(t2[1]);
      	close(t2[0]);  
      	while(read(t3[0],&impar,sizeof(int))>0){
      	suma = par + impar;
      	close(t3[0]);
      	}
      	printf("P2: Suma de los numeros pares e impares: %d\n",suma);
      	write(t4[1],&suma,sizeof(int));
      	close(t3[0]);
      	close(t4[1]);
      	exit(0);
}

if (fork()==0){//P3
	  close(t1[0]);
	  close(t1[1]);
	  close(t2[1]);
	  close(t3[0]);
	  close(t4[0]);
	  close(t4[1]);
	  while(read(t2[0],&numero3,sizeof(numero))>0){
	    	impar = impar + numero3;
	  }  
	  close(t2[0]);
	  printf("P3: Suma de los numeros impares: %d\n",impar);
	  write(t3[1],&impar,sizeof(int));
	  close(t3[1]);
	  exit(0);
}
close(t1[0]);
close(t1[1]);
close(t2[0]);
close(t2[1]);
close(t3[0]); 
close(t3[1]);
close(t4[1]);
close(t4[0]);
wait(NULL);
wait(NULL);
wait(NULL);
exit(0);
}









