/*
* Autor: Daniel Gonzalez
* Carne: 20293
* Curso: Sistemas operativos
* Descripcion: Programa que calcula estadisticas basicas con threads.           
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>
#include <math.h>

int arraySize;

// Funcion mean: Funcion que suma todos los elementos de un array
// y retorna la division de esta suma entre la cantidad total de
// elementos.
void* mean(void* arg) {
    int* array = (int*) arg;
    float *res =  malloc(sizeof(float));
    *res = 0;
    for(int i = 0; i < arraySize; i++) {
        *res += array[i];
    }

    *res /= arraySize;

    pthread_exit((void *) res);
}

void bubbleSort(int * array) {
    for (int i = 1; i < arraySize; i++) {
        for (int j = 0; j < arraySize - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }

        }
    }
}

// Funcion median: Funcion que ordena ascendentemente los elementos
// de un array y retorna el elemento medio.
void* median(void* arg) {
    int* array = (int*) arg;
    bubbleSort(array);
    float *res =  malloc(sizeof(float));
    *res = 0;
    if (arraySize % 2 == 0) {
        int mid = arraySize / 2;
        *res = (float)((array[mid -1] + array[mid])) / 2;
    }
    else {
        int mid = arraySize / 2;
        *res = (float) array[mid];
    }

    pthread_exit((void *) res);
}

// Funcion std: Programa que calcula la desviacion estandar a partir
// de la media de los datos.
void* std(void* arg) {
    int* array = (int*) arg;
    float *mean =  malloc(sizeof(float));
    *mean = 0;
    for (int i = 0; i < arraySize; i++) {
        *mean += array[i];
    }
    *mean /= arraySize;
    float *std =  malloc(sizeof(float));
    *std = 0;
    for (int i = 0; i < arraySize; i++) {
        *std += pow(array[i] - *mean, 2);
    }

    *std = sqrt(*std / arraySize);

    pthread_exit((void *) std);
}

// Funcion max: Funcion que recorre todos los elementos de un array
// y determina cual es el maximo por medio de la comparacion de
// estos.
void* max(void* arg) {
    int* array = (int*) arg;
    float *max =  malloc(sizeof(float));
    *max = array[0];
    for (int i = 0; i < arraySize; i++) {
        if (array[i] > *max) {
            *max = array[i];
        }
    }

    pthread_exit((void *) max);
}

// Funcion min: Funcion que recorre todos los elementos de un array
// y determina cual es el mainimo por medio de la comparacion de
// estos.
void* min(void* arg) {
    int* array = (int*) arg;
    float *min =  malloc(sizeof(float));
    *min = array[0];
    for (int i = 0; i < arraySize; i++) {
        if (array[i] < *min) {
            *min = array[i];
        }
    }

    pthread_exit((void*) min);
}

int main(int argc, char *argv[]) {
    int numbers[argc - 1];
    pthread_t tMean;
    pthread_t tMedian;
    pthread_t tStd;
    pthread_t tMax;
    pthread_t tMin;

    arraySize = argc - 1;

    // Almacenamiento de los numeros ingresados como argumentos
    // al programa.
    for (int i = 0; i < argc - 1; i++) {
        numbers[i] = atoi(argv[i + 1]);
    }

    void* retMean;
    void* retMedian;
    void* retStd;
    void* retMax;
    void* retMin;

    // Creacion de los hilos con su respectiva funcion.
    if (pthread_create(&tMean, NULL, &mean, &numbers) == 0) {
        printf("Thread de media creado correctamente.\n");
    }
    if (pthread_create(&tMedian, NULL, &median, &numbers) == 0) {
        printf("Thread de mediana creado correctamente.\n");
    }
    if (pthread_create(&tStd, NULL, &std, &numbers) == 0) {
        printf("Thread de desviacion estandar creado correctamente.\n");
    }
    if (pthread_create(&tMax, NULL, &max, &numbers) == 0) {
        printf("Thread de maximo creado correctamente.\n");
    }
    if (pthread_create(&tMin, NULL, &min, &numbers) == 0) {
        printf("Thread de min creado correctamente.\n");
    }

    // Los joins permiten recibir el output de la funcion realizada
    // por cada uno de los threads creados. Se muestran estos
    // resultados.
    if (pthread_join(tMean, &retMean) == 0) {
        printf("La media es %f\n", *((float*) retMean));
    }
    if (pthread_join(tMedian, &retMedian) == 0) {
        printf("La mediana es %f\n", *((float*) retMedian));
    }
    if (pthread_join(tStd, &retStd) == 0) {
        printf("La desviacion estandar es %f\n", *((float*) retStd));
    }
    if (pthread_join(tMax, &retMax) == 0) {
        printf("El valor maximo es %f\n", *((float*) retMax));
    }
    if (pthread_join(tMin, &retMin) == 0) {
        printf("El valor minimo es %f\n", *((float*) retMin));
    }

    free(retMean);
    free(retMedian);
    free(retStd);
    free(retMax);
    free(retMin);

    return 0;
}