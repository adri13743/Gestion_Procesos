#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
//EJ 3 
//Adian Rubio Henandez y Saül Cervera Ferrer

int main(int argc,char *argv[])
{
int t1[2],t2[2],t3[2],t4[2],fd,fd2;
char dato;
if (argc < 4){
	printf("Faltan argumentos");
	exit(-1);
}
if (argc > 4){
	printf("Soban argumentos");
	exit(-1);
}

pipe(t4);
if(fork() != 0){//bisabuelo
	wait(NULL);
	fd2 = open(argv[3],O_WRONLY|O_CREAT|O_APPEND,07000);
	close(t4[1]);
	printf("\n WC output: \n");
	while (read(t4[0],&dato,sizeof(dato))>0){
	write(1,&dato,sizeof(dato));
	write(fd2, &dato,sizeof(dato));
	}
	close(t4[0]);
	close(fd2);
	exit(0);
} else	{	
	pipe(t3);
	if(fork() != 0){//abuelo
	wait(NULL);
	close(0);
	dup(t3[0]);
	close(t3[0]);
	close(t3[1]);
	close(1);
	dup(t4[1]);
	close(t4[1]);
	close(t4[0]);
	execlp("wc","wc","-l",NULL);
	perror("Error en ejecutar la función WC");
	exit(-1);
} else	{
	pipe(t2);
	if(fork() != 0){//padre  
	wait(NULL);
	close(0);
	dup(t2[0]);
	close(t2[0]);
	close(t2[1]);
	close(1);
	dup(t3[1]);
	close(t3[0]);
	close(t3[1]);
	close(t4[1]);
	close(t4[0]);
	execlp("grep","grep","^d",NULL);
	perror("Error en ejecutar la función grep");
	exit(-1);
	
}else{
	pipe(t1);
	if(fork() != 0){//hijo
	wait(NULL);
	close(t4[1]);
	close(t4[0]);
	close(t3[1]);
	close(t3[0]);
	close(t1[1]);
	close(t2[0]);
	fd = open(argv[3],O_WRONLY|O_CREAT|O_TRUNC,07000);
	printf("ls output: \n");
	while (read(t1[0],&dato,sizeof(dato))>0){
	write(1,&dato,sizeof(dato));
	write (t2[1],&dato,sizeof(dato));
	write (fd, &dato,sizeof(dato));
	}
	close(t2[1]);
	close(t1[0]);
	close(fd);
	exit(0);
}else{//nieto 
	close(1);
	dup(t1[1]);
	close(t1[0]);
	close(t4[1]);
	close(t4[0]);
	close(t3[1]);
	close(t3[0]);
	close(t2[1]);
	close(t2[0]);
	close(2);
	open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,07000);
	execlp("ls","ls","-al",argv[1],NULL);
	perror("Error en ejecutar la función ls argv[1]");
	exit(-1);
	}
	}
	}
	}
	exit(0);
}











