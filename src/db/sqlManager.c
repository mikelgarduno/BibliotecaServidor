#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../include/sqlManager.h"
#include "../../include/autor.h"
#include "../../include/libro.h"
#include "../../include/categoria.h"
#include "../../include/editorial.h"
#include "../../include/gestorDeArchivos.h"


sqlite3* abrirDB() {
	sqlite3 *db;
	int result = sqlite3_open("biblioteca.db", &db);
	if (result != SQLITE_OK) {
		printf("Error al abrir BD\n");
		return NULL;
	} else
		(printf("BD abierta\n"));
	return db;
}

void cerrarDB(sqlite3 *db) {
	int resultado = sqlite3_close(db);
	if (resultado != SQLITE_OK) {
		printf("No se pudo cerrar la base de datos, código de error: %d\n",
				resultado);
	} else {
		printf("BD cerrada correctamente.\n");
	}
}

void insertarAutor(Autor objAutor) {
	sqlite3 *db = abrirDB();
	int result;

	sqlite3_stmt *stmt;
	char sql[] =
			"INSERT INTO autor (nombre_a, fecha_ncto, lugar_ncto) VALUES (?, ?, ?)";

	result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement: %s\n", sqlite3_errmsg(db));
		guardarErrorEnLog("Error preparing statement");
		sqlite3_close(db);
		return;
	}

	sqlite3_bind_text(stmt, 1, objAutor.name, strlen(objAutor.name),
			SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, objAutor.date, strlen(objAutor.date),
			SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, objAutor.place, strlen(objAutor.place),
			SQLITE_STATIC);

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error insertando datos: %s\n", sqlite3_errmsg(db));
		fflush(stdout);
	} else {
		printf("Autor insertado correctamente\n");
		fflush(stdout);
	}
	sqlite3_finalize(stmt);
	cerrarDB(db);
}

void insertarCategoria(Categoria objCategoria) {
	sqlite3 *db = abrirDB();
	int result;

	sqlite3_stmt *stmt1;
	char sql[] = "INSERT INTO Categoria (nombre_c) VALUES (?)";

	result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt1, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement: %s\n", sqlite3_errmsg(db));
		fflush(stdout);
		sqlite3_close(db);
		return;
	}

	sqlite3_bind_text(stmt1, 1, objCategoria.name, strlen(objCategoria.name),
			SQLITE_STATIC);

	result = sqlite3_step(stmt1);
	if (result != SQLITE_DONE) {
		printf("Error insertando datos: %s\n", sqlite3_errmsg(db));
		fflush(stdout);
	} else {
		printf("Categoria insertada correctamente\n");
		fflush(stdout);
	}
	sqlite3_finalize(stmt1);
	cerrarDB(db);
}

void insertarEditorial(Editorial objEditorial) {
	sqlite3 *db = abrirDB();
	int result;

	sqlite3_stmt *stmt2;
	char sql[] = "INSERT INTO editorial (nombre_e, fecha_fund) VALUES (?, ?)";

	result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt2, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement: %s\n", sqlite3_errmsg(db));
		fflush(stdout);
		sqlite3_close(db);
		return;
	}

	sqlite3_bind_text(stmt2, 1, objEditorial.nombre,
			strlen(objEditorial.nombre), SQLITE_STATIC);
	sqlite3_bind_text(stmt2, 2, objEditorial.fecha, strlen(objEditorial.fecha),
			SQLITE_STATIC);

	result = sqlite3_step(stmt2);
	if (result != SQLITE_DONE) {
		printf("Error insertando datos: %s\n", sqlite3_errmsg(db));
		fflush(stdout);
	} else {
		printf("Editorial insertada correctamente\n");
		fflush(stdout);
	}

	sqlite3_finalize(stmt2);
	cerrarDB(db);
}

