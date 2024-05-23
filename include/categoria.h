#ifndef CATEGORIA_H
#define CATEGORIA_H

typedef struct {
    char *name;
}Categoria;


Categoria* crearCategoria(char *nombre);
void destruirCategoria(Categoria *categoria);
void imprimirCategoria(Categoria *categoria);

#endif
