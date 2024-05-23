#include "../include/categoria.h"
#include <stdlib.h>
#include <string.h>

Categoria* crearCategoria(char *nombre) {
    Categoria *categoria = (Categoria*)malloc(sizeof(Categoria));
    if (categoria == NULL) {
        return NULL; 
    }
    categoria->name = strdup(nombre); 
    if (categoria->name == NULL) {
        free(categoria); 
        return NULL; 
    }
    return categoria;
}

void destruirCategoria(Categoria *categoria) {
    if (categoria != NULL) {
        free(categoria->name);
        free(categoria); 
    }
}

void imprimirCategoria(Categoria *categoria) {
        printf("Categoria: %s\n", categoria->name);
    
}
