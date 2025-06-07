#ifndef RESPUESTA_H
#define RESPUESTA_H

struct Respuesta;

typedef struct Respuesta {
    long long Respuesta_Id;
    int Pregunta_Id;
    int Respuesta_Nro;
    char RespuestaTexto[50];
    float Ponderacion;
    struct Respuesta *sig; // Lista circular
} Respuesta;

typedef struct {
    Respuesta *inicio;
    Respuesta *actual;
    int posicion;
} NavegadorRespuestas;

// Funciones para mostrar respuestas (modo visual)
void menuRespuestas(Respuesta *inicio);
void VerRespuesta(void *contexto);
void SiguienteRespuesta(void *contexto);
void AnteriorRespuesta(void *contexto);

// Funciones auxiliares
int contarRespuestas(Respuesta *inicio);
Respuesta* obtenerAnterior(Respuesta *inicio, Respuesta *actual);

// Gestión de nodos (opcional si ya existen)
void AgregarRespuesta(Respuesta *lista, Respuesta nueva);
void MostrarRespuestas(Respuesta *lista);
#endif
