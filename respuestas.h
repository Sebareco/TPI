#ifndef RESPUESTA_H
#define RESPUESTA_H

typedef struct Respuesta {
    int Respuesta_Id;
    int Pregunta_Id;
    int Respuesta_Nro;
    char RespuestaTexto[50];
    float Ponderacion;
    int Elegida;
    struct Respuesta *sig; // Lista circular
} Respuesta;


void AgregarRespuesta(Respuesta *lista, Respuesta nueva);
void MostrarRespuestas(Respuesta lista);

#endif
