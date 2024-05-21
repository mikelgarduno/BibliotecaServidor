
#include "../include/autor.h"
#include "../include/categoria.h"
#include "../include/editorial.h"
#include "../include/libro.h"
#include "../include/sqlManager.h"
#include <iostream>
#include <winsock.h>

using namespace std;

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

//Inicia la conexión y gestiona los inputs del usuario
SOCKET empezarConexion(){
	WSADATA wsaData;
	SOCKET conn_socket;
	SOCKET comm_socket;
	struct sockaddr_in server;
	struct sockaddr_in client;
	char sendBuff[1024], recvBuff[1024];

	cout << "Iniciando libreria socket\n" << endl;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		cout << " No se ha podido inicializar la libreria socket. Codigo de error: " << WSAGetLastError() << endl;
		return -1;
	}
	cout << "Libreria socket inicializada" << endl;

	//SOCKET creation
	if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		cout << "No se ha podido crear el socket. Codigo de error: " << WSAGetLastError() << endl;
		WSACleanup();
		return -1;
	}
	cout << "Socket creado correctamente" << endl;

	server.sin_addr.s_addr = inet_addr(SERVER_IP);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	if (bind(conn_socket, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
		cout << "Error al vincular el socket. Codigo de error: " << WSAGetLastError() <<endl;
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}
	cout << "Bindeo realizado correctamente" << endl;

	//LISTEN to incoming connections (socket server moves to listening mode)
	if (listen(conn_socket, 1) == SOCKET_ERROR) {
		cout << "Error al activar modo escucha. Codigo de error: " << WSAGetLastError() <<endl;
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	//ACCEPT incoming connections (server keeps waiting for them)
	cout << "Esperando a conexiones del cliente..." << endl;
	int stsize = sizeof(struct sockaddr);
	comm_socket = accept(conn_socket, (struct sockaddr*) &client, &stsize);

	if (comm_socket == INVALID_SOCKET) {
		cout << "Error al aceptar conexion del cliente. Codigo de error: " << WSAGetLastError() << endl;
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	cout << "Conexion entrante por: " << inet_ntoa(client.sin_addr) << " (" << ntohs(client.sin_port) << ")" << endl;

	// Closing the listening sockets (is not going to be used anymore)
	closesocket(conn_socket);

	cout << "Esperando comandos del cliente..." << endl;

	//ESTO IGUAL NO VA AQUI SOLO EN MAIN
	while (1) {
		memset(recvBuff, 0, sizeof(recvBuff));
		int bytesRecibidos = recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
		if (bytesRecibidos <= 0) {
			printf("Error al recibir datos o conexion cerrada\n");
			break;
		}
		recvBuff[bytesRecibidos] = '\0';
		printf("Comando recibido: %s\n", recvBuff);

		if (strcmp(recvBuff, "REGISTRAR_AUTOR") == 0) {
			handleRegistrarAutor(comm_socket);
		} else if (strcmp(recvBuff, "REGISTRAR_LIBRO") == 0) {
			handleRegistrarLibro(comm_socket);
		} else if (strcmp(recvBuff, "REGISTRAR_CATEGORIA") == 0) {
			handleRegistrarCategoria(comm_socket);
		} else if (strcmp(recvBuff, "REGISTRAR_EDITORIAL") == 0) {
			handleRegistrarEditorial(comm_socket);
		}
    }

    closesocket(comm_socket);
    WSACleanup();
    return 0;



}

void handleRegistrarAutor(SOCKET comm_socket) {
    char name[1024], date[1024], place[1024];
    recv(comm_socket, name, sizeof(name), 0);
    recv(comm_socket, date, sizeof(date), 0);
    recv(comm_socket, place, sizeof(place), 0);

    char sql[2048];
    snprintf(sql, sizeof(sql), "INSERT INTO autor (nombre_a, fecha_ncto, lugar_ncto) VALUES ('%s', '%s', '%s');", name, date, place);
    executeSQL(sql);

    char response[] = "Autor registrado correctamente";
    send(comm_socket, response, strlen(response), 0);
}

void handleRegistrarCategoria(SOCKET comm_socket) {
    char name[1024];
    recv(comm_socket, name, sizeof(name), 0);

    char sql[2048];
    snprintf(sql, sizeof(sql), "INSERT INTO Categoria (nombre_c) VALUES ('%s');", name);
    executeSQL(sql);

    char response[] = "Categoria registrada correctamente";
    send(comm_socket, response, strlen(response), 0);
}

void handleRegistrarEditorial(SOCKET comm_socket) {
    char name[1024], fecha[1024];
    recv(comm_socket, name, sizeof(name), 0);
    recv(comm_socket, fecha, sizeof(fecha), 0);

    char sql[2048];
    snprintf(sql, sizeof(sql), "INSERT INTO Editorial (nombre_e, fecha_fund) VALUES ('%s', '%s');", name, fecha);
    executeSQL(sql);

    char response[] = "Editorial registrada correctamente";
    send(comm_socket, response, strlen(response), 0);
}

void handleRegistrarLibro(SOCKET comm_socket) {
	char title[1024], isbn[1024], year[1024], id_autor[1024], id_categoria[1024], id_editorial[1024];
	recv(comm_socket, title, sizeof(title), 0);
	recv(comm_socket, isbn, sizeof(isbn), 0);
	recv(comm_socket, year, sizeof(year), 0);
	recv(comm_socket, id_autor, sizeof(id_autor), 0);
	recv(comm_socket, id_categoria, sizeof(id_categoria), 0);
	recv(comm_socket, id_editorial, sizeof(id_editorial), 0);

	char sql[2048];
	snprintf(sql, sizeof(sql), "INSERT INTO Libro (titulo, isbn, anio, id_autor, id_categoria, id_editorial) VALUES ('%s', '%s', '%s', '%s', '%s', '%s');", title, isbn, year, id_autor, id_categoria, id_editorial);
	executeSQL(sql);

	char response[] = "Libro registrado correctamente";
	send(comm_socket, response, strlen(response), 0);
}


/*Cierra la conexión
void cerrarConexion(SOCKET socket){
printf("Cerrar conexion\n");
fflush(stdout);
}

//Manda una lista de libros, autores, categorias o editoriales
void mandarLista(SOCKET socket, char **lista, int tamanoLista){
printf("Mandar lista\n");
fflush(stdout);
}

//Manda una respuesta al cliente
void mandarRespuesta(SOCKET socket, int respuesta){
if(respuesta == 0){
	printf("Error en la apertura de la BD\n");
	fflush(stdout);
}else if(respuesta == 1){
	printf("Se ha registrado correctamente\n");
	fflush(stdout);
}else if(respuesta == 2){
	printf("Ya existia en la Base de Datos\n");
	fflush(stdout);
}else if(respuesta == 3){
	printf("Se ha borrado correctamente\n");
	fflush(stdout);
}else if(respuesta == 4){
	printf("Ese libro no se puede borrar\n");
	fflush(stdout);
}
}
 */
 