#ifndef MENU_GENERICO_H
#define MENU_GENERICO_H

typedef struct
{
    const char *texto;
    void (*accion)(void*);
} MenuOpcion;


int Salir(const char *texto);
int leerTecla();
void printMenu(MenuOpcion opciones[], int cantidad, int seleccion);
void menuG(MenuOpcion opciones[], int cantidad, void *contexto);
void menuG_con_encabezado(MenuOpcion opciones[], int cantidad, void *contexto, void (*printEncabezado)(void *));
void salirDeEncuesta(void *ctx);


#endif
