
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "respuestas.h"
#include "Menu_Generico.h"

int contarRespuestas(Respuesta *inicio) {
    if (!inicio) return 0;

    int count = 1;
    Respuesta *temp = inicio->sig;
    while (temp && temp != inicio) {
        count++;
        temp = temp->sig;
    }
    return count;
}

Respuesta* ObtenerRespuestaPorIndice(Respuesta *inicio, int indice) {
    if (!inicio) return NULL;

    Respuesta *actual = inicio;
    for (int i = 0; i < indice; i++) {
        actual = actual->sig;
        if (actual == inicio) break; // vuelta completa
    }
    return actual;
}

void printRespuestas(void *contexto) {
    NavegadorRespuestas *nav = (NavegadorRespuestas *)contexto;

    printf("\n==== PREGUNTA ==== ");
    printf("\nPregunta ID: %d", nav->actual->Pregunta_Id);
    printf("\nTexto: %s", nav->actual->RespuestaTexto);
    printf("\nRespuestas Totales: %d", contarRespuestas(nav->inicio));
    printf("\n----------------------------\n");

    Respuesta *r = nav->actual;
    if (r) {
        printf("\nRespuesta Actual: %s", r->RespuestaTexto);
    }
}

void VerRespuesta(void *contexto) {
    NavegadorRespuestas *nav = (NavegadorRespuestas *)contexto;
    Respuesta *r = nav->actual;

    if (r) {
        system("cls");
        printf("\n==== Detalles de la Respuesta ====");
        printf("\nID: %lld", r->Respuesta_Id);
        printf("\nTexto: %s", r->RespuestaTexto);
        printf("\nPonderación: %.2f", r->Ponderacion);
        printf("\n----------------------------------\n");
        system("pause");
    }
}

void salirDeRespuestas(void *contexto) {
    NavegadorRespuestas *nav = (NavegadorRespuestas *)contexto;
    nav->salir = 1;
}

void SiguienteRespuesta(void *contexto) {
    NavegadorRespuestas *nav = (NavegadorRespuestas *)contexto;
    if (nav->actual && nav->actual->sig)
        nav->actual = nav->actual->sig;
}

void AnteriorRespuesta(void *contexto) {
    NavegadorRespuestas *nav = (NavegadorRespuestas *)contexto;
    Respuesta *temp = nav->actual;
    if (!temp || !temp->sig) return;

    Respuesta *prev = temp;
    while (prev->sig != temp) {
        prev = prev->sig;
    }
    nav->actual = prev;
}

void menuRespuestas(Respuesta *lista) {
    if (!lista) {
        printf("\nEsta pregunta no tiene respuestas.");
        system("pause");
        return;
    }

    NavegadorRespuestas nav;
    nav.inicio = lista;
    nav.actual = lista;
    nav.posicion = 0;
    nav.salir = 0;

    while (!nav.salir) {
        MenuOpcion opciones[4];
        int cantidad = 0;
        int total = contarRespuestas(nav.inicio);

        if (nav.actual->sig == nav.inicio) {
            // Estamos en la última respuesta (solo podemos volver)
            opciones[cantidad++] = (MenuOpcion){"Anterior", AnteriorRespuesta};
        } else if (nav.actual == nav.inicio) {
            // Estamos en la primera respuesta (solo podemos avanzar)
            opciones[cantidad++] = (MenuOpcion){"Siguiente", SiguienteRespuesta};
        } else {
            // Estamos en el medio, podemos ir en ambas direcciones
            opciones[cantidad++] = (MenuOpcion){"Siguiente", SiguienteRespuesta};
            opciones[cantidad++] = (MenuOpcion){"Anterior", AnteriorRespuesta};
        }


        opciones[cantidad++] = (MenuOpcion){"Salir", salirDeRespuestas};

        menuG_con_encabezado(opciones, cantidad, &nav, printRespuestas);
    }
}
