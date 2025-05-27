#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "encuesta.h"


void ApilarEncu(PilaEncuestas *pila, Encuesta nueva)
{
    Encuesta *nuevo = malloc(sizeof(Encuesta));
    if(nuevo == NULL)
    {
        printf("No hay espacio en memoria! \n");
        return;
    }
    nuevo->Encuesta_Id = nueva.Encuesta_Id;
    nuevo->Anio = nueva.Anio;
    nuevo->Encuesta_Mes = nueva.Encuesta_Mes;
    strcpy(nuevo->Denominacion, nueva.Denominacion);
    nuevo->Procesada = nueva.Procesada;
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
void MostrarEncuestas(PilaEncuestas pila)
{
    
}
