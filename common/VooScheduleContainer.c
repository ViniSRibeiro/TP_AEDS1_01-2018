//
// Created by vinir on 05/12/2018.
//


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
    size_t len;
    size_t cap;
};

VSContainer VSContainer_new(size_t initialSize) {
    VSContainer instance = malloc(sizeof(struct __VSContainer));
    if(initialSize) {
        instance->list = malloc(sizeof(VooSchedule));
        if(!instance->list) {
            FATAL("Out of memory. Cannot alloc VSContainer of size %llu", initialSize);
        }
        instance->len = 0;
        instance->cap = initialSize;
    } else {
        instance->list = NULL;
        instance->len  = 0;
        instance->cap  = 0;
    }
    return instance;
}

static void validateSize(VSContainer this, size_t size) {
    if(this->cap < size) {
        this->cap = (size - this->cap) == 1 ? (this->cap >= 3 ? (int) (this->cap * 1.5f) : this->cap + 1) : size;
        this->list = realloc(this->list, this->cap);
        if (!this->list) {
            FATAL("Out of memory. Cannot realloc VSContainer to size %llu", this->cap);
        }
    }
}

void VSContainer_insert(VSContainer this, VooSchedule schedule) {
    validateSize(this, this->len++);
    this->list[this->len] = schedule;
}

void VSContainer_insertAt(VSContainer this, size_t pos, VooSchedule schedule) {
    validateSize(this, pos + 1);
    this->list[pos] = schedule;
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

void sort_QuickSort_Particao(int Esq, int Dir, int *i, int *j, VooSchedule *A, VSContainer_Comparator comparator){
    VooSchedule pivo, aux;
    *i = Esq; *j = Dir;
    pivo = A[(*i + *j)/2];

    do
    {
        while (comparator(pivo,A[*i])>0) (*i)++;
        while(comparator(pivo,A[*j])<0) (*j)--;
        if(*i <= *j){
            aux = A[*i]; A[*i] = A[*j]; A[*j] = aux;
            (*i)++; (*j)--;
        }
    }while(*i <= *j);
}

void sort_QuickSort_Ordena(int Esq, int Dir, VooSchedule *A,VSContainer_Comparator comparator) {
    int i, j;
    sort_QuickSort_Particao(Esq, Dir, &i, &j, A,comparator);
    if (Esq < j)sort_QuickSort_Ordena(Esq, j, A,comparator);
    if (i < Dir)sort_QuickSort_Ordena(i, Dir, A,comparator);
}

void sort_QuickSort_main(VooSchedule *A, int n,VSContainer_Comparator comparator) {
    sort_QuickSort_Ordena(0, n - 1, A,comparator);
}

void sort_heapsort(VooSchedule a[], int n) {
    int i = n / 2, pai, filho, t;
    while(true) {
        if (i > 0) {
            i--;
            t = a[i];
        } else {
            n--;
            if (n == 0) return;
            t = a[n];
            a[n] = a[0];
        }
        pai = i;
        filho = i * 2 + 1;
        while (filho < n) {
            if ((filho + 1 < n)  &&  (a[filho + 1] > a[filho]))
                filho++;
            if (a[filho] > t) {
                a[pai] = a[filho];
                pai = filho;
                filho = pai * 2 + 1;
            } else {
                break;
            }
        }
        a[pai] = t;
    }
}