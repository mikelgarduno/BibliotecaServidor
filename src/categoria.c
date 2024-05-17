#include "../include/categoria.h"
#include <stdlib.h>
#include <string.h>

Categoria* crearCategoria(const char *nombre) {
    Categoria *categoria = (Categoria*)malloc(sizeof(Categoria));
    if (categoria == NULL) {
        return NULL; // Error: no se pudo asignar memoria
    }
    categoria->name = strdup(nombre); // Copiar el nombre de la categoría
    if (categoria->name == NULL) {
        free(categoria); // Liberar la memoria asignada previamente
        return NULL; // Error: no se pudo asignar memoria
    }
    return categoria;
}

void destruirCategoria(Categoria *categoria) {
    if (categoria != NULL) {
        free(categoria->name); // Liberar la memoria para el nombre de la categoría
        free(categoria); // Liberar la memoria para la estructura de categoría
    }
}

void imprimirCategoria(Categoria *categoria) {
        printf("Categoria: %s\n", categoria->name);
    
}
