// Servidor Local in C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/sqlManager.h"
#include "../include/sockets.h"
#include "../include/autor.h"

int main(void) {
   sqlite3* baseDeDatos = abrirDB();
   Autor* autor = crear_autor("Mikel Lertxundi","2004","Barakaldo");
   imprimir_autor(*autor);
   Autor* autor2 = crear_autor("Marisa Surgent","2018","Pontevedra");
   imprimir_autor(*autor2);
   insertarAutor(*autor,baseDeDatos);
   insertarAutor(*autor2,baseDeDatos);
   cerrarDB(baseDeDatos);
   return 0;
}
