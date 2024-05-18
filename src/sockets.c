
#include <stdio.h>
#include "../include/autor.h"
#include "../include/categoria.h"
#include "../include/editorial.h"
#include "../include/libro.h"
#include <winsock.h>

//Inicia la conexión y gestiona los inputs del usuario
SOCKET empezarConexion(){
printf("Empezar conexion\n");
fflush(stdout);
}

//Cierra la conexión
void cerrarConexion(SOCKET socket){
printf("Cerrar conexion\n");
fflush(stdout);
}

//Manda una lista de libros, autores, categorias o editoriales
void mandarLista(SOCKET socket, char *lista, int tamanoLista){
printf("Mandar lista\n");
fflush(stdout);
}

//Manda una respuesta al cliente
void mandarRespuesta(SOCKET socket, int respuesta){
if(respuesta == 0){
	printf("Error en la apertura de la BD\n");
	fflush(stdout);
}else if(respuesta == 1){
	printf("Se ha registrado correctamente\n");
	fflush(stdout);
}else if(respuesta == 2){
	printf("Ya existia en la Base de Datos\n");
	fflush(stdout);
}else if(respuesta == 3){
	printf("Se ha borrado correctamente\n");
	fflush(stdout);
}else if(respuesta == 4){
	printf("Ese libro no se puede borrar\n");
	fflush(stdout);
}
}