#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
//EJ 6
//Adian Rubio Henandez y Saül Cervera Ferrer

int t1[2],t2[2];
int main(int argc,char *argv[])
{
if (argc < 2){
	printf("Faltan argumentos");
	exit(-1);
}
if (argc > 2){
	printf("Soban argumentos");
	exit(-1);
}
DIR *dir2;
if((dir2=opendir(argv[1])) == NULL){
	perror("directorio no encontrado");
	exit(-1);
}
struct dirent *dp;
struct stat datos;
char *fichero;
while((dp = readdir(dir2)) != NULL){
	fichero = malloc(strlen(argv[1])+strlen(dp->d_name)+2);
	sprintf(fichero,"%s/%s",argv[1],dp->d_name);
	stat(fichero,&datos);
	if(strcmp(dp->d_name,"..") != 0 && strcmp(dp->d_name,".") != 0 && S_ISDIR(datos.st_mode)){
pipe(t2);
if(fork() != 0){//Abuelo ejecuta wc
	wait(NULL);
	close(0);
	dup(t2[0]);
	close(t2[0]);
	close(t2[1]);
	write(1,"Files and directories of ",25);
	write(1,fichero,sizeof(fichero));
	write(1,": ",2);
	execlp("wc","wc","-l",NULL);
	perror("Error en ejecutar la función WC");
	exit(-1);
} else	{
	pipe(t1);
	if(fork() != 0){//padre ejecuta tail 
	wait(NULL);
	close(0);
	dup(t1[0]);
	close(t1[0]);
	close(t1[1]);
	close(1);
	dup(t2[1]);
	close(t2[0]);
	close(t2[1]);
	execlp("tail","tail","-n","+2",NULL);
	perror("Error en ejecutar la función tail");
	exit(-1);
	} else	{ // hijo ejecuta ls-l
		if(fork() != 0){
		close(t2[1]);
		close(t2[0]);
		close(1);
		dup(t1[1]);
		close(t1[1]);
		close(t1[0]);
		execlp("ls","ls","-l",fichero,NULL);
		perror("Error en ejecutar la función cat");
		exit(-1);
		}
		}
		}
}
}
 exit(0);
}