int comprobarCategoriaNoExiste(char *nombre) {
	sqlite3 *db = abrirDB();
	int result;

	sqlite3_stmt *stmt;
	const char *sql = "SELECT id_cat FROM Categoria WHERE nombre_c = ?";
	result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement: %s\n", sqlite3_errmsg(db));
		fflush(stdout);
		sqlite3_close(db);
		return;
	}

	sqlite3_bind_text(stmt, 1, nombre, strlen(nombre), SQLITE_STATIC);

	if (sqlite3_step(stmt) == SQLITE_ROW) {
		int id = sqlite3_column_int(stmt, 0);
		printf("La categoria %s ya existe con el ID %d\n", nombre, id);
		fflush(stdout);
		sqlite3_finalize(stmt);
		cerrarDB(db);
		return 0;
	} else {
		printf("La categoria %s no existe\n", nombre);
		fflush(stdout);
		sqlite3_finalize(stmt);
		cerrarDB(db);
		return 1;
	}

}

int comprobarEditorialNoExiste(char *nombre) {
	sqlite3 *db = abrirDB();
	int result;
	sqlite3_stmt *stmt;
	const char *sql = "SELECT id_edi FROM editorial WHERE nombre_e = ?";
	result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		fflush(stdout);
		sqlite3_close(db);
		return;
	}
	sqlite3_bind_text(stmt, 1, nombre, strlen(nombre), SQLITE_STATIC);
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		int id = sqlite3_column_int(stmt, 0);
		printf("La editorial %s ya existe con el ID %d\n", nombre, id);
		fflush(stdout);
		sqlite3_finalize(stmt);
		cerrarDB(db);
		return 0;
	} else {
		printf("La editorial %s no existe\n", nombre);
		fflush(stdout);
		sqlite3_finalize(stmt);
		cerrarDB(db);
		return 1;
	}
}

int comprobarAutorNoExiste(char *nombre) {
	sqlite3 *db = abrirDB();
	int result;
	sqlite3_stmt *stmt;
	const char *sql = "SELECT id_aut FROM autor WHERE nombre_a = ?";
	result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement: %s\n", sqlite3_errmsg(db));
		fflush(stdout);
		sqlite3_close(db);
		return;
	}
	sqlite3_bind_text(stmt, 1, nombre, strlen(nombre), SQLITE_STATIC);
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		int id = sqlite3_column_int(stmt, 0);
		printf("El autor %s ya existe con el ID %d\n", nombre, id);
		fflush(stdout);
		sqlite3_finalize(stmt);
		cerrarDB(db);
		return 0;
	} else {
		printf("El autor %s no existe\n", nombre);
		fflush(stdout);
		sqlite3_finalize(stmt);
		cerrarDB(db);
		return 1;
	}
}

int comprobarLibroExistente(char *isbn) {
	sqlite3 *db = abrirDB();
	int result;
	sqlite3_stmt *stmt;
	const char *sql = "SELECT isbn, nombre FROM libro WHERE isbn = ?";
	result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement: %s\n", sqlite3_errmsg(db));
		fflush(stdout);
		sqlite3_close(db);
		return;
	}
	sqlite3_bind_text(stmt, 1, isbn, strlen(isbn), SQLITE_STATIC);
	if (sqlite3_step(stmt) == SQLITE_ROW) {
		char *isbnResult = sqlite3_column_text(stmt, 0);
		char *nombreResult = sqlite3_column_text(stmt, 1);
		printf(
				"El libro con ISBN %s ya existe en la base de datos. Nombre: %s\n",
				isbnResult, nombreResult);
		return 1;
	} else {
		return 0;
	}
	sqlite3_finalize(stmt);
	cerrarDB(db);
}

