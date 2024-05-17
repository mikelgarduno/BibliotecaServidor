#include "../include/menu.h"
#include <stdio.h> 
#include <stdlib.h>

#include "../include/autor.h"
#include "../include/categoria.h"
#include "../include/editorial.h"
#include "../include/libro.h"
#include "../include/sqlManager.h"




void imprimirMenuPrincipal(){ 		//Funcion para imprimir el menu principal
	

printf(
		"\n############################\n" 
		"#//////////////////////////#\n"
		"#     	  BIBLIOTECA        #\n" 
		"#//////////////////////////#\n" 
		"############################\n" 
		"#                          #\n" 
	 	"#  1. Descargar Libro      #\n" 
		"#  2. Subir Libro          #\n" 
		"#  3. Modificar Libro      #\n" 
		"#  4. Registrar Autor      #\n" 
		"#  5. Registrar Editorial  #\n" 
		"#  6. Registrar Categoria  #\n" 
		"#  7. Salir                #\n" 
		"#                          #\n" 
		"############################\n" 
		"#      Inserte numero      #\n" 
		"############################\n"
	);
fflush(stdout);
}

int seleccionarOpcionMenus() { //Funcion para seleccionar una opcion del menu
	int input;
	scanf("%d", &input);
	fflush(stdin);
	return input;

}



void gestionarSubmenus(int n) { //Funcion para gestionar los submenus

	switch (n) {
	    case 1:
	      MenuDescargar();
	      break;

	    case 2:
	      MenuSubir();
	      break;

	    case 3:
		  MenuBorrarLibro();
		  break;

		case 4:
		  MenuRegistrarAutor();
		  break;

	    case 5:
		    MenuRegistrarEditorial();
		  break;

		case 6:
		
		  MenuRegistrarCategoria();
		  break;

		case 7:
		printf("Saliendo...\n");
		fflush(stdout);
		  exit(0);
		  break;
		

	    default:
			
			printf(
				"############################\n" 
				"#   INSERTE VALOR VALIDO   #\n"  
				"############################\n"
			);
			fflush(stdout);
			sleep(1);
			
			

	}

}


void MenuDescargar() { //Funcion para descargar un libro
system("cls");
	int opcion;

	printf("############################\n");
	printf("#--------------------------#\n");
    printf("Buscar por:\n");
    printf("1) Autor\n");
    printf("2) Titulo\n");
    printf("3) Categoria\n");
    printf("4) Editorial\n");
	printf("#--------------------------#\n");
	printf("############################\n");
    printf("Ingrese el numero correspondiente a la opcion deseada: ");
	fflush(stdout);
    scanf("%d", &opcion);
	
	switch (opcion) {
        case 1:
		printf("Buscando por autor\n");
		fflush(stdout);
			//buscarPorAutor();
            break;
        case 2:
		printf("Buscando por titulo\n");
		fflush(stdout);
           // buscarPorTitulo();
            break;
        case 3:
		printf("Buscando por categoria\n");
		fflush(stdout);
           // buscarPorCategoria();
            break;
        case 4:
		printf("Buscando por editorial\n");
		fflush(stdout);
            //buscarPorEditorial();
            break;
        default:
            printf("Opción no válida\n");
            fflush(stdout);
			
    }
}


void MenuSubir(){ //Funcion para subir un libro
	system("cls");
	printf("Recuerde que para subir un libro, es necesario\nhaber registrado previamente el autor, la editorial y la categoria\n");
	fflush(stdout);
	char isbn[50];
	char titulo[50];
	int autor;
	int categoria;
	int editorial;
	char fecha[5];
	char contenido[5000];


	printf(
		"############################\n"
		"#        Introducir        #\n"
		"#          ISBN            #\n"
		"############################\n"
		"#     Inserte el ISBN      #\n"
		"############################\n"
	);
	fflush(stdout);
	scanf("%s", isbn);
	system("cls");

	printf(
		"############################\n"
		"#        Introducir        #\n"
		"#          Titulo          #\n"
		"############################\n"
		"# Inserte nombre completo  #\n"
		"############################\n"
	);
	fflush(stdout);
	scanf("%[^\n]s", titulo);
	system("cls");

	printf(
		"############################\n"
		"#        Introducir        #\n"
		"#          Fecha           #\n"
		"############################\n"
		"#      Inserte anyo        #\n"
		"#      de publicacion      #\n"
		"############################\n"
	);
	fflush(stdout);
	scanf("%s", fecha);
	system("cls");

	printf(
		"############################\n"
		"#        Introducir        #\n"
		"#        Contenido         #\n"
		"############################\n"
		"#      Inserte texto       #\n"
		"############################\n"
	);
	fflush(stdout);
	scanf("%[^\n]s", contenido);
	system("cls");
	
	autor =  seleccionarAutor();
	categoria = seleccionarCategoria();
	editorial = seleccionarEditorial();

	if(comprobarLibroExistente(isbn)==1){
		Libro* objLibro;
		objLibro = crear_libro(isbn, titulo, autor, editorial,categoria,fecha, contenido);
		insertarLibro(*objLibro);
		destruir_libro(objLibro);
	}
}


