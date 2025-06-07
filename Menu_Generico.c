#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include "Menu_Generico.h"
#include "encuesta.h"

int Salir(const char *texto)
{
    return (_stricmp(texto, "Salir") == 0 || _stricmp(texto, "Volver") == 0);
}

int leerTecla() {
    return getch();
}

void printMenu(MenuOpcion opciones[], int cantidad, int seleccion) 
{
    for (int i = 0; i < cantidad; i++) 
	{
        if (i == seleccion)
            printf("-> %s\n", opciones[i].texto);
        else
            printf("   %s\n", opciones[i].texto);
    }
}

void menuG(MenuOpcion opciones[], int cantidad, void *contexto) 
{
    int posicion = 0, tecla;

    while (1) 
	{
        system("cls");  // Limpiar pantalla usando comandos ANSI
        printf("==== MENU ====\n\n");
        printMenu(opciones, cantidad, posicion);

        tecla = leerTecla();

        if (tecla == 224) 
		{
            tecla = leerTecla();
            switch (tecla) 
			{
                case 72: posicion = (posicion - 1 + cantidad) % cantidad; break;
                case 80: posicion = (posicion + 1) % cantidad; break;
            }
        } 
		else if (tecla == 13) 
		{
            if (opciones[posicion].accion)
                opciones[posicion].accion(contexto);
            else if (Salir(opciones[posicion].texto)) 
                break; // opción Salir
        }
    }
}


// ====================== ENCUESTAS ============================== \\



void printEncu(Encuesta *dato)
{
    if(dato != NULL)
    {
        printf("- ID: %s", dato->Encuesta_Id);
        printf("- Nombre %s", dato->Denominacion);
        printf("- Estado: %s", dato->Procesada ? "PROCESADA" : "NO PROCESADA");
    }
}



void menuEncu(MenuOpcion opciones[], int cantidad, void *contexto, PilaEncuestas *pila, PilaEncuestas *aux) 
{
    int posicion = 0, tecla;
    while (1) 
	{
        system("cls");  // Limpiar pantalla usando comandos ANSI
        printf("==== ENCUESTA ====\n\n");
        printEncu(&contexto);
        printMenu(opciones, cantidad, posicion);

        tecla = leerTecla();

        if (tecla == 224) 
        {
            tecla = leerTecla();
            switch (tecla) 
            {
                case 72: posicion = (posicion - 1 + cantidad) % cantidad; break;
                case 80: posicion = (posicion + 1) % cantidad; break;
            }
        } 
        else if (tecla == 13) 
        {
            if (opciones[posicion].accion)
                opciones[posicion].accion(contexto);
            else if (Salir(opciones[posicion].texto))
            Sleep(3000);
            printf("Volviendo al menu...");
        }
    }
}