#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encuesta.h"
#include "preguntas.h"
#include "Menu_Generico.h"


void ApilarEncu(PilaEncuestas *pila, Encuesta *nueva)
{
    Encuesta *nuevo = malloc(sizeof(Encuesta));
    if(nuevo == NULL)
    {
        printf("No hay espacio en memoria! \n");
        return;
    }
    nuevo->Encuesta_Id = nueva->Encuesta_Id;
    nuevo->Anio = nueva->Anio;
    nuevo->Encuesta_Mes = nueva->Encuesta_Mes;
    strcpy(nuevo->Denominacion, nueva->Denominacion);
    nuevo->Procesada = nueva->Procesada;

    nuevo->sig = pila->tope;
    pila->tope = nuevo;
}
Encuesta* DesapilarpEncu(PilaEncuestas *pila)
{
	Encuesta *temporal;
    if(pila->tope != NULL)
    {
        temporal = pila->tope;
    	pila->tope = pila->tope->sig;
    	free(temporal);
    }
    else
    {
    	temporal = NULL;
	}
	return temporal;
}

void VerPreguntas(void *contexto) {
    Encuesta *encuesta = (Encuesta *) contexto;

    if (!encuesta || !encuesta->TopePreguntas) {
        printf("Esta encuesta no tiene preguntas.\n");
        system("pause");
        return;
    }

    menuPreguntas(encuesta);
}

void printEncu(void *contexto) {
    ContextoEncuesta *ctx = (ContextoEncuesta *)contexto;
    Encuesta *dato = *(ctx->dato);

    if (dato != NULL) {
        printf("ID: %d\n", dato->Encuesta_Id);
        printf("Nombre: %s\n", dato->Denominacion);
        printf("Estado: %s\n\n", dato->Procesada ? "PROCESADA" : "NO PROCESADA");
    }
}

void sig(void *contexto) {
    ContextoEncuesta *ctx = (ContextoEncuesta *)contexto;
    ApilarEncu(ctx->aux, *(ctx->dato));
    *(ctx->dato) = DesapilarpEncu(ctx->pila);
}

void ant(void *contexto) {
    ContextoEncuesta *ctx = (ContextoEncuesta *)contexto;
    ApilarEncu(ctx->pila, *(ctx->dato));
    *(ctx->dato) = DesapilarpEncu(ctx->aux);
}



void MostrarEncuesta(PilaEncuestas *pila)
{
    if (pila == NULL || pila->tope == NULL) {
        printf("No hay encuestas disponibles.\n");
        return;
    }

    PilaEncuestas aux = {NULL};
    Encuesta *dato = DesapilarpEncu(pila);
    ContextoEncuesta ctx = {pila, &aux, &dato};

    while (1) {
        system("cls");
        printEncu(&ctx);

        if (aux.tope == NULL) {
            MenuOpcion opciones[] = {
                {"Ver preguntas", VerPreguntas},
                {"Siguiente", sig},
                {"Salir", NULL}
            };
            menuG(opciones, 2, &ctx);
        }
        else if (aux.tope != NULL && pila->tope != NULL) {
            MenuOpcion opciones[] = {
                {"Ver preguntas", VerPreguntas},
                {"Siguiente", sig},
                {"Anterior", ant},
                {"Salir", NULL}
            };
            menuG(opciones, 3, &ctx);
        }
        else if (pila->tope == NULL) {
            MenuOpcion opciones[] = {
                {"Ver preguntas", VerPreguntas},
                {"Anterior", ant},
                {"Salir", NULL}
            };
            menuG(opciones, 2, &ctx);
        } else break;
    }

    // Restaurar pila original si saliste antes del final
    ApilarEncu(&aux, dato);
    while (aux.tope != NULL) {
        Encuesta *e = DesapilarpEncu(&aux);
        ApilarEncu(pila, e);
    }
}