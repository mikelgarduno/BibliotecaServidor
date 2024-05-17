/*
 * sockets.c
 *
 *  Created on: 17 may 2024
 *      Author: mikel
 */
#include <stdio.h>
#include "../include/autor.h"
#include "../include/categoria.h"
#include "../include/editorial.h"
#include "../include/libro.h"

/// @brief 
//Empieza la conexión con el usuario y le envía la biblioteca
void empezarConexion(){
printf("Empezar conexion\n");
fflush(stdout);
printf("Esperando conexion\n");
fflush(stdout);
printf("Conexion establecida\n");
fflush(stdout);

}
/// @brief 
//Cierra la conexión con el usuario
void cerrarConexion(){
printf("Conexion cerrada\n");
fflush(stdout);
}

void enviarBiblioteca(){
	printf("Enviando Biblioteca\n");
	fflush(stdout);
	printf("Biblioteca Enviada\n");
	fflush(stdout);
}

void enviarRespuestaRegistro(int respuesta){
if(respuesta==1){
printf("Registro correcto\n");
fflush(stdout);
}else{
printf("Registro incorrecto, ya existe en la BD\n");
fflush(stdout);
}
}

void enviarRespuestaLibroBorrado(){
printf("Libro borrado correctamente\n");
fflush(stdout);
}

