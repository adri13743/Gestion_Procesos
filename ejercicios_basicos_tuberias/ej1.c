#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
//EJ 1
//Adian Rubio Henandez y Saül Cervera Ferrer

int t1[2],t2[2];
int main(int argc,char *argv[])
{
if (argc < 3){
	printf("Faltan argumentos");
	exit(-1);
}
if (argc > 3){
	printf("Soban argumentos");
	exit(-1);
}
pipe(t2);
if(fork() != 0){//Abuelo ejecuta wc
	wait(NULL);
	close(0);
	dup(t2[0]);
	close(t2[0]);
	close(t2[1]);
	close(1);
	open(argv[2],O_WRONLY|O_CREAT|O_APPEND,0600);
	execlp("wc","wc","-l",NULL);
	perror("Error en ejecutar la función WC");
	exit(-1);
} else	{
	pipe(t1);
	if(fork() != 0){//padre ejecuta grep 
	wait(NULL);
	close(0);
	dup(t1[0]);
	close(t1[0]);
	close(t1[1]);
	close(1);
	dup(t2[1]);
	close(t2[0]);
	close(t2[1]);
	execlp("grep","grep","a",NULL);
	perror("Error en ejecutar la función grep");
	exit(-1);
	} else	{ // hijo ejecuta cat
		close(t2[1]);
		close(t2[0]);
		close(1);
		dup(t1[1]);
		close(t1[1]);
		close(t1[0]);
		execlp("cat","cat",argv[1],NULL);
		perror("Error en ejecutar la función cat");
		exit(-1);
		}
 exit(0);
}
}
