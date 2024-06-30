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
//EJ 4
//Adian Rubio Henandez y Saül Cervera Ferrer

void imprimir(char *arg){
char *fichero;
struct dirent *dp;
struct stat datos;
DIR *dir2;
dir2=opendir(arg);
for (int x = 0;x<sangria;x++){
	printf("\t");
	}
if(sangria >0){printf("Directory %s:\n",arg);}
while((dp = readdir(dir2)) != NULL){
	fichero = malloc(strlen(arg)+strlen(dp->d_name)+2);
	sprintf(fichero,"%s/%s",arg,dp->d_name);
	stat(fichero,&datos);
	if(strcmp(dp->d_name,"..") != 0 && strcmp(dp->d_name,".") != 0){
	if(S_ISDIR(datos.st_mode)){
		sangria++;
		imprimir(fichero);
		sangria--;
		}else{
		for (int x = 0;x<sangria;x++){
		printf("\t");
		}
		if(sangria >0){printf("    ");}
		printf("%s \n",fichero);}
	if((stat(fichero,&datos))!=0){
		perror("stat");
		exit(-1);
		}
	}
}
free(fichero);
closedir(dir2);
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
printf("Tree of directory %s:\n",argv[1]);
closedir(dir);
imprimir(argv[1]);

exit(0); 
}
