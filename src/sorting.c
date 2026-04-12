#include "sorting.h"

void swap_deportistas(Deportista* a, Deportista* b){
    Deportista tmp = *a;
    *a = *b;
    *b = tmp;
}