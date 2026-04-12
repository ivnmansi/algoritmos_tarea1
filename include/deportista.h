/**
 * @file deportista.h
 * @brief
 *
 */

#ifndef DEPORTISTA_H
#define DEPORTISTA_H

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Estructura que representa a un deportista
*/
typedef struct {
    int ID;
    char* Nombre;
    char* Equipo;
    float Puntaje;
    int Competencias;
} Deportista_;
typedef Deportista_* Deportista;

Deportista createDeportista(int id, char* nombre, char* equipo, float puntaje, int competencias);
void deleteDeportista(Deportista deportista);
void print_deportista(Deportista deportista);
void swap_deportistas(Deportista* a, Deportista* b);

#endif