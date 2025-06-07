#ifndef PREGUNTA_H
#define PREGUNTA_H
#include "respuestas.h"


typedef struct Pregunta {
    int Encuesta_Id;
    int Pregunta_Id;
    char PreguntaTexto[100];
    float Ponderacion;
    Pregunta *sig; // Apunta a la siguiente pregunta
    Respuesta *TopeRespuestas; // Apunta a su lista de respuestas
} Pregunta;


void AgregarPregunta(Pregunta *lista, Pregunta nueva);
void MostrarPreguntas(Pregunta *lista);

#endif
