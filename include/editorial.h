#ifndef EDITORIAL_H
#define EDITORIAL_H
typedef struct {
    char *nombre;
    char *fecha;
}Editorial;

Editorial *crear_editorial(const char *nombre, const char *fecha);
void destruir_editorial(Editorial *editorial);
void imprimirEditorial(Editorial editorial);
#endif