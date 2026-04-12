#include "base.h"
#include "csv.h"
#include "sorting.h"

void runExperiment(){
    Deportista* arr = NULL;
    int n = 0;

    if(!loadDeportistasCSVArray(&arr, &n)){
        printf("No se pudo cargar CSV en arreglo.\n");
        return;
    }

    clock_t t0 = clock();
    cocktail_shaker_sort_desc(arr, n, SORT_BY_PUNTAJE);
    clock_t t1 = clock();

    double elapsed = (double)(t1 - t0) / CLOCKS_PER_SEC;
    printf("Elementos: %d\n", n);
    printf("Tiempo cocktail shaker: %.6f s\n", elapsed);

    int muestra = n < 10 ? n : 10;
    for(int i = 0; i < muestra; i++){
        printf("ID: %d | Nombre: %s | Equipo: %s | Puntaje: %.2f | Competencias: %d\n",
            arr[i]->ID, arr[i]->Nombre, arr[i]->Equipo, arr[i]->Puntaje, arr[i]->Competencias);
    }

    freeDeportistasArray(arr, n);
}

