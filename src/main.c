// Servidor Local in C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/sqlManager.h"
#include "../include/sockets.h"
#include "../include/autor.h"
#include "../include/categoria.h"

int main(void) {
   sqlite3* baseDeDatos = abrirDB();
   char * lista = obtenerLibros(baseDeDatos);
   for(int i = 0; i < strlen(lista); i++) {
      printf("%c", lista[i]);
   }
   fflush(stdout);
   cerrarDB(baseDeDatos);
   return 0;
}
