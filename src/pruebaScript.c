#include <fcntl.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void ejecutarScript(char* path, char* in, char* out);

int main(void) {
	int n;
	const char* out = "fileOut.txt"; //GUARDA LO QUE EL SCRIPT TIRA POR STDOUT ACA
	const char* in = "fileIn.txt";   // EL SCRIPT TOMA STDIN DE ACA
	const char* path = "Nuevo.sh";   // ESTE ES EL SCRIPT
	ejecutarScript(path,in,out);
	printf("Ingresa un numero para probar stdin:\n");
	scanf("%d",&n);
	printf("me escribiste %d\n",n);
}


//redirecciona STDOUT a out y STDIN a in y ejecuta el script,
// cuando termina vuelve STDOUT y STDIN a la normalidad
void ejecutarScript(char* path, char* in, char* out) {
	char* command = (char*) malloc(strlen(path) + 3);
	strcpy(command, "sh ");
	strcat(command, path);
	int bako, newo, baki, newi;
	fflush(stdout);
	//fflush(stdin);
	__fpurge(stdin);
	bako = dup(fileno(stdout)); //
	baki = dup(fileno(stdin));  //
	newo = open(out, O_WRONLY | O_APPEND);
	newi = open(in, O_RDONLY); //  		esto me cambia los stdin y stdout originales por mis arhcivos
	dup2(newo, fileno(stdout)); //
	dup2(newi, fileno(stdin));  //
	close(newo);  				//
	close(newi);  				//
	system(command);            // -> aca va mi codigo
	fflush(stdout);             //
	//fflush(stdin);
	__fpurge(stdin);//
	dup2(bako, fileno(stdout)); //
	dup2(baki, fileno(stdin)); //  		esto me cambia los stdin y stdout de nuevo a los originales
	close(bako);                //
	close(baki);
}