void MenuBorrarLibro(){ 		

}


void MenuRegistrarAutor(){ //Funcion para registrar un autor
system("cls");

	char nombre[50];
	char fecha[50];
	char lugar[50];

	printf(
		"############################\n"
		"#         Registrar        #\n"
		"#          Autor           #\n"
		"############################\n"
		"# Inserte nombre completo  #\n"
		"############################\n"
	);
	fflush(stdout);
	scanf("%[^\n]s", nombre);
	system("cls");

	printf(
		"############################\n"
		"#      Inserte anyo        #\n"
		"#      de nacimiento       #\n"
		"############################\n"
	);
	fflush(stdout);
	scanf("%s", fecha);
	system("cls");

	printf(
		"############################\n"
		"#      Inserte nombre      #\n"
		"# del lugar de nacimiento  #\n"
		"############################\n"
	);
	fflush(stdout);
	scanf("%s", lugar);
	system("cls");
	if(comprobarAutorNoExiste(nombre)==1){
		Autor* objAutor;
		objAutor = crear_autor(nombre, fecha, lugar);
		insertarAutor(*objAutor);
		destruir_autor(objAutor);
	}

}


void MenuRegistrarCategoria(){ //Funcion para registrar una categoria
system("cls");

	char nombre[50];
	printf(
		"############################\n"
		"#         Registrar        #\n"
		"#         Categoria        #\n"
		"############################\n"
		"#      Inserte nombre      #\n"
		"#      de la categoria     #\n"
		"############################\n"
	);
	fflush(stdout);
	scanf("%s", nombre);
	system("cls");
	
	if(comprobarCategoriaNoExiste(nombre)==1){
	Categoria* objCategoria;
	objCategoria = crearCategoria(nombre);
	insertarCategoria(*objCategoria);
	destruirCategoria(objCategoria);
	}
}


void MenuRegistrarEditorial(){ //Funcion para registrar una editorial
system("cls");
	char nombre[50];
	char fecha[50];

	printf(
		"############################\n"
		"#         Registrar        #\n"
		"#         Editorial        #\n"
		"############################\n"
		"#       Inserte nombre     #\n"
		"#      de la editorial     #\n"
		"############################\n"
	);
	fflush(stdout);
	scanf("%s", nombre);
	system("cls");

	printf(
		"############################\n"
		"#      Inserte fecha       #\n"
		"#       de fundacion       #\n"
		"############################\n"
	);
	fflush(stdout);
	scanf("%s",fecha);
	system("cls");

	if(comprobarEditorialNoExiste(nombre)==1){
		Editorial* objEditorial;
		objEditorial = crear_editorial(nombre, fecha);
		insertarEditorial(*objEditorial);
		destruir_editorial(objEditorial);
	}
	//imprimirEditorial(*objEditorial);
}

void cargando(){ //Funcion para simular un cargando
	printf("Cargando.");
	fflush(stdout);
	sleep(1);
	printf(".");
	fflush(stdout);
	sleep(1);
	printf(".\n");
	fflush(stdout);
}

void empezarMenu(){ //Funcion para empezar el menu
	printf("Bienvenido al servidor local de la biblioteca\n");
	fflush(stdout);
	cargando();
	while (1){
	sleep(1);
	system("cls");
    imprimirMenuPrincipal();
	gestionarSubmenus(seleccionarOpcionMenus());
	}
}


void buscarPorAutor() {
    system("cls");
	printf("Autores disponibles:\n");
	fflush(stdout);
	//mostrarAutores();

	int autorSeleccionado;
	printf("Escriba el codigo del autor que desea seleccionar: ");
	fflush(stdout);
	scanf("%d", &autorSeleccionado);
	fflush(stdout);

	//seleccionarAutor(autorSeleccionado);

	
}

void buscarPorTitulo() {
	char titulo[100];
	printf("Ingrese el título que desea buscar: ");
	fflush(stdout);
	scanf("%s", titulo);
	//buscarLibroPorTitulo(titulo);
}

void buscarPorCategoria() {
/* 
	// Connect to the database
	sqlite3 *db;
	int result = sqlite3_open("biblioteca.db", &db);
	if (result != SQLITE_OK) {
		printf("Error opening database: %s\n", sqlite3_errmsg(db));
		guardarErrorEnLog("Error opening database");
		return;
	}

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
	sqlite3_close(db); */
}

void buscarPorEditorial() {
	/* // Connect to the database
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
	sqlite3_close(db); */
}

