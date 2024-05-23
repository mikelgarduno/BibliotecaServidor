#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../include/sqlManager.h"
#include "../../include/autor.h"
#include "../../include/libro.h"
#include "../../include/categoria.h"
#include "../../include/editorial.h"
#include "../../include/gestorDeArchivos.h"

// Abre la base de datos
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

// Cierra la base de datos
void cerrarDB(sqlite3 *db) {
	int resultado = sqlite3_close(db);
	if (resultado != SQLITE_OK) {
		printf("No se pudo cerrar la base de datos, código de error: %d\n",resultado);
	} else {
		printf("BD cerrada correctamente.\n");
	}
}

//Inserta un autor en la base de datos
int insertarAutor(Autor objAutor, sqlite3* db) {
	int result;

	sqlite3_stmt *stmt;
	char sql[] =
			"INSERT INTO autor (nombre_a, fecha_ncto, lugar_ncto) VALUES (?, ?, ?)";

	result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 0;
	}

	sqlite3_bind_text(stmt, 1, objAutor.name, strlen(objAutor.name),
			SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, objAutor.date, strlen(objAutor.date),
			SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, objAutor.place, strlen(objAutor.place),
			SQLITE_STATIC);

	if(comprobarAutorNoExiste(objAutor.name, db) == 1){
		result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error insertando datos: %s\n", sqlite3_errmsg(db));
		fflush(stdout);
		sqlite3_finalize(stmt);
		return 0;
	} else {
		printf("Autor insertado correctamente\n");
		fflush(stdout);
		sqlite3_finalize(stmt);
		return 1;
	}
	}else{
		sqlite3_finalize(stmt);
		return 2;
	}


}

//Inserta una categoria en la base de datos
int insertarCategoria(Categoria objCategoria, sqlite3* db) {
	int result;

	sqlite3_stmt *stmt1;
	char sql[] = "INSERT INTO Categoria (nombre_c) VALUES (?)";

	result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt1, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement: %s\n", sqlite3_errmsg(db));
		fflush(stdout);
		sqlite3_close(db);
		return 0;
	}

	sqlite3_bind_text(stmt1, 1, objCategoria.name, strlen(objCategoria.name),SQLITE_STATIC);

	if(comprobarCategoriaNoExiste(objCategoria.name, db) == 1){
	result = sqlite3_step(stmt1);
	if (result != SQLITE_DONE) {
		printf("Error insertando datos: %s\n", sqlite3_errmsg(db));
		fflush(stdout);
		sqlite3_finalize(stmt1);
		return 0;
	} else {
		printf("Categoria insertada correctamente\n");
		fflush(stdout);
		sqlite3_finalize(stmt1);
		return 1;
	}
	}else{
		sqlite3_finalize(stmt1);
		return 2;	
	}
	

}

//Inserta una editorial en la base de datos
int insertarEditorial(Editorial objEditorial, sqlite3* db) {
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

	if(comprobarEditorialNoExiste(objEditorial.nombre, db) == 1){
	result = sqlite3_step(stmt2);
	if (result != SQLITE_DONE) {
		printf("Error insertando datos: %s\n", sqlite3_errmsg(db));
		fflush(stdout);
		sqlite3_finalize(stmt2);
		return 0;	
	} else {
		printf("Editorial insertada correctamente\n");
		fflush(stdout);
		sqlite3_finalize(stmt2);
		return 1;
	}
	}else{
		sqlite3_finalize(stmt2);
		return 2;
	}
}

