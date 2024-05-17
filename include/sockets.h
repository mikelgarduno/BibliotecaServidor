/*
 * sockets.h
 *
 *  Created on: 17 may 2024
 *      Author: mikel
 */

#ifndef SOCKETS_H_
#define SOCKETS_H_

#include "../include/autor.h"
#include "../include/categoria.h"
#include "../include/editorial.h"
#include "../include/libro.h"

void empezarConexion();
void cerrarConexion();
void enviarBiblioteca();
void enviarRespuestaRegistro();
void enviarRespuestaLibroBorrado();



#endif /* SOCKETS_H_ */
