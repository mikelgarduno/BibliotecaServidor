// Servidor Local in C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/sqlManager.h"
#include "../include/sockets.h"
#include "../include/autor.h"
#include "../include/categoria.h"
#include "../include/gestorDeArchivos.h"

int main(void) {
   sqlite3* baseDeDatos = abrirDB();
   cerrarDB(baseDeDatos);
   return 0;
}
