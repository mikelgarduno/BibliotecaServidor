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
    Categoria* categoria = crearCategoria("Terror");
    Categoria* categoria2 = crearCategoria("Aventura");
    insertarCategoria(*categoria,baseDeDatos);
    insertarCategoria(*categoria2,baseDeDatos);


   cerrarDB(baseDeDatos);
   return 0;
}
