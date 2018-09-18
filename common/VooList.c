#include "VooList.h"

typedef struct _Node {
    Voo data;
    struct _Node *next;
} *_Node;

struct __VooList {
    _Node first;
    _Node last;
    uint32_t length;
};

static _Node _AllocateNode(Voo v/*, _Node next*/) {
    _Node h = malloc(sizeof(struct _Node));
    h->data = v;
    h->next = NULL;
    return h;
}

static Voo _Foreach(VooList this, Voo (*func)(VooList, _Node, void *), void *data) {
    Voo r = NULL;
    for (_Node f = this->first; f != NULL && r == NULL; f = f->next) {
        r = func(this, f, data);
    }
    return r;
}

static Voo _VooList_removeRoutine(VooList list, _Node node, VID *_id) {
    VID id = *_id;
    _Node next = node->next;
    if (next && VID_COMPARE(Voo_getVid(next->data), id)) {
        node->next = next->next;
        Voo v = next->data;
        if (next == list->last) {
            list->last = node;
        }
        free(next);
        return v;
    }
    return NULL;
}

static Voo _VooList_findRoutine(__attribute__((unused)) VooList list, _Node node, VID *_id) {
    VID id = *_id;
    _Node next = node->next;
    if (next && VID_COMPARE(Voo_getVid(next->data), id)) {
        return next->data;
    }
    return NULL;
}

VooList VooList_new() {
    VooList instance = malloc(sizeof(struct __VooList));
    instance->first = instance->last = _AllocateNode(NULL);
    instance->length = 0;
    return instance;
}

void VooList_insert(VooList this, Voo voo) {
    _Node f = this->first;
    while (f != NULL) {
        if(f->next != NULL) {
            _Node next = f->next;
            if (Time_compareTo(
                    FlightData_getSchedule(Voo_getTakeoff(voo)),
                    FlightData_getSchedule(Voo_getTakeoff(next->data))
            ) > 0) {
                f = next;
                continue;
            }
        }
        (f->next = _AllocateNode(voo))->next = f->next;
        break;
    }
    this->length++;
}

Voo VooList_remove(VooList this, VID vid) {
    return _Foreach(
            this,
            (Voo (*)(VooList, _Node, void *)) _VooList_removeRoutine,
            &vid
    );
}

Voo VooList_find(VooList this, VID vid) {
    return _Foreach(
            this,
            (Voo (*)(VooList, _Node, void *)) _VooList_findRoutine,
            &vid
    );
}

void VooList_forEach(VooList this, void (*target)(Voo)) {
    for(_Node f = this->first->next; f != NULL; f = f->next) {
        target(f->data);
    }
}

uint32_t VooList_size(VooList this) {
    return this->length;
}

void VooList_print(VooList this) {
    for(_Node f = this->first->next; f != NULL; f = f->next) {
        Voo v = f->data;
        VID id = Voo_getVid(v);
        Time takeOff = FlightData_getSchedule(Voo_getTakeoff(v));
        DEBUGLN("ID: %08lx%08lx %02d:%02d", id.mostSigBits, id.lessSigBits, Time_getHour(takeOff), Time_getMinute(takeOff));
    }
}

void VooList_delete(VooList instance) {
    for(_Node n = instance->first->next; n != NULL; free(n), n = n->next) {
        Voo_delete(n->data);
    }
    free(instance->first);
    free(instance);
}

