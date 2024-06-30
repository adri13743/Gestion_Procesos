#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>


//EJ 3
//Adian Rubio Henandez y Saül Cervera Ferrer

void imprimir(char *arg){
char *fichero;
struct dirent *dp;
struct stat datos;
DIR *dir2;
dir2=opendir(arg);
printf("Contents of directory %s:\n",arg);
while((dp = readdir(dir2)) != NULL){
	fichero = malloc(strlen(arg)+strlen(dp->d_name)+2);
	sprintf(fichero,"%s/%s",arg,dp->d_name);
	stat(fichero,&datos);
	if(S_ISDIR(datos.st_mode)){
		printf("D ");
		}else{printf("R ");}
	if((stat(fichero,&datos))!=0){
		perror("stat");
		exit(-1);
		}
	printf("%s \n",fichero);
}
free(fichero);
closedir(dir2);
exit(0);
}



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
DIR *dir;
struct stat datos2;
if((dir=opendir(argv[1])) == NULL){
	stat(argv[1],&datos2);
	if((S_ISREG(datos2.st_mode)) || (S_ISLNK(datos2.st_mode))){
	perror("Nombre exixtente como fichero regular o enlace simbolico");
	exit(-1);
	}
	mkdir(argv[1],0755);
	exit(0);
}
closedir(dir);
imprimir(argv[1]);
closedir(dir);
exit(0); 
}
