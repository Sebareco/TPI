#include <stdio.h>
#include <stdlib.h>
#include "csv.h"

csv* PedidoCsv()
{
    FILE *csv = fopen("CSVS.csv", "r");
    if(csv != NULL)
    {
        
    }    
}

csv* PedidoTesteo() { // A mano
    csv* Dato = NULL;

    Dato = (csv*)malloc(sizeof(csv));
    if (Dato == NULL) {
        printf("Error al asignar memoria.\n");
    } else {
        printf("Ingrese los siguientes datos:");
        printf("\n-----------------------------");

        printf("\nID de la encuesta: ");
        scanf("%d", &Dato->ID_Encuesta);

        printf("\nID de la pregunta: ");
        scanf("%d", &Dato->ID_Pregunta);

        printf("\nID de la respuesta: ");
        scanf("%lld", &Dato->ID_Respuesta);

        printf("\nFecha en que se realizó la encuesta (AAAAMMDD): ");
        scanf("%d", &Dato->Fec_Realizo_Enc);

        printf("\nID del encuestador: ");
        scanf("%d", &Dato->Encuestador);

        printf("\nNumero de respuesta: ");
        scanf("%lf", &Dato->ID_Enc_Resp);

        Dato->izquierda = NULL;
        Dato->derecha = NULL;
    }

    return Dato;
}



csv* insertarCSV(csv* raiz, csv* nuevo) {
    csv* resultado = raiz;
  
    if (raiz == NULL) {
        resultado = nuevo;
    } else if (nuevo->ID_Enc_Resp < raiz->ID_Enc_Resp) {
        raiz->izquierda = insertarCSV(raiz->izquierda, nuevo);
    } else if (nuevo->ID_Enc_Resp > raiz->ID_Enc_Resp) {
        raiz->derecha = insertarCSV(raiz->derecha, nuevo);
    }
    // Si son iguales, no insertamos (puede cambiarse si querés permitir duplicados)

    return resultado;
}

void InsertarArbol(Arbol *R) {
    csv* nuevo = PedidoTesteo();
    if (nuevo != NULL) {
        R->Raiz = insertarCSV(R->Raiz, nuevo); // Usando tu función insertarCSV que compara por ID_Encuesta
    }
}