int seleccionarAutor() {

	int result;
	sqlite3 *db = abrirDB();
	sqlite3_stmt *stmt;
	char sql[] = "SELECT id_aut, nombre_a, fecha_ncto, lugar_ncto  FROM autor";
	result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement: %s\n", sqlite3_errmsg(db));
		fflush(stdout);
		cerrarDB(db);
		return;
	}

	printf("Lista de autores:\n");
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		int id = sqlite3_column_int(stmt, 0);
		char *nombre = sqlite3_column_text(stmt, 1);
		char *fecha = sqlite3_column_text(stmt, 2);
		char *lugar = sqlite3_column_text(stmt, 3);
		printf("ID: %d, Nombre: %s, Lugar y Fecha de nacimiento: %s, %s\n", id, nombre,lugar,fecha);
		fflush(stdout);
	}

	sqlite3_finalize(stmt);
	cerrarDB(db);

	int ID;
	printf("Ingrese el ID del autor que desea seleccionar: ");
	fflush(stdout);
	scanf("%d", &ID);
return ID;
}

int seleccionarCategoria(){
sqlite3 *db = abrirDB();
	int result;

	sqlite3_stmt *stmt;
	const char *sql = "SELECT id_cat, nombre_c FROM Categoria";
	result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement: %s\n", sqlite3_errmsg(db));
		fflush(stdout);
		sqlite3_close(db);
		return;
	}

	printf("Lista de categorias:\n");
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		int id = sqlite3_column_int(stmt, 0);
		char *nombre = sqlite3_column_text(stmt, 1);
		printf("ID: %d, Nombre: %s\n", id, nombre);
		fflush(stdout);
	}

	sqlite3_finalize(stmt);
	cerrarDB(db);

	int ID;
	printf("Ingrese el ID de la categoria que desea seleccionar: ");
	fflush(stdout);
	scanf("%d", &ID);
return ID;
}

int seleccionarEditorial(){
sqlite3 *db = abrirDB();
	int result;

	sqlite3_stmt *stmt;
	const char *sql = "SELECT id_edi, nombre_e,fecha_fund FROM Editorial";
	result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement: %s\n", sqlite3_errmsg(db));
		fflush(stdout);
		cerrarDB(db);
		return;
	}

	printf("Lista de editoriales:\n");
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		int id = sqlite3_column_int(stmt, 0);
		char *nombre = sqlite3_column_text(stmt, 1);
		char *fecha = sqlite3_column_text(stmt, 2);
		printf("ID: %d, Nombre: %s, Fecha de fundacion: %s\n", id, nombre, fecha);
		fflush(stdout);
	}

	sqlite3_finalize(stmt);
	cerrarDB(db);

	int ID;
	printf("Ingrese el ID de la editorial que desea seleccionar: ");
	fflush(stdout);
	scanf("%d", &ID);
return ID;
}

void insertarLibro(Libro objLibro) {
	sqlite3 *db = abrirDB();
	int result;
	sqlite3_stmt *stmt;
	char sql[] =
			"INSERT INTO libro (isbn, titulo, id_aut, id_cat, id_edi) VALUES (?, ?, ?, ?, ?)";
	result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement: %s\n", sqlite3_errmsg(db));
		fflush(stdout);
		sqlite3_close(db);
		return;
	}

	sqlite3_bind_text(stmt, 1, objLibro.isbn, strlen(objLibro.isbn),
			SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, objLibro.titulo, strlen(objLibro.titulo),
			SQLITE_STATIC);
//	sqlite3_bind_int(stmt, 3, objLibro.autor->);
//	sqlite3_bind_int(stmt, 4, objLibro.id_cat);
//	sqlite3_bind_int(stmt, 5, objLibro.id_edi);

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error insertando datos: %s\n", sqlite3_errmsg(db));
		fflush(stdout);
	} else {
		printf("Libro insertada correctamente\n");
		fflush(stdout);
	}
	sqlite3_finalize(stmt);
	cerrarDB(db);
}

