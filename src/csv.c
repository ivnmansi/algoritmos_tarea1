#include "csv.h"
#include "base.h"
#include "generator.h"

void createDeportistasCSV(int cantidadDatos){
    FILE* f = fopen(CSV_ROUTE,"w");
    if(f == NULL){
        printf("No se pudo crear el archivo.\n");
        return;
    }
    fprintf(f, "ID,Nombre,Equipo,Puntaje,Competencias\n");
    for(int i = 0; i < cantidadDatos; i++){
        int id = i;
        char* nombre = generate_random_name();
        char* equipo = generate_random_team();
        float puntaje = generate_random_score();
        int competencias = generate_random_competitions();
        fprintf(f, "%d,%s,%s,%.2f,%d\n", id, nombre, equipo, puntaje, competencias);
        free(nombre);
        free(equipo);
    }

    printf("Archivo CSV creado con éxito.\n");
    fclose(f);
}

static char* duplicateString(const char* src){
    size_t len = strlen(src);
    char* copy = malloc((len + 1) * sizeof(char));
    if(copy == NULL){
        return NULL;
    }
    memcpy(copy, src, len + 1);
    return copy;
}

void loadDeportistasCSV(LinkedList linkedList){
    if(linkedList == NULL){
        return;
    }

    FILE* f = fopen(CSV_ROUTE,"r");
    if(f == NULL){
        return;
    }

    char line[512];

    if(fgets(line, sizeof(line), f) == NULL){
        fclose(f);
        return;
    }

    while(fgets(line, sizeof(line), f) != NULL){
        char* token = strtok(line, ",\n\r");
        if(token == NULL){
            continue;
        }
        int id = atoi(token);

        token = strtok(NULL, ",\n\r");
        if(token == NULL){
            continue;
        }
        char* nombre = duplicateString(token);
        if(nombre == NULL){
            continue;
        }

        token = strtok(NULL, ",\n\r");
        if(token == NULL){
            free(nombre);
            continue;
        }
        char* equipo = duplicateString(token);
        if(equipo == NULL){
            free(nombre);
            continue;
        }

        token = strtok(NULL, ",\n\r");
        if(token == NULL){
            free(nombre);
            free(equipo);
            continue;
        }
        float puntaje = strtof(token, NULL);

        token = strtok(NULL, ",\n\r");
        if(token == NULL){
            free(nombre);
            free(equipo);
            continue;
        }
        int competencias = atoi(token);

        Deportista deportista = createDeportista(id, nombre, equipo, puntaje, competencias);
        if(deportista == NULL){
            free(nombre);
            free(equipo);
            continue;
        }

        addDeportistaToList(linkedList, deportista);
    }

    fclose(f);
}

int loadDeportistasCSVToArray(Deportista** outArray, int* outCount){
    *outArray = NULL;
    *outCount = 0;

    FILE* f = fopen(CSV_ROUTE, "r");
    if(f == NULL){
        return 0;
    }

    int capacity = 128;
    int count = 0;
    Deportista* array = malloc((size_t)capacity * sizeof(Deportista));
    if(array == NULL){
        fclose(f);
        return 0;
    }

    char line[512];

    if(fgets(line, sizeof(line), f) == NULL){
        free(array);
        fclose(f);
        return 0;
    }

    while(fgets(line, sizeof(line), f) != NULL){
        char* token = strtok(line, ",\n\r");
        if(token == NULL){
            continue;
        }
        int id = atoi(token);

        token = strtok(NULL, ",\n\r");
        if(token == NULL){
            continue;
        }
        char* nombre = duplicateString(token);
        if(nombre == NULL){
            continue;
        }

        token = strtok(NULL, ",\n\r");
        if(token == NULL){
            free(nombre);
            continue;
        }
        char* equipo = duplicateString(token);
        if(equipo == NULL){
            free(nombre);
            continue;
        }

        token = strtok(NULL, ",\n\r");
        if(token == NULL){
            free(nombre);
            free(equipo);
            continue;
        }
        float puntaje = strtof(token, NULL);

        token = strtok(NULL, ",\n\r");
        if(token == NULL){
            free(nombre);
            free(equipo);
            continue;
        }
        int competencias = atoi(token);

        Deportista d = createDeportista(id, nombre, equipo, puntaje, competencias);
        if(d == NULL){
            free(nombre);
            free(equipo);
            continue;
        }

        if(count == capacity){
            capacity *= 2;
            Deportista* resized = realloc(array, (size_t)capacity * sizeof(Deportista));
            if(resized == NULL){
                deleteDeportista(d);
                freeDeportistasArray(array, count);
                fclose(f);
                return 0;
            }
            array = resized;
        }

        array[count++] = d;
    }

    fclose(f);

    *outArray = array;
    *outCount = count;
    return 1;
}

void freeDeportistasArray(Deportista* array, int count){
    if(array == NULL){
        return;
    }
    for(int i = 0; i < count; i++){
        deleteDeportista(array[i]);
    }
    free(array);
}