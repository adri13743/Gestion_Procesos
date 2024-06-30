#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
//EJ 1
//Adian Rubio Henandez y Saül Cervera Ferrer

int main(int argc,char *argv[])
{
if (argc < 2){
	printf("Faltan argumentos");
	exit(-1);
}
if (argc > 2){
	printf("Sobran argumentos");
	exit(-1);
}
struct stat datos;
struct tm *fecha;
char tipo;
char *fichero;

if(stat(argv[1],&datos)==0){
	printf("%s\n",argv[1]);
	switch(datos.st_mode & S_IFMT)
	{
	case S_IFREG:
	printf("TYPE: Regular File\n");
	case S_IFDIR:
	printf("TYPE: Directory\n");
	break;
	}
}else{
	printf("Erro al ejecutar la funcion stat()");
	exit(-1);
}
printf("PERMISSIONS: %d\n",datos.st_mode & 777);
printf("HARD LINKS: %ld\n",datos.st_nlink);
printf("SIZE: %ld\n",datos.st_size);
fecha = localtime(&(datos.st_mtime));
printf("INODE: %ld\n",datos.st_ino);
printf("LAST ACCESS: %d/%d/%d\n",fecha->tm_mday,fecha->tm_mon+1,fecha->tm_year+1900);
exit(0); 
}
