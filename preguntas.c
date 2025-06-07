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

void MostrarEncabezadoEncuesta(Encuesta *e) {
    printf("====================================\n");
    printf("Encuesta ID: %d\n", e->Encuesta_Id);
    printf("Nombre: %s\n", e->Denominacion);
    printf("Año: %d\n", e->Anio);
    printf("Mes: %d\n", e->Encuesta_Mes);
    printf("Cantidad de preguntas: %d\n", contarPreguntas(e->TopePreguntas));
    printf("====================================\n\n");
}

void VerPregunta(void *contexto) {
    ContextoPregunta *ctx = (ContextoPregunta *)contexto;
    Pregunta *p = ctx->actual;

    if (p != NULL) {
        system("cls");
        printf("=== Detalles de la Pregunta ===\n");
        printf("ID: %d\n", p->Pregunta_Id);
        printf("Texto: %s\n", p->PreguntaTexto);
        printf("Ponderación: %.2f\n", p->Ponderacion);
        printf("---------------------------\n\n");
        system("pause");

        // Mostrar menú de respuestas
        menuRespuestas(p->TopeRespuestas);
    }
}

void VerRespuestas(void *contexto) {
    ContextoPregunta *ctx = (ContextoPregunta *)contexto;
    if (!ctx || !ctx->actual || !ctx->actual->TopeRespuestas) {
        printf("Esta pregunta no tiene respuestas.\n");
        system("pause");
        return;
    }

    menuRespuestas(ctx->actual->TopeRespuestas);
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
        printf("Esta encuesta no tiene preguntas.\n");
        system("pause");
        return;
    }

    ContextoPregunta ctx;
    ctx.encuesta = encuesta;
    ctx.inicio = encuesta->TopePreguntas;
    ctx.actual = ctx.inicio;
    ctx.posicion = 0;

    MenuOpcion opciones_medio[] = {
        {"Ver Pregunta", VerPregunta},
        {"Siguiente", SiguientePregunta},
        {"Anterior", AnteriorPregunta},
        {"Salir", NULL}
    };

    MenuOpcion opciones_inicio[] = {
        {"Ver Pregunta", VerPregunta},
        {"Siguiente", SiguientePregunta},
        {"Salir", NULL}
    };

    MenuOpcion opciones_final[] = {
        {"Ver Pregunta", VerPregunta},
        {"Anterior", AnteriorPregunta},
        {"Salir", NULL}
    };

    while (1) {
        system("cls");
        MostrarEncabezadoEncuesta(encuesta);

        int total = contarPreguntas(ctx.inicio);

        if (ctx.posicion == 0 && ctx.actual->sig != NULL) {
            menuG(opciones_inicio, 3, &ctx);
        } else if (ctx.actual->sig == NULL && ctx.posicion > 0) {
            menuG(opciones_final, 3, &ctx);
        } else {
            menuG(opciones_medio, 4, &ctx);
        }

        if (ctx.actual == NULL) break;
    }
}
