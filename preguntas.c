#include <stdio.h>
#include <stdlib.h>
#include "preguntas.h"
#include "respuestas.h"

void MostrarPreguntas(Pregunta *lista) {
    if (!lista) {
        printf("No hay preguntas cargadas.\n");
        return;
    }

    int i = 1;
    Pregunta *act = lista;
    while (act) {
        printf("Pregunta %d: %s\n", i++, act->PreguntaTexto);
        MostrarRespuestas(act->TopeRespuestas);  // llama a respuestas.c
        printf("\n");
        act = act->sig;
    }
}
