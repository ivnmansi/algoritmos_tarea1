/**
 * @file cocktail_shaker.c
 * @brief Desarrollo del algoritmo cocktail shaker sort
 */


#include "sorting.h"

/**
 * @brief Funcion que determina si dos deportistas deben ser intercambiados según el criterio y orden de ordenamiento.
 *
 * @param lef Deportista izquierdo.
 * @param right Deportista derecho.
 * @param criteria Criterio a utilizar para la comparacion.
 * @param order Orden de ordenamiento (ascendente o descendente).
 * @return int 1 si se deben intercambiar, 0 en caso contrario.
 */
static int should_swap(Deportista left, Deportista right, SortCriteria criteria, SortOrder order)
{
    int cmp = compare_by_criteria(left, right, criteria);

    if(order == ASCENDING){
        return cmp > 0; // SI left > right, entonces se debe intercambiar
    }

    return cmp < 0; // DESCENDING, Si left < right, entonces se debe intercambiar
}

void cocktail_shaker_sort(Deportista* array, int n, SortCriteria criteria, SortOrder order)
{
    if(array == NULL || n < 2){
        return;
    }

    int left = 0;
    int right = n - 1;
    int swapped = 1;

    while(swapped){
        swapped = 0;

        for(int i = left; i < right; i++){
            if(should_swap(array[i], array[i + 1], criteria, order)){
                swap_deportistas(&array[i], &array[i + 1]);
                swapped = 1;
            }
        }

        if(!swapped){
            break;
        }

        right--;
        swapped = 0;

        for(int i = right; i > left; i--){
            if(should_swap(array[i - 1], array[i], criteria, order)){
                swap_deportistas(&array[i - 1], &array[i]);
                swapped = 1;
            }
        }

        left++;
    }
}