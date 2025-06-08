#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encuesta.h"
#include "preguntas.h"
#include "Menu_Generico.h"


void ApilarEncu(PilaEncuestas *pila, Encuesta *nueva) {
    Encuesta *nuevo = malloc(sizeof(Encuesta));
    if(nuevo == NULL) return;

    nuevo->Encuesta_Id = nueva->Encuesta_Id;
    nuevo->Anio = nueva->Anio;
    nuevo->Encuesta_Mes = nueva->Encuesta_Mes;
    strcpy(nuevo->Denominacion, nueva->Denominacion);
    nuevo->Procesada = nueva->Procesada;

    nuevo->TopePreguntas = nueva->TopePreguntas;

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
    }
    else
    {
    	temporal = NULL;
	}
	return temporal;
}

void IngresarEncuesta(void *contexto) {
    Encuesta *encuesta = ((ContextoEncuesta *) contexto)->dato;


    if (!encuesta || !encuesta->TopePreguntas) {
        printf("Esta encuesta no tiene preguntas.\n");
        system("pause");
        return;
    }

    menuPreguntas(encuesta);
}

void printEncu(void *contexto) {
    ContextoEncuesta *ctx = (ContextoEncuesta *)contexto;
    Encuesta *dato = ctx->dato;

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
    ContextoEncuesta ctx = {pila, &aux, dato, 0};

    while (ctx.salir != 1) {
        system("cls");

        // Imprimir encabezado antes del menú
        printEncu(&ctx);

        MenuOpcion opciones[4];
        int cantidad = 0;

        opciones[cantidad++] = (MenuOpcion){"Ingresar a la Encuesta", IngresarEncuesta};

        if (aux.tope == NULL && pila->tope != NULL) {
            opciones[cantidad++] = (MenuOpcion){"Siguiente", sig};
        } else if (aux.tope != NULL && pila->tope != NULL) {
            opciones[cantidad++] = (MenuOpcion){"Siguiente", sig};
            opciones[cantidad++] = (MenuOpcion){"Anterior", ant};
        } else if (pila->tope == NULL && aux.tope != NULL) {
            opciones[cantidad++] = (MenuOpcion){"Anterior", ant};
        }

        opciones[cantidad++] = (MenuOpcion){"Salir", salirDeEncuesta};
        // Usamos el nuevo menú con encabezado
        menuG_con_encabezado(opciones, cantidad, &ctx, (void (*)(void *))printEncu);
        // Verificamos si se debe salir
        if (pila->tope == NULL && aux.tope == NULL)
            break;
	}

	    // Restaurar pila original si saliste antes del final
	    ApilarEncu(&aux, dato);
	    while (aux.tope != NULL) {
	        Encuesta *e = DesapilarpEncu(&aux);
	        ApilarEncu(pila, e);
    }
}



void CargarEncuestaDePrueba(PilaEncuestas *pila) {
    Encuesta *e = (Encuesta*)malloc(sizeof(Encuesta));
    if (!e) return;

    e->Encuesta_Id = 1;
    strcpy(e->Denominacion, "Encuesta de Satisfacción");
    e->Encuesta_Mes = 6;
    e->Anio = 2025;
    e->Procesada = 0;
    e->sig = NULL;
    e->TopePreguntas = NULL;

    // Crear preguntas
    Pregunta *p1 = (Pregunta*)malloc(sizeof(Pregunta));
    p1->Pregunta_Id = 101;
    strcpy(p1->PreguntaTexto, "¿Cómo calificaría nuestro servicio?");
    p1->Ponderacion = 1.0f;
    p1->TopeRespuestas = NULL;
    p1->sig = NULL;

    Pregunta *p2 = (Pregunta*)malloc(sizeof(Pregunta));
    p2->Pregunta_Id = 102;
    strcpy(p2->PreguntaTexto, "¿Nos recomendaría?");
    p2->Ponderacion = 1.0f;
    p2->TopeRespuestas = NULL;
    p2->sig = NULL;

    // Crear respuestas
    Respuesta *r1 = (Respuesta*)malloc(sizeof(Respuesta));
    r1->Respuesta_Id = 1;
    r1->Pregunta_Id = 101;
    r1->Respuesta_Nro = 1;
    strcpy(r1->RespuestaTexto, "Excelente");
    r1->Ponderacion = 5;
    r1->sig = r1;  // circular

    Respuesta *r2 = (Respuesta*)malloc(sizeof(Respuesta));
    r2->Respuesta_Id = 2;
    r2->Pregunta_Id = 101;
    r2->Respuesta_Nro = 2;
    strcpy(r2->RespuestaTexto, "Bueno");
    r2->Ponderacion = 4;
    r2->sig = r1;
    r1->sig = r2;

    Respuesta *r3 = (Respuesta*)malloc(sizeof(Respuesta));
    r3->Respuesta_Id = 3;
    r3->Pregunta_Id = 101;
    r3->Respuesta_Nro = 3;
    strcpy(r3->RespuestaTexto, "Regular");
    r3->Ponderacion = 3;
    r3->sig = r1;
    r2->sig = r3;

    p1->TopeRespuestas = r1;

    // Segunda pregunta
    Respuesta *r4 = (Respuesta*)malloc(sizeof(Respuesta));
    r4->Respuesta_Id = 1;
    r4->Pregunta_Id = 102;
    r4->Respuesta_Nro = 1;
    strcpy(r4->RespuestaTexto, "Sí");
    r4->Ponderacion = 1;
    r4->sig = r4;

    Respuesta *r5 = (Respuesta*)malloc(sizeof(Respuesta));
    r5->Respuesta_Id = 2;
    r5->Pregunta_Id = 102;
    r5->Respuesta_Nro = 2;
    strcpy(r5->RespuestaTexto, "No");
    r5->Ponderacion = 0;
    r5->sig = r4;
    r4->sig = r5;

    p2->TopeRespuestas = r4;

    // Agregar preguntas a la encuesta (lista simple)
    p1->sig = p2;
    p2->sig = NULL;
    e->TopePreguntas = p1;

    // Apilar la encuesta
    ApilarEncu(pila, e);
    system("chcp 65001 > nul");
}