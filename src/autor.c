#include <stdlib.h>
#include <string.h>
#include "../include/autor.h"

Autor *crear_autor(const char *nombre, const char *fecha_nacimiento, const char *lugar_nacimiento) {
    Autor *autor = (Autor *)malloc(sizeof(Autor));
    if (autor == NULL) {
        return NULL;
    }

    autor->name = strdup(nombre);
    autor->date = strdup(fecha_nacimiento);
    autor->place = strdup(lugar_nacimiento);

    return autor;
}

void destruir_autor(Autor *autor) {
    free(autor->name);
    free(autor->date);
    free(autor->place);
    free(autor);
}

void imprimir_autor(Autor autor){
    printf("%s;%s;%s\n", autor.name, autor.date, autor.place);

}

