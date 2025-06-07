#ifndef PREGUNTA_H
#define PREGUNTA_H
#include "respuestas.h"

struct Encuesta;
struct Pregunta;

typedef struct Pregunta {
    int Encuesta_Id;
    int Pregunta_Id;
    char PreguntaTexto[100];
    float Ponderacion;
    struct Pregunta *sig; // Apunta a la siguiente pregunta
    struct Respuesta *TopeRespuestas; // Apunta a su lista de respuestas
} Pregunta;

typedef struct {
    Pregunta *inicio;
    Pregunta *actual;
    int posicion;
    struct Encuesta *encuesta;
} ContextoPregunta;

void menuPreguntas(Encuesta *encuesta);
void VerPreguntas(Encuesta *encuesta);
int contarPreguntas(Pregunta *inicio);
Pregunta* ObtenerPreguntaPorIndice(Pregunta *inicio, int indice);

void AgregarRespuesta(Respuesta *lista, Respuesta nueva);
void MostrarRespuestas(Respuesta *lista);


#endif
