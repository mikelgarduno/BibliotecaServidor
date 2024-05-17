#ifndef SQL_MANAGER_H
#define SQL_MANAGER_H

#include "sqlite3.h"
#include "../include/autor.h"
#include "../include/categoria.h"
#include "../include/editorial.h"
#include "../include/libro.h"


sqlite3* abrirDB();
void cerrarDB(sqlite3 *db);

void insertarAutor(Autor objAutor);
void insertarCategoria(Categoria objCategoria);
void insertarEditorial(Editorial objEditorial);
void insertarLibro(Libro objLibro);

int comprobarCategoriaNoExiste(char *nombre);
int comprobarCategoriaNoExiste(char *nombre);
int comprobarAutorNoExiste(char *nombre);
int comprobarLibroExistente(char *isbn);

Categoria obtenerCategorias();

void mostrarAutores();
int seleccionarAutor();
int seleccionarCategoria();
int seleccionarEditorial();

void buscarLibroPorTitulo(char *titulo);
void buscarLibroPorCategoria();
void buscarLibroPorEditorial();
#endif
