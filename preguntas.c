#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "Menu_Generico.h"
#include "preguntas.h"
#include "respuestas.h"

int contarPreguntas(Pregunta *inicio) {
    int count = 0;
    while (inicio != NULL) {
        count++;
        inicio = inicio->sig;
    }
    return count;
}

Pregunta* ObtenerPreguntaPorIndice(Pregunta *inicio, int indice) {
    int i = 0;
    while (inicio != NULL && i < indice) {
        inicio = inicio->sig;
        i++;
    }
    return inicio;
}

void printPreguntas(void *contexto) {
    ContextoPregunta *ctx = (ContextoPregunta *)contexto;
    Encuesta *e = ctx->encuesta;
    Pregunta *p = ctx->actual;

    printf("==== ENCUESTA ====");
    printf("\nID: %d", e->Encuesta_Id);
    printf("\nNombre: %s", e->Denominacion);
    printf("\nPreguntas Totales: %d", contarPreguntas(e->TopePreguntas));
    printf("\n-------------------------\n");
    printf("\nPregunta Actual: %s", p ? p->PreguntaTexto : "(ninguna)");
    printf("\n");
}

void IngresarPregunta(void *contexto) {
    ContextoPregunta *ctx = (ContextoPregunta *)contexto;
    Pregunta *p = ctx->actual;

    if (p != NULL) {
        menuRespuestas(p->TopeRespuestas);
    }
}

void salirDePreguntas(void *contexto) {
    ContextoPregunta *ctx = (ContextoPregunta *)contexto;
    ctx->salir = 1;
}

void SiguientePregunta(void *contexto) {
    ContextoPregunta *ctx = (ContextoPregunta *)contexto;
    if (ctx->actual != NULL && ctx->actual->sig != NULL) {
        ctx->actual = ctx->actual->sig;
        ctx->posicion++;
    }
}

void AnteriorPregunta(void *contexto) {
    ContextoPregunta *ctx = (ContextoPregunta *)contexto;
    if (ctx->posicion > 0) {
        ctx->actual = ctx->inicio;
        for (int i = 0; i < ctx->posicion - 1; i++) {
            ctx->actual = ctx->actual->sig;
        }
        ctx->posicion--;
    }
}

void menuPreguntas(Encuesta *encuesta) {
    if (!encuesta || !encuesta->TopePreguntas) {
        printf("Esta encuesta no tiene preguntas.");
        system("pause");
        return;
    }

    ContextoPregunta ctx;
    ctx.encuesta = encuesta;
    ctx.inicio = encuesta->TopePreguntas;
    ctx.actual = ctx.inicio;
    ctx.posicion = 0;
    ctx.salir = 0;

    while (!ctx.salir) {
        MenuOpcion opciones[4];
        int cantidad = 0;

        opciones[cantidad++] = (MenuOpcion){"Ingresar a la Pregunta", IngresarPregunta};

        if (ctx.posicion == 0 && ctx.actual->sig != NULL)
            opciones[cantidad++] = (MenuOpcion){"Siguiente", SiguientePregunta};
        else if (ctx.actual->sig == NULL && ctx.posicion > 0)
            opciones[cantidad++] = (MenuOpcion){"Anterior", AnteriorPregunta};
        else if (ctx.actual->sig != NULL && ctx.posicion > 0) {
            opciones[cantidad++] = (MenuOpcion){"Siguiente", SiguientePregunta};
            opciones[cantidad++] = (MenuOpcion){"Anterior", AnteriorPregunta};
        }

        opciones[cantidad++] = (MenuOpcion){"Salir", salirDePreguntas};

        menuG_con_encabezado(opciones, cantidad, &ctx, printPreguntas);
    }
}
