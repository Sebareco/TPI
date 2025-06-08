#ifndef RESPUESTA_H
#define RESPUESTA_H

typedef struct Pregunta Pregunta;
typedef struct Respuesta Respuesta;

typedef struct Respuesta {
    long long Respuesta_Id;
    int Pregunta_Id;
    int Respuesta_Nro;
    char RespuestaTexto[50];
    float Ponderacion;
    Respuesta *sig;
} Respuesta;

typedef struct {
    Respuesta *inicio;
    Respuesta *actual;
    int posicion;
    int salir;
} NavegadorRespuestas;

int contarRespuestas(Respuesta *inicio);
Respuesta* obtenerAnterior(Respuesta *inicio, Respuesta *actual);
void VerRespuesta(void *contexto);
void SiguienteRespuesta(void *contexto);
void AnteriorRespuesta(void *contexto);
void menuRespuestas(Respuesta *inicio);

#endif
