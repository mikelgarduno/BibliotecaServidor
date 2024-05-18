
#ifndef SOCKETS_H_
#define SOCKETS_H_

#include "../include/autor.h"
#include "../include/categoria.h"
#include "../include/editorial.h"
#include "../include/libro.h"
#include <winsock2.h>
#include <winsock.h>

SOCKET empezarConexion();
void cerrarConexion(SOCKET socket);

void mandarLista(SOCKET socket, char *lista, int tamanoLista);  
void mandarRespuesta(SOCKET socket, int respuesta);


#endif /* SOCKETS_H_ */
