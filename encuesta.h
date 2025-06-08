#ifndef ENCUESTA_H
#define ENCUESTA_H

#include "preguntas.h"

typedef struct Encuesta Encuesta;
typedef struct Pregunta Pregunta;

typedef struct Encuesta {
    int Encuesta_Id;
    char Denominacion[50];
    int Encuesta_Mes;
    int Anio;
    int Procesada; // 0: No procesada, 1: Procesada
    Encuesta *sig; // Apunta al siguiente en la pila
    Pregunta *TopePreguntas; // Apunta a su lista de preguntas
} Encuesta;

typedef struct {
    Encuesta *tope; // Apunta a la encuesta en el tope de la pila
} PilaEncuestas; // Creas la variable que apunte al tope en el main
// ej: PilaEncuestas Pila1;

typedef struct {
    PilaEncuestas *pila;
    PilaEncuestas *aux;
    Encuesta **dato;
    int salir;
} ContextoEncuesta;

void ApilarEncu(PilaEncuestas *pila, Encuesta *nueva);
Encuesta* DesapilarpEncu(PilaEncuestas *pila);
void VerPreguntas(void *contexto);
void printEncu(void *contexto);
void sig(void *contexto);
void ant(void *contexto);
void MostrarEncuesta(PilaEncuestas *pila);
void CargarEncuestaDePrueba(PilaEncuestas *pila);

#endif
