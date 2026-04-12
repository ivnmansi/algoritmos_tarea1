/**
 * @file run_experiment.c
 * @brief Operaciones de ordenamiento, búsqueda y ranking.
 */

#include "base.h"
#include "csv.h"
#include "sorting.h"
#include "print_format.h"
#include <stdio.h>


void printDeportistasArray(Deportista *deportistas, int rankingAmount){
    for(int i = 0; i < rankingAmount; i++){
        print_deportista(deportistas[i]);
    }
}

/**
 * @brief Carga el CSV actual en un arreglo.
 *
 * @param deportistas Dirección donde se entrega el arreglo creado.
 * @param count Dirección donde se entrega la cantidad de elementos.
 * @return int 1 si la carga fue exitosa, 0 en caso contrario.
 */
static int load_data(Deportista **deportistas, int *count)
{
    if(deportistas == NULL){
        return 0;
    }

    if(count == NULL){
        return 0;
    }

    *deportistas = loadDeportistasArray(count);
    if(*deportistas == NULL){
        printf("No hay deportistas cargados en el CSV\n");
        return 0;
    }

    if(*count == 0){
        freeDeportistasArray(*deportistas, *count);
        printf("No hay deportistas cargados en el CSV\n");
        return 0;
    }

    return 1;
}

/**
 * @brief Pregunta qué ordenamiento usar.
 *
 * @return int Opción seleccionada.
 */
static SortAlgorithm ask_sort_algorithm()
{
    char option[16];
    int selected;

    do {
        system("clear");

        printf(BOLD BLUE "=== Algoritmo de ordenamiento ===\n" NORMAL);
        printf("  1) Insertion sort\n");
        printf("  2) Bubble sort\n");
        printf("  3) Selection sort\n");
        printf("  4) Cocktail shaker sort\n\n");
        printf(BOLD "Opcion: " NORMAL);

        if(fgets(option, sizeof(option), stdin) == NULL){
            return 0;
        }

        selected = atoi(option);
    }
    while(selected < INSERTION_SORT || selected > COCKTAIL_SHAKER_SORT);

    return (SortAlgorithm)selected;
}

/**
 * @brief Pregunta qué búsqueda usar.
 *
 * @return int Opción seleccionada.
 */
static SearchAlgorithm ask_search_algorithm()
{
    char option[16];
    int selected;

    do {
        system("clear");

        printf(BOLD BLUE "=== Algoritmo de busqueda ===\n" NORMAL);
        printf("  1) Busqueda secuencial\n");
        printf("  2) Busqueda binaria\n\n");
        printf(BOLD "Opcion: " NORMAL);

        if(fgets(option, sizeof(option), stdin) == NULL){
            return 0;
        }

        selected = atoi(option);
    }
    while(selected < 1 || selected > 2);

    return (SearchAlgorithm)selected;
}



/**
 * @brief Ejecuta una operación de ordenamiento o ranking.
 *
 * @param criteria Campo por el cual se ordena.
 * @param rankingAmount Cantidad de elementos a mostrar.
 * @param descending 1 si el orden es descendente, 0 en caso contrario.
 */
static void run_sort_operation(SortCriteria criteria, int rankingAmount, SortOrder order)
{
    Deportista *deportistas;
    SortAlgorithm algorithmOption = ask_sort_algorithm();
    int count;


    switch(algorithmOption){
        case INSERTION_SORT:
            if(load_data(&deportistas, &count) == 0){
                return;
            }

            insertion_sort_deportistas(deportistas, count, criteria, order);
            if(rankingAmount > count){
                rankingAmount = count;
            }

            printDeportistasArray(deportistas, rankingAmount);

            freeDeportistasArray(deportistas, count);
            break;
        case BUBBLE_SORT:
            if(load_data(&deportistas, &count) == 0){
                return;
            }
            optimized_bubble_sort(deportistas, count, criteria, order);
            if(rankingAmount > count){
                rankingAmount = count;
            }
            printDeportistasArray(deportistas, rankingAmount);

            freeDeportistasArray(deportistas, count);
            break;
        case SELECTION_SORT:
            if(load_data(&deportistas, &count) == 0){
                return;
            }

            selection_sort(deportistas, count, criteria, order);

            if(rankingAmount > count){
                rankingAmount = count;
            }

            printDeportistasArray(deportistas, rankingAmount);
            freeDeportistasArray(deportistas, count);
            break;
        case COCKTAIL_SHAKER_SORT:
            if(load_data(&deportistas, &count) == 0){
                return;
            }
            cocktail_shaker_sort(deportistas, count, criteria, order);
            if(rankingAmount > count){
                rankingAmount = count;
            }

            printDeportistasArray(deportistas, rankingAmount);

            freeDeportistasArray(deportistas, count);
            break;
        default:
            printf("Error\n");
            break;
    }
}



/**
 * @brief Busca un deportista por ID e imprime el resultado.
 *
 * @param targetId ID buscado.
 */
void search_by_id(int targetId)
{
    Deportista *deportistas;
    SearchAlgorithm algorithmOption;
    int count, index;

    algorithmOption = ask_search_algorithm();

    switch(algorithmOption){
        case SECUENTIAL_SEARCH:
            if(load_data(&deportistas, &count) == 0){
                return;
            }

            index = sequential_search_by_id(deportistas, count, targetId);
            if(index < 0){
                freeDeportistasArray(deportistas, count);
                printf("No se encontro un deportista con ID %d\n", targetId);
                return;
            }

            print_deportista(deportistas[index]);
            freeDeportistasArray(deportistas, count);
            break;
        case BINARY_SEARCH:
            if(load_data(&deportistas, &count) == 0){
                return;
            }

            // Requisito para busqueda binaria: arreglo ordenado por ID ascendente
            insertion_sort_deportistas(deportistas, count, SORT_BY_ID, ASCENDING);

            index = binary_search_by_id(deportistas, count, targetId);
            if(index < 0){
                freeDeportistasArray(deportistas, count);
                printf("No se encontro un deportista con ID %d\n", targetId);
                return;
            }

            print_deportista(deportistas[index]);
            freeDeportistasArray(deportistas, count);
            break;
        default:
            printf("Aun no esta implementado\n");
            break;
    }
}