void buscarLibroPorTitulo(char *titulo) {
	// Abrir la base de datos
	sqlite3 *db = abrirDB();
	int result;
	// Preparar el statement SQL para buscar libros por título
	sqlite3_stmt *stmt;
	const char *sql = "SELECT id_libro, titulo FROM libro WHERE titulo LIKE ?";
	result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement: %s\n", sqlite3_errmsg(db));
		guardarErrorEnLog("Error preparing statement");
		sqlite3_close(db);
		return;
	}
	// Vincular el valor del título al marcador de posición
	result = sqlite3_bind_text(stmt, 1, titulo, strlen(titulo), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameter: %s\n", sqlite3_errmsg(db));
		guardarErrorEnLog("Error binding parameter");
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return;
	}
	// Ejecutar la consulta y recuperar los títulos de los libros
	printf("Lista de libros con título similar a '%s':\n", titulo);
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		int bookId = sqlite3_column_int(stmt, 0);
		const unsigned char *bookTitle = sqlite3_column_text(stmt, 1);
		printf("Código: %d, Título: %s\n", bookId, bookTitle);
	}

	// Clean up
	sqlite3_finalize(stmt);

	// Prompt el usuario para ingresar el código del libro seleccionado
	int selectedBookId;
	printf("Ingrese el código del libro que desea ver: ");
	scanf("%d", &selectedBookId);

	// Preparar el statement SQL para buscar el libro por código
	sqlite3_stmt *stmt2;
	const char *sql2 = "SELECT * FROM libro WHERE id_libro = ?";
	result = sqlite3_prepare_v2(db, sql2, strlen(sql2) + 1, &stmt2, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement: %s\n", sqlite3_errmsg(db));
		guardarErrorEnLog("Error preparing statement");
		sqlite3_close(db);
		return;
	}

	// Vincular el valor del código al marcador de posición
	result = sqlite3_bind_int(stmt2, 1, selectedBookId);
	if (result != SQLITE_OK) {
		printf("Error binding parameter: %s\n", sqlite3_errmsg(db));
		guardarErrorEnLog("Error binding parameter");
		sqlite3_finalize(stmt2);
		sqlite3_close(db);
		return;
	}

	// Ejecutar la consulta y recuperar los datos del libro
	if (sqlite3_step(stmt2) == SQLITE_ROW) {
		int bookId = sqlite3_column_int(stmt2, 0);
		const unsigned char *bookTitle = sqlite3_column_text(stmt2, 1);
		const unsigned char *bookAuthor = sqlite3_column_text(stmt2, 2);
		const unsigned char *bookCategory = sqlite3_column_text(stmt2, 3);
		const unsigned char *bookEditorial = sqlite3_column_text(stmt2, 4);
		const unsigned char *bookYear = sqlite3_column_text(stmt2, 5);

		// Obtener los demás datos del libro y mostrarlos
		printf("Código: %d\n", bookId);
		printf("Título: %s\n", bookTitle);
		printf("Autor: %s\n", bookAuthor);
		printf("Categoría: %s\n", bookCategory);
		printf("Editorial: %s\n", bookEditorial);
		printf("Año: %s\n", bookYear);

	} else {
		printf("No se encontró un libro con el código %d\n", selectedBookId);
	}
	// Clean up
	sqlite3_finalize(stmt2);
	cerrarDB(db);

}

