#ifndef SQL_MANAGER_H
#define SQL_MANAGER_H

#include "sqlite3.h"
#include "../include/autor.h"
#include "../include/categoria.h"
#include "../include/editorial.h"
#include "../include/libro.h"


sqlite3* abrirDB();
void cerrarDB(sqlite3 *db);

int insertarAutor(Autor objAutor, sqlite3* db);
int insertarCategoria(Categoria objCategoria, sqlite3* db);
int insertarEditorial(Editorial objEditorial, sqlite3* db);
int insertarLibro(Libro objLibro, sqlite3* db);

int borrarLibro(int id, sqlite3* db);

int comprobarCategoriaNoExiste(char *nombre, sqlite3* db);
int comprobarEditorialNoExiste(char *nombre, sqlite3* db);
int comprobarAutorNoExiste(char *nombre, sqlite3* db);

char** obtenerCategorias( sqlite3* db);
char** obtenerEditoriales( sqlite3* db);
char** obtenerAutores( sqlite3* db);
char** obtenerLibros( sqlite3* db);

void ejecutarSQL(char *sql, sqlite3* db);

#endif
