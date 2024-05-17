#include <stdlib.h>
#include "../include/biblioteca.h"

Biblioteca *crear_biblioteca() {
    Biblioteca *biblioteca = (Biblioteca *)malloc(sizeof(Biblioteca));
    if (biblioteca == NULL) {
        return NULL;
    }

    biblioteca->lslibros = NULL;
    biblioteca->cantiLibros = 0;

    return biblioteca;
}

void agregar_libro(Biblioteca *biblioteca, Libro *libro) {
    biblioteca->cantiLibros++;
    biblioteca->lslibros = (Libro **)realloc(biblioteca->lslibros, biblioteca->cantiLibros * sizeof(Libro *));
    if (biblioteca->lslibros == NULL) {
        // Manejo de error, por ejemplo, liberar recursos y devolver error.
        return;
    }
    biblioteca->lslibros[biblioteca->cantiLibros - 1] = libro;
}

void destruir_biblioteca(Biblioteca *biblioteca) {
    for (int i = 0; i < biblioteca->cantiLibros; i++) {
        destruir_libro(biblioteca->lslibros[i]);
    }
    free(biblioteca->lslibros);
    free(biblioteca);
}
