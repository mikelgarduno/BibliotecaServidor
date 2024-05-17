#ifndef MENU_H
#define MENU_H


void imprimirMenuPrincipal();
void gestionarSubmenus(int n);
int seleccionarOpcionMenus();

void MenuDescargar();
void MenuSubir();
void MenuBorrarLibro();

void MenuRegistrarAutor();
void MenuRegistrarCategoria();
void MenuRegistrarEditorial();

void buscarPorAutor();
void buscarPorTitulo();
void buscarPorCategoria();
void buscarPorEditorial();
#endif // MENU_H