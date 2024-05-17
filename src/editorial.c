#include <stdlib.h>
#include <string.h>
#include "../include/editorial.h"

Editorial *crear_editorial(const char *nombre, const char *fecha) {
    Editorial *editorial = (Editorial *)malloc(sizeof(Editorial));
    if (editorial == NULL) {
        return NULL;
    }

    editorial->nombre = strdup(nombre);
    editorial->fecha = strdup(fecha);

    return editorial;
}

void destruir_editorial(Editorial *editorial) {
    free(editorial->nombre);
    free(editorial->fecha);
    free(editorial);
}

void imprimirEditorial(Editorial editorial){
    printf("%s;%s\n", editorial.nombre, editorial.fecha);
}

