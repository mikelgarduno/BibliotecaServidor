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

	FILE* archivoConfig = fopen("config.txt", "r");
	if (archivoConfig == NULL) {
		printf("Error opening config file\n");
		guardarErrorEnLog("Error opening config file");
		return;
	}
	char ruta[4096];
	fgets(ruta, sizeof(ruta), archivoConfig);
    fclose(archivoConfig);
	FILE* archivoLog = fopen(ruta, "a");
	if (archivoLog != NULL) {
		fprintf(archivoLog, "[%s] Error: %s\n", hora, mensajeError);
		fclose(archivoLog);
	}

}
