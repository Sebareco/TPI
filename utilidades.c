#include <stdio.h>
#include <string.h>

int contarCifras(long long valor) {
    int cifras = 0;
    while (valor > 0) {
        valor /= 10;
        cifras++;
    }
    return cifras;
}

void verificar(void* dato, int tipo) {
    switch(tipo) {
        case 1: { // int
            int valor = *(int*)dato;
            if (valor >= 0 && valor <= 1000) {
                printf("Entero válido: %d\n", valor);
            } else {
                printf("Entero inválido: %d\n", valor);
            }
            break;
        }
        case 2: { // float
            float valor = *(float*)dato;
            if (valor >= 0.0f && valor <= 10000.0f) {
                printf("Flotante válido: %.2f\n", valor);
            } else {
                printf("Flotante inválido: %.2f\n", valor);
            }
            break;
        }
        case 3: { // string
            char* texto = (char*)dato;
            if (strlen(texto) > 0) {
                printf("Cadena válida: %s\n", texto);
            } else {
                printf("Cadena vacía\n");
            }
            break;
        }
        case 4: { // long long
            long long valor = *(long long*)dato;
            if(contarCifras(valor) == 12)
            {
                printf("LONG LONG VALIDO");
            }
            else
            {
                printf("LONG LONG INVALIDO");
            }
        }
        default:
            printf("Tipo no reconocido\n");
    }
}
