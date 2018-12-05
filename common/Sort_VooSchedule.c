//
// Created by vinir on 05/12/2018.
//

#include "Sort_VooSchedule.h"

void sort_bubbleSort(int* vet, int length) {
    int i, j, temp;

    for (i = 0; i < length - 1; i++){
        for (j = (i+1); j < length; j++){
            if (vet[j] < vet[i]){
                temp = vet[i];
                vet[i] = vet[j];
                vet[j] = temp;
            }
        }
    }
}

void sort_selection_sort(int num[], int tam) {
    int i, j, min, aux;
    for (i = 0; i < (tam-1); i++)
    {
        min = i;
        for (j = (i+1); j < tam; j++) {
            if(num[j] < num[min])
                min = j;
        }
        if (num[i] != num[min]) {
            aux = num[i];
            num[i] = num[min];
            num[min] = aux;
        }
    }
}

void sort_insertion_sort(int vetor[], int TAM) {

    int escolhido, j;

    for (int i = 1; i < TAM; i++) {
        escolhido = vetor[i];
        j = i - 1;

        while ((j >= 0) && (vetor[j] > escolhido)) {
            vetor[j + 1] = vetor[j];
            j--;
        }

        vetor[j + 1] = escolhido;
    }
}

void sort_shellSort(int *vet, int TAM) {
    int i , j , value;
    int gap = 1;
    while(gap < TAM) {
        gap = 3*gap+1;
    }
    while ( gap > 1) {
        gap /= 3;
        for(i = gap; i < TAM; i++) {
            value = vet[i];
            j = i;
            while (j >= gap && value < vet[j - gap]) {
                vet[j] = vet [j - gap];
                j = j - gap;
            }
            vet [j] = value;
        }
    }
}

