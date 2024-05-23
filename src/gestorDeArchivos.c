#include "../include/gestorDeArchivos.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void guardarErrorEnLog(char* mensajeError) {
	time_t ahora = time(NULL);
	struct tm* tiempo = localtime(&ahora);
	char hora[20];
	strftime(hora, sizeof(hora), "%Y-%m-%d %H:%M:%S", tiempo);


	FILE* archivoLog = fopen("ficheroLog.log", "a");
	fprintf(archivoLog, "[%s] Error: %s\n", hora, mensajeError);
	fclose(archivoLog);
}

void guardarInfoEnLog(char* mensajeInfo) {
	time_t ahora = time(NULL);
	struct tm* tiempo = localtime(&ahora);
	char hora[20];
	strftime(hora, sizeof(hora), "%Y-%m-%d %H:%M:%S", tiempo);

	FILE* archivoLog = fopen("ficheroLog.log", "a");
	fprintf(archivoLog, "[%s] Info: %s\n", hora, mensajeInfo);
	fclose(archivoLog);
}
