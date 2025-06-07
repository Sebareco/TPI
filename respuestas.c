#include <stdio.h>
#include <stdlib.h>
#include "respuestas.h"

void MostrarRespuestas(Respuesta *lista) {
    if (!lista) {
        printf("   [Sin respuestas]\n");
        return;
    }

    Respuesta *inicio = lista;
    Respuesta *act = lista;
    int n = 1;
    do {
        printf("   Opcion %d: %s", n++, act->RespuestaTexto);
        if (act->Elegida)
            printf("  <- seleccionada");
        printf("\n");
        act = act->sig;
    } while (act != inicio);
}