//Inserta un libro en la base de datos
int insertarLibro(Libro objLibro, sqlite3* db) {
	int result;
	sqlite3_stmt *stmt;
	char sql[] =
			"INSERT INTO libro (isbn, titulo, fecha_pub, id_aut, id_cat, id_edi, contenido) VALUES (?, ?, ?, ?, ?, ?, ?)";
	result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement: %s\n", sqlite3_errmsg(db));
		fflush(stdout);
		sqlite3_close(db);
		return 0;
	}

	sqlite3_bind_text(stmt, 1, objLibro.isbn, strlen(objLibro.isbn),SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, objLibro.titulo, strlen(objLibro.titulo),SQLITE_STATIC);
	sqlite3_bind_text(stmt, 3, objLibro.fechaCreacion, strlen(objLibro.fechaCreacion), SQLITE_STATIC);
	sqlite3_bind_int(stmt, 4, objLibro.autor);
	sqlite3_bind_int(stmt, 5, objLibro.categoria);
	sqlite3_bind_int(stmt, 6, objLibro.editorial);
	sqlite3_bind_text(stmt, 7, objLibro.contenido, strlen(objLibro.contenido), SQLITE_STATIC);

	result = sqlite3_step(stmt);
	if (result == SQLITE_CONSTRAINT) {
		printf("El libro ya existe\n",sqlite3_errmsg(db));
		fflush(stdout);
		sqlite3_finalize(stmt);
		return 2;
	}else if(result != SQLITE_DONE){
		printf("Error insertando datos: %s\n", sqlite3_errmsg(db));
		fflush(stdout);
		sqlite3_finalize(stmt);
	return 0;
	} else {
		printf("Libro insertado correctamente\n");
		fflush(stdout);
		sqlite3_finalize(stmt);
		return 1;
	}
}

//Comprueba si la categoria ya existe
int comprobarCategoriaNoExiste(char *nombre, sqlite3* db) {
	int result;

	sqlite3_stmt *stmt;
	const char *sql = "SELECT id_cat FROM Categoria WHERE nombre_c = ?";
	result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement: %s\n", sqlite3_errmsg(db));
		fflush(stdout);
		sqlite3_close(db);
		return 0;
	}

	sqlite3_bind_text(stmt, 1, nombre, strlen(nombre), SQLITE_STATIC);

	if (sqlite3_step(stmt) == SQLITE_ROW) {
		int id = sqlite3_column_int(stmt, 0);
		printf("La categoria %s ya existe con el ID %d\n", nombre, id);
		fflush(stdout);
		sqlite3_finalize(stmt);
		return 0;
	} else {
		printf("La categoria %s no existe\n", nombre);
		fflush(stdout);
		sqlite3_finalize(stmt);
		return 1;
	}

}

//Comprueba si la editorial ya existe
int comprobarEditorialNoExiste(char *nombre, sqlite3* db) {
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
		return 0;
	} else {
		printf("La editorial %s no existe\n", nombre);
		fflush(stdout);
		sqlite3_finalize(stmt);
		return 1;
	}
}

//Comprueba si el autor ya existe
int comprobarAutorNoExiste(char *nombre, sqlite3* db) {
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
		return 0;
	} else {
		printf("El autor %s no existe\n", nombre);
		fflush(stdout);
		sqlite3_finalize(stmt);
		return 1;
	}
}

//Devuelve un array con todas las categorias
char* obtenerCategorias(sqlite3* db){
	int result;
	sqlite3_stmt *stmt;
	const char *sql = "SELECT id_cat, nombre_c FROM Categoria";
	result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement: %s\n", sqlite3_errmsg(db));
		fflush(stdout);
		sqlite3_close(db);
		return NULL;
	}

	char* categorias = NULL;
    int tamanoTotal = 0;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *nombre = sqlite3_column_text(stmt, 1);
        int tamano = snprintf(NULL, 0, "%d;%s\n", id, nombre);
        categorias = (char*)realloc(categorias, tamanoTotal + tamano + 1);
        snprintf(categorias + tamanoTotal, tamano + 1, "%d;%s\n", id, nombre);
        tamanoTotal += tamano;
    }

    sqlite3_finalize(stmt);
    return categorias;
}

//Devuelve un array con todas las editoriales
char* obtenerEditoriales(sqlite3* db){
	int result;
	sqlite3_stmt *stmt;
	const char *sql = "SELECT id_edi, nombre_e, fecha_fund FROM Editorial";
	result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement: %s\n", sqlite3_errmsg(db));
		fflush(stdout);
		sqlite3_close(db);
		return NULL;
	}

	char* editoriales = NULL;
    int tamanoTotal = 0;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *nombre = sqlite3_column_text(stmt, 1);
		const unsigned char *fecha = sqlite3_column_text(stmt, 2);
        int tamano = snprintf(NULL, 0, "%d;%s;%s\n", id, nombre,fecha);
        editoriales = (char*)realloc(editoriales, tamanoTotal + tamano + 1);
        snprintf(editoriales + tamanoTotal, tamano + 1, "%d;%s;%s\n", id, nombre,fecha);
        tamanoTotal += tamano;
    }

    sqlite3_finalize(stmt);
    return editoriales;
}

