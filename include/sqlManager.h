#ifndef SQL_MANAGER_H
#define SQL_MANAGER_H

#include "sqlite3.h"
#include "../include/autor.h"
#include "../include/categoria.h"
#include "../include/editorial.h"
#include "../include/libro.h"


sqlite3* abrirDB();
void cerrarDB(sqlite3 *db);

int insertarAutor(Autor objAutor);
int insertarCategoria(Categoria objCategoria);
int insertarEditorial(Editorial objEditorial);
int insertarLibro(Libro objLibro);

int borrarLibro(int id);

int comprobarCategoriaNoExiste(char *nombre);
int comprobarEditorialNoExiste(char *nombre);
int comprobarAutorNoExiste(char *nombre);

Categoria* obtenerCategorias();
Editorial* obtenerEditoriales();
Autor* obtenerAutores();
Libro* obtenerLibros();

#endif
