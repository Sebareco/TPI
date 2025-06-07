#include <stdio.h>
#include <stdlib.h>
#include "encuesta.h"
#include "preguntas.h"
#include "Menu_Generico.h"


void ApilarEncu(PilaEncuestas *pila, Encuesta *nueva)
{
    Encuesta *nuevo = malloc(sizeof(Encuesta));
    if(nuevo == NULL)
    {
        printf("No hay espacio en memoria! \n");
        return;
    }
    nuevo->Encuesta_Id = nueva->Encuesta_Id;
    nuevo->Anio = nueva->Anio;
    nuevo->Encuesta_Mes = nueva->Encuesta_Mes;
    strcpy(nuevo->Denominacion, nueva->Denominacion);
    nuevo->Procesada = nueva->Procesada;

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
    	free(temporal);
    }
    else
    {
    	temporal = NULL;
	}
	return temporal;
}

void sig(PilaEncuestas *pila, PilaEncuestas *aux, Encuesta *dato)
{
    ApilarEncu(&aux, dato);
    dato = DesapilarpEncu(&pila);
}

void ant(PilaEncuestas *pila, PilaEncuestas *aux, Encuesta *dato)
{
    ApilarEncu(&pila, dato);
    dato = DesapilarpEncu(&aux);
}

void salir()
{

}


void MostrarEncuesta(PilaEncuestas *pila)
{
    if(pila->tope != NULL)
    {
        Encuesta *dato;
        PilaEncuestas *aux;
        dato = DesapilarpEncu(&pila);
        while(1){
            if(aux->tope == NULL)
            {
                MenuOpcion Encuesta [] =
                {
                    {"Ver Encuestas", NULL},
                    {"Siguiente", sig},
                    {"Salir", NULL}
                };
                int cantidadOpciones = sizeof(Encuesta) / sizeof(Encuesta[0]);
                menuEncu(Encuesta, cantidadOpciones, &dato, &pila, &aux);
            }
            else if(aux->tope != NULL && pila->tope != NULL)
            {
                MenuOpcion Encuesta [] =
                {
                    {"Ver Encuestas", NULL},
                    {"Siguiente", sig},
                    {"Anterior", ant},
                    {"Salir", NULL}
                };
                int cantidadOpciones = sizeof(Encuesta) / sizeof(Encuesta[0]);
                menuEncu(Encuesta, cantidadOpciones, &dato, &pila, &aux);
            }
            else if(pila->tope == NULL)
            {
                MenuOpcion Encuesta [] =
                {
                    {"Ver Encuestas", NULL},
                    {"Anterior", ant},
                    {"Salir", NULL}
                };
                int cantidadOpciones = sizeof(Encuesta) / sizeof(Encuesta[0]);
                menuEncu(Encuesta, cantidadOpciones, &dato, &pila, &aux);
            }
        }
    }
}