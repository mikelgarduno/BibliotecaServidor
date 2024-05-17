#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H
#include "libro.h"
typedef struct{
    Libro **lslibros;
    int cantiLibros;
}Biblioteca;

Biblioteca *crear_biblioteca();
void agregar_libro(Biblioteca *biblioteca, Libro *libro);
void destruir_biblioteca(Biblioteca *biblioteca);

#endif // BIBLIOTECA_H