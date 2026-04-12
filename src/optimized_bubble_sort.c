#include "sorting.h"

void optimized_bubble_sort(Deportista *deportistas, int length, SortCriteria criteria, SortOrder order)
{
    int swapped;

    for (int i = 0; i < length - 1; i++) {
        swapped = 0;

        for (int j = 0; j < length - i - 1; j++) {
            int cmp = compare_by_criteria(deportistas[j], deportistas[j + 1], criteria);
            int shouldSwap = (order == ASCENDING) ? (cmp > 0) : (cmp < 0);

            if (shouldSwap) {
                swap_deportistas(&deportistas[j], &deportistas[j + 1]);
                swapped = 1;
            }
        }

        if (!swapped) {
            break;
        }
    }
}