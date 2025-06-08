#ifndef PREGUNTA_H
#define PREGUNTA_H
#include "encuesta.h"
#include "respuestas.h"

typedef struct Encuesta Encuesta;
typedef struct Pregunta Pregunta;
typedef struct Respuesta Respuesta;

typedef struct Pregunta {
    int Encuesta_Id;
    int Pregunta_Id;
    char PreguntaTexto[100];
    float Ponderacion;
    Pregunta *sig; // Apunta a la siguiente pregunta
    Respuesta *TopeRespuestas; // Apunta a su lista de respuestas
} Pregunta;

typedef struct {
    Pregunta *inicio;
    Pregunta *actual;
    int posicion;
    Encuesta *encuesta;
    int salir;
} ContextoPregunta;


int contarPreguntas(Pregunta *inicio);
Pregunta* ObtenerPreguntaPorIndice(Pregunta *inicio, int indice);
void MostrarEncabezadoEncuesta(Encuesta *e);
void VerPregunta(void *contexto);
void VerRespuestas(void *contexto);
void SiguientePregunta(void *contexto);
void AnteriorPregunta(void *contexto);
void menuPreguntas(Encuesta *encuesta);


#endif
