#ifndef CSV_H
#define CSV_H
#include "encuesta.h"

typedef struct csv
{
    int ID_Encuesta;
    int ID_Pregunta;
    long long ID_Respuesta;
    int Fec_Realizo_Enc;
    int Encuestador;
    long long ID_Enc_Resp;
    csv *izquierda;
    csv *derecha;
}csv;

typedef struct 
{
    csv *Raiz;
}Arbol;

void insertarArbol(Arbol *R);

#endif