//Devuelve un array con todos los autores


char* obtenerAutores(sqlite3* db){ 
	int result;
	sqlite3_stmt *stmt;
	const char *sql = "SELECT * FROM Autor";
	result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement: %s\n", sqlite3_errmsg(db));
		fflush(stdout);
		sqlite3_close(db);
		return NULL;
	}

	char* autores = NULL;
    int tamanoTotal = 0;

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *nombre = sqlite3_column_text(stmt, 1);
		const unsigned char *fecha = sqlite3_column_text(stmt, 2);
		const unsigned char *lugar = sqlite3_column_text(stmt, 3);
        int tamano = snprintf(NULL, 0, "%d;%s;%s;%s\n", id, nombre,fecha,lugar);
        autores = (char*)realloc(autores, tamanoTotal + tamano + 1);
		snprintf(autores + tamanoTotal, tamano + 1, "%d;%s;%s;%s\n", id,nombre,fecha,lugar);
        tamanoTotal += tamano;
    }

    sqlite3_finalize(stmt);
    return autores;
}

//Devuelve un array con todos los libros
char* obtenerLibros(sqlite3* db){
	int result;
	sqlite3_stmt *stmt;
	const char *sql = "SELECT * FROM Libro";
	result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement: %s\n", sqlite3_errmsg(db));
		fflush(stdout);
		sqlite3_close(db);
		return NULL;
	}

	char* libros = NULL;
	int tamanoTotal = 0;

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		const unsigned char *isbn = sqlite3_column_text(stmt, 0);
		const unsigned char *titulo = sqlite3_column_text(stmt, 1);
		const unsigned char *fecha = sqlite3_column_text(stmt, 2);
		int id_aut = sqlite3_column_int(stmt, 3);
		int id_cat = sqlite3_column_int(stmt, 4);
		int id_edi = sqlite3_column_int(stmt, 5);
		const unsigned char *contenido = sqlite3_column_text(stmt, 6);
		int tamano = snprintf(NULL, 0, "%s;%s;%s;%d;%d;%d;%s\n",isbn,titulo,fecha,id_aut,id_cat,id_edi,contenido);
		libros = (char*)realloc(libros, tamanoTotal + tamano + 1);
		snprintf(libros + tamanoTotal, tamano + 1, "%s;%s;%s;%d;%d;%d;%s\n",isbn,titulo,fecha,id_aut,id_cat,id_edi,contenido);
		tamanoTotal += tamano;
	}

	sqlite3_finalize(stmt);
	return libros;

}	

//Borra un libro de la base de datos
int borrarLibro(int id, sqlite3* db){
	int result;
	sqlite3_stmt *stmt;
	const char *sql = "DELETE FROM libro WHERE ISBN = ?";
	result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement: %s\n", sqlite3_errmsg(db));
		fflush(stdout);
		sqlite3_close(db);
		return 0;
	}
	sqlite3_bind_int(stmt, 1, id);
	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error borrando datos: %s\n", sqlite3_errmsg(db));
		fflush(stdout);
		sqlite3_finalize(stmt);
		return 0;
	} else {
		int filasAfectadas = sqlite3_changes(db);
		if (filasAfectadas == 0) {
			printf("No se ha encontrado ningún libro con el ID %d\n", id);
			fflush(stdout);
			sqlite3_finalize(stmt);
			return 4;
		} else {
			printf("Libro borrado correctamente\n");
			fflush(stdout);
			sqlite3_finalize(stmt);
			return 3;
		}
	}
}

// Función para ejecutar una consulta SQL
void ejecutarSQL(char *sql, sqlite3* db) {
    if (db == NULL) {
        return;
    }

    char *errMsg = 0;
    int rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        printf("Error en SQL: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Operación de SQL ejecutada con éxito\n");
    }

}


