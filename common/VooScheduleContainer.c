//
// Created by vinir on 05/12/2018.
//

#include "VooScheduleContainer.h"


static void sort_bubbleSort
    (VooSchedule *list, int length, VSContainer_Comparator comparator);
static void sort_selectionSort
    (VooSchedule *list, int length, VSContainer_Comparator comparator);
static void sort_insertionSort
    (VooSchedule *list, int length, VSContainer_Comparator comparator);
static void sort_shellSort
    (VooSchedule *list, int length, VSContainer_Comparator comparator);

struct __VSContainer {
    VooSchedule *list;
    int len;
    int cap;
    struct VSContainer_SortStats stats; 
};

VSContainer VSContainer_new() {
    VSContainer instance = malloc(sizeof(struct __VSContainer));
    instance->list = NULL;
    instance->len = 0;
    instance->cap = 0;
    instance->stats = (struct VSContainer_SortStats){
        .comps   = 0,
        .moves   = 0,
        .elapsed = 0
    };
    return instance;
}

void VSContainer_insert(VSContainer this, VooSchedule schedule) {
    if(this->len + 1 >= this->cap) { // Increase
        this->cap = this->cap >= 3 ? (int)(this->cap * 1.5f) : this->cap + 1;
        this->list = realloc(this->list, this->cap);
        if(!this->list) {
            FATAL("Out of memory");
        }
    }
    this->list[this->len++] = schedule;
}

void VSContainer_sort(VSContainer this, VSContainer_SortType, VSContainer_Comparator comparator) {

}

void sort_bubbleSort
    (VooSchedule *list, int length, VSContainer_Comparator comparator) {
    for (int i = 0; i < length - 1; i++){
        for (int j = (i+1); j < length; j++){
            if (comparator(list[j], list[i]) < 0){
                VooSchedule temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
}

void sort_selectionSort
    (VooSchedule *list, int length, VSContainer_Comparator comparator) {i

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

void sort_insertionSort
    (VooSchedule *list, int length, VSContainer_Comparator comparator) {

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

void sort_shellSort
    (VooSchedule *list, int length, VSContainer_Comparator comparator) {

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

