#ifndef CSV_H
#define CSV_H

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include "linked_list.h"



int loadDeportistasCSVArray(Deportista** outArray, int* outCount);
void freeDeportistasArray(Deportista* array, int count);


#endif