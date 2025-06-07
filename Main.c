#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "encuesta.h"
#include "preguntas.h"
#include "respuestas.h"
#include "Menu_Generico.h"

// Crea una respuesta
Respuesta* crearRespuesta(int id, const char *texto, double valor) {
    Respuesta *r = (Respuesta*)malloc(sizeof(Respuesta));
    if (!r) return NULL;
    r->Respuesta_Id = id;
    strcpy(r->RespuestaTexto, texto);
    r->Ponderacion = valor;
    r->sig = NULL;
    return r;
}

// Agrega una respuesta circularmente
void agregarRespuesta(Pregunta *preg, Respuesta *nueva) {
    if (!preg->TopeRespuestas) {
        preg->TopeRespuestas = nueva;
        nueva->sig = nueva;
    } else {
        Respuesta *temp = preg->TopeRespuestas;
        while (temp->sig != preg->TopeRespuestas)
            temp = temp->sig;
        temp->sig = nueva;
        nueva->sig = preg->TopeRespuestas;
    }
}

// Crea una pregunta
Pregunta* crearPregunta(int id, const char *texto) {
    Pregunta *p = (Pregunta*)malloc(sizeof(Pregunta));
    if (!p) return NULL;
    p->Pregunta_Id = id;
    strcpy(p->PreguntaTexto, texto);
    p->TopeRespuestas = NULL;
    p->sig = NULL;
    return p;
}

// Agrega una pregunta al inicio
void agregarPregunta(Encuesta *enc, Pregunta *nueva) {
    nueva->sig = enc->TopePreguntas;
    enc->TopePreguntas = nueva;
}

// Crea una encuesta completa
Encuesta* crearEncuesta() {
    Encuesta *e = (Encuesta*)malloc(sizeof(Encuesta));
    e->Encuesta_Id = 1;
    e->Anio = 2025;
    e->Encuesta_Mes = 6;
    strcpy(e->Denominacion, "Encuesta de Satisfacción");
    e->Procesada = 0;
    e->TopePreguntas = NULL;

    Pregunta *p1 = crearPregunta(101, "¿Cómo calificaría nuestro servicio?");
    agregarRespuesta(p1, crearRespuesta(1, "Excelente", 5.0));
    agregarRespuesta(p1, crearRespuesta(2, "Bueno", 4.0));
    agregarRespuesta(p1, crearRespuesta(3, "Regular", 3.0));

    Pregunta *p2 = crearPregunta(102, "¿Nos recomendaría?");
    agregarRespuesta(p2, crearRespuesta(1, "Sí", 1.0));
    agregarRespuesta(p2, crearRespuesta(2, "No", 0.0));

    agregarPregunta(e, p2);
    agregarPregunta(e, p1);

    return e;
}

void VerEncuestas(void *contexto) {
    PilaEncuestas *pila = (PilaEncuestas *)contexto;
    MostrarEncuesta(pila);
}

void menuPrincipal(PilaEncuestas *pila) {
    MenuOpcion opciones[] = {
        {"Ver Encuestas", VerEncuestas},
        {"Salir", NULL}
    };
    int cantidad = sizeof(opciones) / sizeof(opciones[0]);

    menuG(opciones, cantidad, pila);
}

int main() {
    PilaEncuestas pila = { NULL };
    CargarEncuestaDePrueba(&pila); // esta función la que armamos con preguntas y respuestas

    menuPrincipal(&pila);

    return 0;
}
