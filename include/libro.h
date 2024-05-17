#ifndef LIBRO_H
#define LIBRO_H
#include "autor.h"
#include "editorial.h"
#include "categoria.h"

typedef struct{
    char  *isbn;
	char *titulo;
	char *fechaCreacion;
    Autor *autor;
    Editorial *editorial;
    Categoria *categoria;
    char* contenido;
}Libro;

Libro *crear_libro(char* isbn ,const char *titulo, Autor *autor, Editorial *editorial, Categoria *categoria, char* contenido, char* fechaCreacion);
void destruir_libro(Libro *libro);
#endif