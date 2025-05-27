#include <stdio.h>
#include <stdlib.h>
#include "Menu_Generico.h"

int main ()
{
    MenuOpcion Lobby [] =
    {
        {"Encuesta", NULL},
        {"Preguntas", NULL},
        {"Respuestas", NULL},
        {"Salir", NULL}
    };

    int cantidadOpciones = sizeof(Lobby) / sizeof(Lobby[0]);
    menuG(Lobby, cantidadOpciones, NULL);

    return 0;
}