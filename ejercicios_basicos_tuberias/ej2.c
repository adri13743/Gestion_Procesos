#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
//EJ 2 
//Adian Rubio Henandez y Saül Cervera Ferrer

int main(int argc,char *argv[])
{
int t1[2],t2[2],t3[2],fd,n;
char dato[1];
char dato2;
char cd;

n = 1;
dato2 = 1;
if (argc < 2){
	printf("Faltan argumentos");
	exit(-1);
}
if (argc > 2){
	printf("Sobran argumentos");
	exit(-1);
}

fd = open(argv[1],0);
pipe(t1);
pipe(t2);
pipe(t3);
write(t3[1],&dato2,1);
if (fork()==0){//P1
close(t2[1]);
close(t2[0]);
close(t3[1]);
close(t1[0]);
while (n && (read(t3[0],&dato2,1)>0)){
	n = read(fd,&dato,sizeof(dato));
	if(n != 0){
	printf("P1: ");
	printf("%s",dato);
	cd = *dato;
	while(n!= 0 && cd != '\n'){
	n = read(fd,&dato,sizeof(dato));
	cd = *dato;
	printf("%s",dato);
	}
	}
	write(t1[1],&dato2,sizeof(dato2));
	}
close(t1[1]);
close(t3[0]);
exit(0);
}


if(fork()==0){//P2
close(t3[1]);
close(t3[0]);
close(t1[1]);
close(t2[0]);
while (n  && read(t1[0],&dato2,1)>0){
	n = read(fd,&dato,sizeof(dato));
	if(n != 0){
	printf("P2: ");
	printf("%s",dato);
	cd = *dato;
	while(n!= 0 && cd != '\n'){
	n = read(fd,&dato,sizeof(dato));
	cd = *dato;
	printf("%s",dato);
	}
	}
	write(t2[1],&dato2,sizeof(dato2));
	}
close(t2[1]);
close(t1[0]);
exit(0);
}


if(fork()==0){//P3
close(t1[1]);
close(t1[0]);
close(t2[1]);
close(t3[0]);
while (n && read(t2[0],&dato2,1)>0){
	n = read(fd,&dato,sizeof(dato));
	if(n != 0){
	printf("P3: ");
	printf("%s",dato);
	cd = *dato;
	while(n!= 0 && cd != '\n'){
	n = read(fd,&dato,sizeof(dato));
	cd = *dato;
	printf("%s",dato);
	}
	}
	write(t3[1],&dato2,sizeof(dato2));
	}
close(t3[1]);
close(t2[0]);
exit(0);
}
	
close(t1[0]);
close(t1[1]);
close(t2[0]);
close(t2[1]);
close(t3[0]);
close(t3[1]);
wait(NULL);
wait(NULL);
wait(NULL);
wait(NULL);
exit(0);
}











