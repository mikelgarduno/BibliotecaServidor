#include <stdlib.h>
#include "../include/libro.h"

Libro *crear_libro(char* isbn ,const char *titulo, int autor, int editorial, int categoria, char* contenido, char* fechaCreacion) {
    Libro *libro = (Libro *)malloc(sizeof(Libro));
    if (libro == NULL) {
        return NULL;
    }

    libro->titulo = strdup(titulo);
    libro->autor = autor;
    libro->editorial = editorial;
    libro->fechaCreacion = fechaCreacion;
    libro->categoria = categoria;
    libro->contenido = contenido;
    libro->isbn = isbn;


    return libro;
}

void destruir_libro(Libro *libro) {
    free(libro->titulo);
    free(libro);
}

void imprimir_libro(Libro *libro){
    printf("%s; %s; %d; %d; %d; %s; %s\n", libro->isbn, libro->titulo, libro->autor, libro->editorial, libro->categoria, libro->contenido, libro->fechaCreacion);
}