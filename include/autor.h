#ifndef AUTOR_H
#define AUTOR_H
typedef struct {
    char *name;
    char *date;
    char *place;
} Autor;

Autor *crear_autor(const char *nombre, const char *fecha_nacimiento, const char *lugar_nacimiento);
void destruir_autor(Autor *autor);
void imprimir_autor(Autor autor);




#endif
