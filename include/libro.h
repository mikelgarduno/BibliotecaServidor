#ifndef LIBRO_H
#define LIBRO_H
#include "autor.h"
#include "editorial.h"
#include "categoria.h"

typedef struct{
    char  *isbn;
	char *titulo;
	char *fechaCreacion;
    int autor;
    int editorial;
    int categoria;
    char* contenido;
}Libro;

Libro *crear_libro(char* isbn ,const char *titulo, int autor, int editorial, int categoria, char* contenido, char* fechaCreacion);
void destruir_libro(Libro *libro);
void imprimir_libro(Libro *libro);
#endif