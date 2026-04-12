/**
 * @file deportista.c
 * @brief
 *
 */

#include "deportista.h"

Deportista createDeportista(int id, char* nombre, char* equipo, float puntaje, int competencias){
    Deportista newDeportista = malloc(sizeof(Deportista_));
    if(newDeportista == NULL){
        return NULL;
    }
    newDeportista->ID = id;
    newDeportista->Nombre = nombre;
    newDeportista->Equipo = equipo;
    newDeportista->Puntaje = puntaje;
    newDeportista->Competencias = competencias;

    return newDeportista;
}

void deleteDeportista(Deportista deportista){
    free(deportista->Nombre);
    free(deportista->Equipo);
    free(deportista);
}

/**
 * @brief Imprime un deportista.
 *
 * @param deportista Deportista a imprimir.
 */
void print_deportista(Deportista deportista)
{
    if(deportista == NULL){
        return;
    }

    printf("ID: %d | Nombre: %s | Equipo: %s | Puntaje: %.2f | Competencias: %d\n",
        deportista->ID,
        deportista->Nombre,
        deportista->Equipo,
        deportista->Puntaje,
        deportista->Competencias);
}

void swap_deportistas(Deportista* a, Deportista* b){
    Deportista tmp = *a;
    *a = *b;
    *b = tmp;
}