void buscarLibroPorCategoria() {
	// Connect to the database
	sqlite3 *db = abrirDB();
	int result;

	// Prepare the SQL statement to retrieve the categories
	sqlite3_stmt *stmt;
	const char *sql = "SELECT id_cat, nombre_c FROM categoria";
	result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement: %s\n", sqlite3_errmsg(db));
		guardarErrorEnLog("Error preparing statement");
		sqlite3_close(db);
		return;
	}

	// Execute the statement and retrieve the categories
	printf("Categorías disponibles:\n");
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		int codigo = sqlite3_column_int(stmt, 0);
		const unsigned char *nombre = sqlite3_column_text(stmt, 1);
		printf("Código: %d, Nombre: %s\n", codigo, nombre);
	}

	// Clean up
	sqlite3_finalize(stmt);

	// Prompt the user to enter a category code
	int selectedCodigo;
	printf("Ingrese el código de la categoría que desea ver: ");
	scanf("%d", &selectedCodigo);

	// Preparar el statement SQL para recuperar los libros de la categoría seleccionada
	sqlite3_stmt *stmt2;
	const char *sql2 = "SELECT * FROM libro WHERE id_cat = ?";
	result = sqlite3_prepare_v2(db, sql2, strlen(sql2) + 1, &stmt2, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement: %s\n", sqlite3_errmsg(db));
		guardarErrorEnLog("Error preparing statement");
		sqlite3_close(db);
		return;
	}

	result = sqlite3_bind_int(stmt2, 1, selectedCodigo);
	if (result != SQLITE_OK) {
		printf("Error binding parameter: %s\n", sqlite3_errmsg(db));
		guardarErrorEnLog("Error binding parameter");
		sqlite3_finalize(stmt2);
		sqlite3_close(db);
		return;
	}

	// Execute the statement and retrieve the books
	printf("Libros de la categoría con código %d:\n", selectedCodigo);
	while (sqlite3_step(stmt2) == SQLITE_ROW) {
		int bookId = sqlite3_column_int(stmt2, 0);
		const unsigned char *bookTitle = sqlite3_column_text(stmt2, 1);
		printf("Código: %d, Título: %s\n", bookId, bookTitle);
	}

	// Clean up
	sqlite3_finalize(stmt2);
	sqlite3_close(db);
}

void buscarLibroPorEditorial() {
	// Connect to the database
	sqlite3 *db;
	int result = sqlite3_open("biblioteca.db", &db);

	// Prepare the SQL statement to retrieve the editorials
	sqlite3_stmt *stmt;
	const char *sql = "SELECT id_edi, nombre_e FROM editorial";
	result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement: %s\n", sqlite3_errmsg(db));
		guardarErrorEnLog("Error preparing statement");
		sqlite3_close(db);
		return;
	}

	// Execute the statement and retrieve the editorials
	printf("Editoriales disponibles:\n");
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		int codigo = sqlite3_column_int(stmt, 0);
		const unsigned char *nombre = sqlite3_column_text(stmt, 1);
		printf("Código: %d, Nombre: %s\n", codigo, nombre);
	}

	// Clean up
	sqlite3_finalize(stmt);

	// Prompt the user to enter an editorial code
	int selectedCodigo;
	printf("Ingrese el código de la editorial que desea ver: ");
	scanf("%d", &selectedCodigo);

	// Prepare the SQL statement to retrieve the books from the selected editorial
	sqlite3_stmt *stmt2;
	const char *sql2 = "SELECT * FROM libro WHERE id_edi = ?";
	result = sqlite3_prepare_v2(db, sql2, strlen(sql2) + 1, &stmt2, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement: %s\n", sqlite3_errmsg(db));
		guardarErrorEnLog("Error preparing statement");
		sqlite3_close(db);
		return;
	}

	result = sqlite3_bind_int(stmt2, 1, selectedCodigo);
	if (result != SQLITE_OK) {
		printf("Error binding parameter: %s\n", sqlite3_errmsg(db));
		guardarErrorEnLog("Error binding parameter");
		sqlite3_finalize(stmt2);
		sqlite3_close(db);
		return;
	}

	// Execute the statement and retrieve the books
	printf("Libros de la editorial con código %d:\n", selectedCodigo);
	while (sqlite3_step(stmt2) == SQLITE_ROW) {
		int bookId = sqlite3_column_int(stmt2, 0);
		const unsigned char *bookTitle = sqlite3_column_text(stmt2, 1);
		printf("Código: %d, Título: %s\n", bookId, bookTitle);
	}

	// Clean up
	sqlite3_finalize(stmt2);
	sqlite3_close(db);
}