/**
 * @brief Muestra el ranking de los mejores N deportistas según puntaje.
 *
 * @param rankingAmount Cantidad de deportistas a mostrar.
 */
void show_ranking(int rankingAmount)
{
    run_sort_operation(4, rankingAmount, 1);
}

/**
 * @brief Imprime la ayuda de uso del programa.
 *
 * @param programName Nombre del ejecutable.
 */
void print_help(const char *programName)
{
    printf("Uso: %s [opciones]\n", programName);
    printf("  -h                 Muestra esta ayuda\n");
    printf("  -g [cantidad]      Genera datos aleatorios\n");
    printf("  -t                 Ordena deportistas\n");
    printf("  -id [valor]        Busca un deportista por ID\n");
    printf("  -r [cantidad]      Muestra el top N por puntaje\n");
    printf("  -b                 Ejecuta benchmark de busqueda\n");
}

/**
 * @brief Pregunta por el campo de ordenamiento.
 *
 * @return SortCriteria Opción seleccionada.
 */
static SortCriteria ask_sort_criteria()
{
    char option[16];
    SortCriteria criteria;

    do {
        system("clear");

        printf(BOLD BLUE "=== Campo de ordenamiento ===\n" NORMAL);
        printf("  1) ID\n");
        printf("  2) Puntaje\n");
        printf("  3) Competencias\n");
        printf("  4) Nombre\n");
        printf("  5) Equipo\n\n");
        printf(BOLD "Opcion: " NORMAL);

        if(fgets(option, sizeof(option), stdin) == NULL){
            return 0;
        }

        criteria = atoi(option);
    }
    while(criteria < 1 || criteria > 5);

    return criteria;
}


/**
 * @brief Funcion que pregunta por el sentido del ordenamiento
 * @return SortOrder Opcion seleccionada
 */
SortOrder ask_sort_order()
{
    char option[16];
    int selected;

    do {
        system("clear");

        printf(BOLD BLUE "=== Orden ===\n" NORMAL);
        printf("  1) Descendente\n");
        printf("  2) Ascendente\n\n");
        printf(BOLD "Opcion: " NORMAL);

        if(fgets(option, sizeof(option), stdin) == NULL){
            return 0;
        }

        selected = atoi(option);
    }
    while(selected < 1 || selected > 2);

    return (selected == 1) ? DESCENDING : ASCENDING;
}

void runExperiment()
{
    SortCriteria criteria = ask_sort_criteria();

    SortOrder order = ask_sort_order();

    run_sort_operation(criteria, MAX_DATA, order);

}

void run_search_benchmark()
{
    const int sizes[] = {10, 100, 1000, 10000};
    const int num_sizes = (int)(sizeof(sizes) / sizeof(sizes[0]));
    const int repeats = 30; // cantidad de veces que se repite cada prueba para promediar resultados

    FILE *out = fopen(BENCHMARK_ROUTE, "w");
    if(out == NULL){
        printf("No se pudo crear archivo\n");
        return;
    }

    fprintf(out, "n,repeticiones,promedio_secuencial_s,promedio_binaria_s\n");
    printf("n | repeticiones | secuencial(s) | binaria(s)\n");
    printf("-------------------------------------------------\n");

    for(int i = 0; i < num_sizes; i++){
        int n = sizes[i];
        double total_seq = 0;
        double total_bin = 0;
        int validRuns = 0;

        for(int j = 0; j < repeats; j++){
            int count = 0;
            Deportista *deportistas;
            int targetId;
            clock_t start, end;

            createDeportistasCSV(n);
            deportistas = loadDeportistasArray(&count);
            if(deportistas == NULL || count <= 0){
                if(deportistas != NULL){
                    freeDeportistasArray(deportistas, count);
                }
                continue;
            }

            // Se toma el ID del ultimo elemento arbitrariamente (asi se asegura que existe)
            targetId = deportistas[count - 1]->ID;

            start = clock();
            sequential_search_by_id(deportistas, count, targetId);
            end = clock();
            total_seq += (double)(end - start) / CLOCKS_PER_SEC;

            // Insertion sort necesita tener el arreglo ordenado
            insertion_sort_deportistas(deportistas, count, SORT_BY_ID, ASCENDING);

            start = clock();
            binary_search_by_id(deportistas, count, targetId);
            end = clock();
            total_bin += (double)(end - start) / CLOCKS_PER_SEC;

            validRuns++;
            freeDeportistasArray(deportistas, count);
        }

        if(validRuns == 0){ //Si no se pudo ejecutar ninguna prueba, se escribe 0 en los tiempos para ese tamaño
            fprintf(out, "%d,%d,0,0\n", n, repeats);
            printf("%d | %d | 0 | 0\n", n, repeats);
            continue;
        }


        double avgSeq = total_seq / validRuns;
        double avgBin = total_bin / validRuns;

        fprintf(out, "%d,%d,%.10f,%.10f\n", n, validRuns, avgSeq, avgBin);
        printf("%d | %d | %.10f | %.10f\n", n, validRuns, avgSeq, avgBin);

    }

    fclose(out);
    printf("\nBenchmark guardado correctamente\n");
}

