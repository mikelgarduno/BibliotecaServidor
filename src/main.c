// Servidor Local in C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/sqlManager.h"
#include "../include/sockets.h"
#include "../include/autor.h"
#include "../include/editorial.h"
#include "../include/libro.h"
#include "../include/categoria.h"
#include "../include/gestorDeArchivos.h"
#include <winsock.h>

 #define SERVER_IP "127.0.0.1"
 #define SERVER_PORT 6000

void handleRegistrarAutor(SOCKET comm_socket, sqlite3* baseDeDatos);
void handleRegistrarLibro(SOCKET comm_socket, sqlite3* baseDatos);
void handleRegistrarCategoria(SOCKET comm_socket, sqlite3* baseDeDatos);
void handleRegistrarEditorial(SOCKET comm_socket, sqlite3* baseDeDatos);
void handleBorrarLibro(SOCKET comm_socket, sqlite3* baseDeDatos);


int main(void) {
   sqlite3* baseDeDatos = abrirDB();

   // Inicia la conexión y gestiona los inputs del usuario
   WSADATA wsaData;
   SOCKET conn_socket;
   SOCKET comm_socket;
   struct sockaddr_in server;
   struct sockaddr_in client;
   char sendBuff[1024], recvBuff[1024];

   printf("Iniciando libreria socket\n");
   if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
      printf("Error al iniciar la libreria socket. Codigo de error: %d\n", WSAGetLastError());
      return -1;
   }
   printf("Libreria socket iniciada correctamente\n");

   // SOCKET creation
   if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
      printf("Error al crear el socket. Codigo de error: %d\n", WSAGetLastError());
      WSACleanup();
      return -1;
   }
   printf("Socket creado correctamente\n");

   server.sin_addr.s_addr = inet_addr(SERVER_IP);
   server.sin_family = AF_INET;
   server.sin_port = htons(SERVER_PORT);

   if (bind(conn_socket, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
      printf("Error al realizar el bind. Codigo de error: %d\n", WSAGetLastError());
      closesocket(conn_socket);
      WSACleanup();
      return -1;
   }
   printf("Bind realizado correctamente\n");

   // LISTEN to incoming connections (socket server moves to listening mode)
   if (listen(conn_socket, 1) == SOCKET_ERROR) {
      printf("Error al realizar el listen. Codigo de error: %d\n", WSAGetLastError());
      closesocket(conn_socket);
      WSACleanup();
      return -1;
   }

   // ACCEPT incoming connections (server keeps waiting for them)
   printf("Esperando conexion entrante...\n");
   int stsize = sizeof(struct sockaddr);
   comm_socket = accept(conn_socket, (struct sockaddr*) &client, &stsize);

   if (comm_socket == INVALID_SOCKET) {
      printf("Error al aceptar la conexion. Codigo de error: %d\n", WSAGetLastError());
      closesocket(conn_socket);
      WSACleanup();
      return -1;
   }

   // Closing the listening sockets (is not going to be used anymore)
   closesocket(conn_socket);

   printf("Conexion aceptada\n");

   printf("Esperando comandos del cliente...");
   while (1) {
      recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
      printf("Comando recibido: %s \n", recvBuff);

      if (strcmp(recvBuff, "REGISTRAR_AUTOR") == 0) {
         handleRegistrarAutor(comm_socket, baseDeDatos);
      } else if (strcmp(recvBuff, "REGISTRAR_LIBRO") == 0) {
         handleRegistrarLibro(comm_socket, baseDeDatos);
      } else if (strcmp(recvBuff, "REGISTRAR_CATEGORIA") == 0) {
         handleRegistrarCategoria(comm_socket, baseDeDatos);
      } else if (strcmp(recvBuff, "REGISTRAR_EDITORIAL") == 0) {
         handleRegistrarEditorial(comm_socket, baseDeDatos);
      } else if (strcmp(recvBuff, "BORRAR_LIBRO") == 0) {
         handleBorrarLibro(comm_socket, baseDeDatos);
      }
   }

   closesocket(comm_socket);
   WSACleanup();
   return 0;

   cerrarDB(baseDeDatos);
   return 0;
}

void handleRegistrarAutor(SOCKET comm_socket, sqlite3* baseDeDatos) {
    char name[1024], date[1024], place[1024];
    recv(comm_socket, name, sizeof(name), 0);
    recv(comm_socket, date, sizeof(date), 0);
    recv(comm_socket, place, sizeof(place), 0);

   Autor* autor = crearAutor(name, date, place);
   insertarAutor(*autor, baseDeDatos);

    char response[] = "Autor registrado correctamente";
    send(comm_socket, response, strlen(response), 0);
}

void handleRegistrarCategoria(SOCKET comm_socket, sqlite3* baseDeDatos) {
    char name[50];
    recv(comm_socket, name, sizeof(name), 0);

	Categoria* categoria= crearCategoria(name);
    insertarCategoria(*categoria,baseDeDatos);

   char response[] = "Categoria registrada correctamente";
   send(comm_socket, response, strlen(response), 0);
	
}

void handleRegistrarEditorial(SOCKET comm_socket, sqlite3* baseDeDatos) {
	
    char name[50], fecha[50];
    recv(comm_socket, name, sizeof(name), 0);
    recv(comm_socket, fecha, sizeof(fecha), 0);
	

    Editorial* editorial = crearEditorial(name, fecha);
	insertarEditorial(*editorial,baseDeDatos);

    char response[] = "Editorial registrada correctamente";
    send(comm_socket, response, strlen(response), 0);
	
}
