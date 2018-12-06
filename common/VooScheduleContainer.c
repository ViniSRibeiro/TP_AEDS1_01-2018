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

static struct VSContainer_SortStats sort_quickSort
        (VooSchedule *list, int length, VSContainer_Comparator comparator);

static struct VSContainer_SortStats sort_HeapSort
        (VooSchedule *list, int length, VSContainer_Comparator comparator);

struct __VSContainer {
    VooSchedule *list;
    size_t      len;
    size_t      cap;
};

VSContainer VSContainer_new(size_t initialSize) {
    VSContainer instance = malloc(sizeof(struct __VSContainer));
    if (initialSize) {
        instance->list = calloc(initialSize, sizeof(VooSchedule));
        if (!instance->list) {
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
    if (this->cap < size) {
        this->cap  = (size - this->cap) == 1 ? (this->cap >= 3 ? (int) (this->cap * 1.5f) : this->cap + 1) : size;
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
    int length = (int) this->len;
    switch (type) {
        case VSCONTAINER_BUBBLE:
            return sort_bubbleSort(this->list, length, comparator);
        case VSCONTAINER_SELECTION:
            return sort_selectionSort(this->list, length, comparator);
        case VSCONTAINER_INSERTION:
            return sort_insertionSort(this->list, length, comparator);
        case VSCONTAINER_SHELL:
            return sort_shellSort(this->list, length, comparator);
        case VSCONTAINER_QUICK:
            return sort_quickSort(this->list, length, comparator);
        case VSCONTAINER_HEAP:
            return sort_HeapSort(this->list, length, comparator);
        default:
            FATAL("Runtime exception: Invalid sort type");
    }
}

void VSContainer_delete(VSContainer this) {
    for (size_t i = 0; i < this->len; ++i) {
        if (this->list[i] != NULL) {
            VooSchedule_delete(this->list[i]);
        }
    }
    free(this->list);
    free(this);
}

struct VSContainer_SortStats sort_bubbleSort
        (VooSchedule *list, int length, VSContainer_Comparator comparator) {
    struct VSContainer_SortStats stats = {0};
    for (int i = 0; i < length - 1; i++) {
        for (int j = (i + 1); j < length; j++) {
            if ((stats.comps++, comparator(list[j], list[i])) >0 ) {
                VooSchedule temp = list[i];
                list[i] = list[j];
                list[j] = temp;
                stats.moves++;
            }
        }
    }
    return (stats);
}

struct VSContainer_SortStats sort_selectionSort
        (VooSchedule *list, int length, VSContainer_Comparator comparator) {
    struct VSContainer_SortStats stats = {0};
    int j, min;
    VooSchedule aux;
    for (int i = 0; i < (length - 1); i++) {
        min = i;
        for (j = (i + 1); j < length; j++) {
            if (list[j] < list[min])
                min = j;
        }
        if ((stats.comps++, comparator(list[i], list[min])) != 0) {
            aux = list[i];
            list[i] = list[min];
            list[min] = aux;
            stats.moves++;
        }
    }
    return (stats) ;
}

struct VSContainer_SortStats sort_insertionSort
        (VooSchedule *list, int length, VSContainer_Comparator comparator) {
    struct VSContainer_SortStats stats = {0};
    int j;
    VooSchedule escolhido;

    for (int i = 1; i < length; i++) {
        escolhido = list[i];
        j = i - 1;

        while ((j >= 0) && (stats.comps++, comparator(list[j],escolhido)) < 0) {
            list[j + 1] = list[j];
            j--;
        }

        list[j + 1] = escolhido;
        stats.moves++;
    }
    return (stats);
}

struct VSContainer_SortStats sort_shellSort
        (VooSchedule *list, int length, VSContainer_Comparator comparator) {
    struct VSContainer_SortStats stats = {0};
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
            while (j >= gap && (stats.comps++, comparator(value, list[j - gap])) < 0) {
                list[j] = list[j - gap];
                j = j - gap;
            }
            list[j] = value;
            stats.moves++;
        }
    }
    return (stats);
}

void sort_QuickSort_Particao(int Esq, int Dir, int *i, int *j, VooSchedule *list, VSContainer_Comparator comparator,
                             struct VSContainer_SortStats *stats) {
    VooSchedule pivo, aux;
    *i = Esq;
    *j = Dir;
    pivo = list[(*i + *j) / 2];

    do {
        while (stats->comps++, comparator(pivo, list[*i]) > 0) (*i)++;
        while (stats->comps++, comparator(pivo, list[*j]) < 0) (*j)--;
        if (*i <= *j) {
            aux = list[*i];
            list[*i] = list[*j];
            list[*j] = aux;
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}

void sort_QuickSort_Ordena(int Esq, int Dir, VooSchedule *list, VSContainer_Comparator comparator,
                           struct VSContainer_SortStats *stats) {
    int i, j;
    sort_QuickSort_Particao(Esq, Dir, &i, &j, list, comparator, stats);

    if (Esq < j) {
        sort_QuickSort_Ordena(Esq, j, list, comparator, stats);
    }

    if (i < Dir) {
        sort_QuickSort_Ordena(i, Dir, list, comparator, stats);
    }

}

struct VSContainer_SortStats sort_quickSort(VooSchedule *list, int length, VSContainer_Comparator comparator) {
    struct VSContainer_SortStats stats = {0};
    sort_QuickSort_Ordena(0, length - 1, list, comparator, &stats);
    return stats;
}

struct VSContainer_SortStats sort_HeapSort(VooSchedule *list, int length, VSContainer_Comparator comparator) {
    struct VSContainer_SortStats stats = {0};
    int i = length / 2, pai, filho;
    VooSchedule t;
    while (true) {
        if (i > 0) {
            i--;
            t = list[i];
        } else {
            length--;
            if (length == 0) return (struct VSContainer_SortStats) {};
            t = list[length];
            list[length] = list[0];
        }
        pai = i;
        filho = i * 2 + 1;
        while (filho < length) {
            if ((filho + 1 < length) && (list[filho + 1] > list[filho]))
                filho++;
            if (stats.comps++, comparator(list[filho], t) > 0) {
                list[pai] = list[filho];
                pai = filho;
                filho = pai * 2 + 1;
                stats.moves++;
            } else {
                break;
            }
        }
        list[pai] = t;
        return (stats);
    }
}
