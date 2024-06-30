#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
int sangria = 0;
int repeticiones = 0;
//EJ 5
//Adian Rubio Henandez y Saül Cervera Ferrer

void busqueda(char *arg, char *nombre){
char *fichero;
struct dirent *dp;
struct stat datos;
DIR *dir2;
dir2=opendir(arg);
struct stat datos3;
while((dp = readdir(dir2)) != NULL){
	fichero = malloc(strlen(arg)+strlen(dp->d_name)+2);
	sprintf(fichero,"%s/%s",arg,dp->d_name);
	stat(fichero,&datos);
	stat(nombre,&datos3);
	if(strcmp(dp->d_name,"..") != 0 && strcmp(dp->d_name,".") != 0){
	if(S_ISDIR(datos.st_mode)){
		sangria++;
		busqueda(fichero,nombre);
		sangria--;
		}else{
			if(S_ISREG(datos.st_mode) && datos.st_ino == datos3.st_ino){
			printf("(%ld) %s \n",datos.st_ino,fichero);
			repeticiones++;
			}
		}
	if((stat(fichero,&datos))!=0){
		perror("stat");
		exit(-1);
		}
	}
}
if(sangria==0){
printf("Total number of hard links: %d\n",repeticiones);
}
free(fichero);
closedir(dir2);
}

int main(int argc,char *argv[])
{
if (argc < 3){
	printf("Faltan argumentos");
	exit(-1);
}
if (argc > 3){
	printf("Sobran argumentos");
	exit(-1);
}
DIR *dir;
struct stat datos2;
if((dir=opendir(argv[1])) == NULL){
	stat(argv[1],&datos2);
	if((S_ISREG(datos2.st_mode)) || (S_ISLNK(datos2.st_mode))){
	perror("Nombre exixtente como fichero regular o enlace simbolico");
	exit(-1);
	}
	perror("directorio no encontrado");
	exit(-1);
}
int fich;
struct stat datoss;
if(stat(argv[2],&datoss)==-1){
printf("Erro al encontrar el fichero");
	exit(-1);
}
printf("Inode of file %s: %ld\n",argv[2],datoss.st_ino);
closedir(dir);
busqueda(argv[1],argv[2]);
exit(0); 
}
