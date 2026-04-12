/**
 * @file insertion_sort.c
 * @brief Implementacion de insertion sort para deportistas.
 */

#include "sorting.h"

/**
 * @brief Funcion que utiliza insertion sort para ordenar un arreglo de deportistas segun un criterio y orden de ordenamiento.
 *
 * @param deportistas Arreglo de deportistas a ordenar.
 * @param length Largo del arreglo.
 * @param criteria Criterio a utilizar para la comparacion.
 * @param order Orden de ordenamiento (ascendente o descendente).
 */
void insertion_sort_deportistas(Deportista *deportistas, int length, SortCriteria criteria, SortOrder order)
{
    if(deportistas == NULL || length < 2){
        return;
    }

    for(int i = 1; i < length; i++){
        Deportista key = deportistas[i];
        int j = i - 1;

        while(j >= 0){
            int cmp = compare_by_criteria(deportistas[j], key, criteria);

            int should_shift;
            if(order == ASCENDING){
                should_shift = (cmp > 0);
            }
            else {
                should_shift = (cmp < 0);
            }

            if(!should_shift){
                break;
            }

            deportistas[j + 1] = deportistas[j];
            j--;
        }

        deportistas[j + 1] = key;
    }
}
