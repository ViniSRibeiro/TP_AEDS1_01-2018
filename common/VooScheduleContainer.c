//
// Created by vinir on 05/12/2018.
//

#include <windef.h>
#include "VooScheduleContainer.h"


static struct VSContainer_SortStats sort_bubbleSort
        (VooSchedule *list, int length, VSContainer_Comparator comparator);

static struct VSContainer_SortStats sort_selectionSort
        (VooSchedule *list, int length, VSContainer_Comparator comparator);

static struct VSContainer_SortStats sort_insertionSort
        (VooSchedule *list, int length, VSContainer_Comparator comparator);

static struct VSContainer_SortStats sort_shellSort
        (VooSchedule *list, int length, VSContainer_Comparator comparator);

struct __VSContainer {
    VooSchedule *list;
    int len;
    int cap;
};

VSContainer VSContainer_new() {
    VSContainer instance = malloc(sizeof(struct __VSContainer));
    instance->list = NULL;
    instance->len = 0;
    instance->cap = 0;
    return instance;
}

void VSContainer_insert(VSContainer this, VooSchedule schedule) {
    if (this->len + 1 >= this->cap) { // Increase
        this->cap = this->cap >= 3 ? (int) (this->cap * 1.5f) : this->cap + 1;
        this->list = realloc(this->list, this->cap);
        if (!this->list) {
            FATAL("Out of memory");
        }
    }
    this->list[this->len++] = schedule;
}

struct VSContainer_SortStats
VSContainer_sort(VSContainer this, enum VSContainer_SortType type, VSContainer_Comparator comparator) {
    switch (type) {
        case VSCONTAINER_BUBBLE:
            return sort_bubbleSort(this->list, this->len, comparator);
        case VSCONTAINER_SELECTION:
            return sort_selectionSort(this->list, this->len, comparator);
        case VSCONTAINER_INSERTION:
            return sort_insertionSort(this->list, this->len, comparator);
        case VSCONTAINER_SHELL:
            return sort_shellSort(this->list, this->len, comparator);
        case VSCONTAINER_QUICK:
            return sort_bubbleSort(this->list, this->len, comparator); // TODO Replace bubble to quick
        case VSCONTAINER_HEAP:
            return sort_bubbleSort(this->list, this->len, comparator); // TODO Replace bubble to heap
        default:
            FATAL("Runtime exception: Invalid sort type");
    }
}

struct VSContainer_SortStats sort_bubbleSort
        (VooSchedule *list, int length, VSContainer_Comparator comparator) {
    for (int i = 0; i < length - 1; i++) {
        for (int j = (i + 1); j < length; j++) {
            if (comparator(list[j], list[i]) > 0) {
                VooSchedule temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
    return (struct VSContainer_SortStats) {};
}

struct VSContainer_SortStats sort_selectionSort
        (VooSchedule *list, int length, VSContainer_Comparator comparator) {

    int j, min;
    VooSchedule aux;
    for (int i = 0; i < (length - 1); i++) {
        min = i;
        for (j = (i + 1); j < length; j++) {
            if (list[j] < list[min])
                min = j;
        }
        if (comparator(list[i], list[min]) != 0) {
            aux = list[i];
            list[i] = list[min];
            list[min] = aux;
        }
    }
    return (struct VSContainer_SortStats) {};
}

struct VSContainer_SortStats sort_insertionSort
        (VooSchedule *list, int length, VSContainer_Comparator comparator) {

    int j;
    VooSchedule escolhido;

    for (int i = 1; i < length; i++) {
        escolhido = list[i];
        j = i - 1;

        while ((j >= 0) && comparator(list[j], escolhido) < 0) {
            list[j + 1] = list[j];
            j--;
        }

        list[j + 1] = escolhido;
    }
    return (struct VSContainer_SortStats) {};
}

struct VSContainer_SortStats sort_shellSort
        (VooSchedule *list, int length, VSContainer_Comparator comparator) {

    int i, j;
    VooSchedule value;
    int gap = 1;
    while (gap > length) {
        gap = 3 * gap + 1;
    }
    while (gap > 1) {
        gap /= 3;
        for (i = gap; i < length; i++) {
            value = list[i];
            j = i;
            while (j >= gap && comparator(value, list[j - gap]) < 0) {
                list[j] = list[j - gap];
                j = j - gap;
            }
            list[j] = value;
        }
    }
    return (struct VSContainer_SortStats) {};
}

void Particao(int Esq, int Dir,int *i, int *j, VooSchedule *A){
    VooSchedule pivo, aux;
    *i = Esq; *j = Dir;
    pivo = A[(*i + *j)/2];

    do
    {
        while(pivo -> Chave > A[*i] -> Chave) (*i)++;
        while(pivo -> Chave < A[*j] -> Chave) (*j)--;
        if(*i <= *j){
            aux = A[*i]; A[*i] = A[*j]; A[*j] = aux;
            (*i)++; (*j)--;
        }
    }while(*i <= *j);
}

void Ordena(int Esq, int Dir, VooSchedule *A) {
    int i, j;
    Particao(Esq, Dir, &i, &j, A);
    if (Esq < j)Ordena(Esq, j, A);
    if (i < Dir)Ordena(i, Dir, A);
}

void QuickSort(VooSchedule *A, int n) {
    Ordena(0, n - 1, A);
}

