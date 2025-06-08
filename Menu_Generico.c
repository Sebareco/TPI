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

void salirDeEncuesta(void *ctx) {
	((ContextoEncuesta*)ctx)->salir = 1;
}

void menuG_con_encabezado(MenuOpcion opciones[], int cantidad, void *contexto, void (*printEncabezado)(void *)) {
    int posicion = 0, tecla;

    while (1) {
        system("cls");

        // Imprime encabezado personalizado
        if (printEncabezado)
            printEncabezado(contexto);

        printf("==== OPCIONES ====\n\n");
        for (int i = 0; i < cantidad; i++) {
            if (i == posicion)
                printf("-> %s\n", opciones[i].texto);
            else
                printf("   %s\n", opciones[i].texto);
        }

        tecla = getch();
        if (tecla == 224) {
            tecla = getch();
            if (tecla == 72) posicion = (posicion - 1 + cantidad) % cantidad;
            if (tecla == 80) posicion = (posicion + 1) % cantidad;
        }else if (tecla == 13) {
		    if (_stricmp(opciones[posicion].texto, "Salir") == 0) {
		        if (opciones[posicion].accion)
		            opciones[posicion].accion(contexto);
		        break; // salir del menú
		    }
		    else if (_stricmp(opciones[posicion].texto, "Siguiente") == 0) {
		        if (opciones[posicion].accion)
		            opciones[posicion].accion(contexto);
		        break; // volver al bucle principal para reconstruir menú
		    }
		    else if (_stricmp(opciones[posicion].texto, "Anterior") == 0) {
		        if (opciones[posicion].accion)
		            opciones[posicion].accion(contexto);
		        break; // también salimos para reconstruir
		    }
		    else if (opciones[posicion].accion) {
		        opciones[posicion].accion(contexto); // Ver pregunta, etc.
		    }
		}
	}
}
