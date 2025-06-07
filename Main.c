#include <stdio.h>
#include <stdlib.h>
#include "encuesta.h"
#include "Menu_Generico.h"


int main ()
{
    PilaEncuestas pila;
    MenuOpcion Lobby [] =
    {
        {"Ver Encuestas", MostrarEncuesta},
        {"Salir", NULL}
    };

    int cantidadOpciones = sizeof(Lobby) / sizeof(Lobby[0]);
    menuG(Lobby, cantidadOpciones, &pila);

    return 0;
}