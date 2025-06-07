#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "respuestas.h"
#include "Menu_Generico.h"

int contarRespuestas(Respuesta *inicio) {
    if (inicio == NULL) return 0;
    int count = 1;
    Respuesta *r = inicio->sig;
    while (r != NULL && r != inicio) {
        count++;
        r = r->sig;
    }
    return count;
}

Respuesta* obtenerAnterior(Respuesta *inicio, Respuesta *actual) {
    if (inicio == NULL || actual == NULL) return NULL;
    Respuesta *r = inicio;
    while (r->sig != actual && r->sig != inicio) {
        r = r->sig;
    }
    return r;
}

void VerRespuesta(void *contexto) {
    NavegadorRespuestas *ctx = (NavegadorRespuestas *) contexto;
    Respuesta *r = ctx->actual;

    if (r != NULL) {
        printf("=== Respuesta %d ===\n", ctx->posicion + 1);
        printf("ID: %lld\n", r->Respuesta_Id);
        printf("Texto: %s\n", r->RespuestaTexto);
        printf("Nro: %d\n", r->Respuesta_Nro);
        printf("Ponderación: %.2f\n", r->Ponderacion);
        printf("----------------------\n");
        system("pause");
    }
}

void SiguienteRespuesta(void *contexto) {
    NavegadorRespuestas *ctx = (NavegadorRespuestas *)contexto;
    if (ctx->actual != NULL) {
        ctx->actual = ctx->actual->sig;
        ctx->posicion = (ctx->posicion + 1) % contarRespuestas(ctx->inicio);
    }
}

void AnteriorRespuesta(void *contexto) {
    NavegadorRespuestas *ctx = (NavegadorRespuestas *)contexto;
    Respuesta *prev = obtenerAnterior(ctx->inicio, ctx->actual);
    if (prev != NULL) {
        ctx->actual = prev;
        ctx->posicion = (ctx->posicion - 1 + contarRespuestas(ctx->inicio)) % contarRespuestas(ctx->inicio);
    }
}

void menuRespuestas(Respuesta *inicio) {
    if (inicio == NULL) {
        printf("No hay respuestas para esta pregunta.\n");
        system("pause");
        return;
    }

    NavegadorRespuestas ctx = {inicio, inicio, 0};

    MenuOpcion opciones[] = {
        {"Ver Respuesta", VerRespuesta},
        {"Siguiente", SiguienteRespuesta},
        {"Anterior", AnteriorRespuesta},
        {"Salir", NULL}
    };

    while (1) {
        system("cls");
        printf("=== Navegador de Respuestas ===\n");
        printf("Posición actual: %d\n\n", ctx.posicion + 1);
        menuG(opciones, 4, &ctx);
        if (ctx.actual == NULL) break;
    }
}