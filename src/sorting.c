#include "sorting.h"

/**
 * @brief Compara dos deportistas según un criterio de ordenamiento.
 *
 * @param left Deportista izquierdo.
 * @param right Deportista derecho.
 * @param criteria Criterio a utilizar para la comparacion.
 * @return int Resultado de la comparacion: -1 si left < right, 1 si left > right, 0 si son iguales.
 */
int compare_by_criteria(Deportista left, Deportista right, SortCriteria criteria)
{
    switch(criteria){
        case SORT_BY_PUNTAJE:
            if(left->Puntaje < right->Puntaje) return -1;
            if(left->Puntaje > right->Puntaje) return 1;
            return 0;

        case SORT_BY_ID:
            if(left->ID < right->ID) return -1;
            if(left->ID > right->ID) return 1;
            return 0;

        case SORT_BY_COMPETENCIAS:
            if(left->Competencias < right->Competencias) return -1;
            if(left->Competencias > right->Competencias) return 1;
            return 0;

        case SORT_BY_NOMBRE:
            return strcmp(left->Nombre, right->Nombre);

        case SORT_BY_EQUIPO:
            return strcmp(left->Equipo, right->Equipo);

        default:
            return 0;
    }
}