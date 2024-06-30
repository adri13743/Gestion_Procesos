#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>
//EJ 2
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
if(lstat(argv[1],&datos)==0){
	printf("LINK: %s\n",argv[1]);
}else{
	printf("Erro al ejecutar la funcion lstat()");
	exit(-1);
}
printf("PERMISSIONS: %d\n",datos.st_mode & 777);
printf("HARD LINKS: %ld\n",datos.st_nlink);
printf("SIZE: %ld\n",datos.st_size);
fecha = localtime(&(datos.st_mtime));
printf("INODE: %ld\n",datos.st_ino);
printf("LAST ACCESS: %d/%d/%d\n",fecha->tm_mday,fecha->tm_mon+1,fecha->tm_year+1900);
char *s;
s = malloc(datos.st_size +1);
readlink(argv[1],s,datos.st_size);
s[datos.st_size]='\0';
if(stat(argv[1],&datos)==0){
	printf("FILE WHERE %s LINKS: %s\n",argv[1],s);
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


//A) Son los mismos ya que el programa que relaizamos primero imprime los datos del enlaze simbolico entornces coinciden por eso.
//B) Por que es el enlace que apunta al registro del sistema de archivos donde se encuentran los datos.
//C) Si se complentan y coinciden por que tanto los enlaces duros como los enlaces originales ofrecen la misma funcionalidad.





















