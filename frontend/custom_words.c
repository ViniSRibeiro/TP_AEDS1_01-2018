//
// Created by viniciuslrangel on 19/09/18.
//

#include "custom_words.h"
#include "../FIFTH/src/words.h"
#include "../common/VooSchedule.h"
#include "interactive.h"

#define GET_TIME(x, y) \
do {\
    int pos = DString_indexOf(x, ':');\
    if(pos == -1) {\
        FATAL("%s is not a valid time!", DString_raw(x));\
    }\
    DString h = DString_substr(x, 0, pos);\
    DString m = DString_substr(x, pos + 1, -1);\
    (y) = Time_new(strtol(DString_raw(h), NULL, 10), strtol(DString_raw(m), NULL, 10));\
    DString_delete(h);\
    DString_delete(m);\
    DString_delete(x);\
} while(0)

static VooSchedule item = NULL;

static void OperationA(__attribute__((unused)) ProgramStack stack) {
    if (item != NULL) {
        VooSchedule_delete(item);
    }
    item = VooSchedule_new();
}

static void OperationB(ProgramStack stack) {
    DString landingAir, takeOffAir, landingTimeStr, takeOffTimeStr;

    int8_t runway;
    struct PElement runwayElement = PStack_pop(stack);
    if(runwayElement.type == DATATYPE_STRING) {
        runway = (int8_t) strtol(DString_raw(runwayElement.data.string), NULL, 10);
        DString_delete(runwayElement.data.string);
    } else {
        runway = (int8_t) runwayElement.data.number;
    }

    POP_STRING(landingAir, stack);
    POP_STRING(takeOffAir, stack);
    POP_STRING(landingTimeStr, stack);
    POP_STRING(takeOffTimeStr, stack);

    Time landingTime, takeOffTime;
    GET_TIME(landingTimeStr, landingTime);
    GET_TIME(takeOffTimeStr, takeOffTime);

    VooSchedule_insert(
            item,
            Voo_new(
                    FlightData_new(
                            takeOffTime,
                            Aeroporto_get(DString_raw(takeOffAir)),
                            -1
                    ),
                    FlightData_new(
                            landingTime,
                            Aeroporto_get(DString_raw(landingAir)),
                            runway
                    )
            )
    );
    DString_delete(takeOffAir);
    DString_delete(landingAir);
}


static void OperationC(ProgramStack stack) {
    DString id;
    POP_STRING(id, stack);
    Voo v = VooSchedule_remove(item, (VID) {
            .bits = (uint32_t) strtol(DString_raw(id), NULL, 16)
    });
    if (v) {
        Voo_print(v);
    }
}


static void OperationD(ProgramStack stack) {
    DString id;
    POP_STRING(id, stack);
    Voo v = VooSchedule_find(item, (VID) {
            .bits = (uint32_t) strtol(DString_raw(id), NULL, 16)
    });
    DString_delete(id);
    Voo_print(v);
}


static void OperationE(ProgramStack stack) {
    DString landingTimeStr, takeOffTimeStr;
    POP_STRING(landingTimeStr, stack);
    POP_STRING(takeOffTimeStr, stack);
    Time landingTime, takeOffTime;
    GET_TIME(landingTimeStr, landingTime);
    GET_TIME(takeOffTimeStr, takeOffTime);
    VooSchedule_forEach(item, takeOffTime, landingTime, Voo_print);
    Time_delete(landingTime);
    Time_delete(takeOffTime);
}


static void OperationF(ProgramStack stack) {
    DString takeOffTimeStr;
    POP_STRING(takeOffTimeStr, stack);
    Time takeOffTime;
    GET_TIME(takeOffTimeStr, takeOffTime);
    VooSchedule_forEach(item, takeOffTime, NULL, Voo_print);
    Time_delete(takeOffTime);
}


static void OperationG(ProgramStack stack) {
    DString landingTimeStr;
    POP_STRING(landingTimeStr, stack);
    Time landingTime;
    GET_TIME(landingTimeStr, landingTime);
    VooSchedule_forEach(item, NULL, landingTime, Voo_print);
    Time_delete(landingTime);
}


static void OperationH(__attribute__((unused)) ProgramStack stack) {
    VooSchedule_forEach(item, NULL, NULL, Voo_print);
}


static void OperationI(__attribute__((unused)) ProgramStack stack) {
    struct VooSchedule_SearchResult result = VooSchedule_findPeakTime(item);
    PRINTLN("Intervalo de pico:"
            "\n> Decolagem %02dH"
            "\n> Pouso %02dH"
            "\n> Numero de voos: %d",
            result.takeOff, result.landing,
            VooScheduleItem_num(result.list)
    );
}


static void OperationJ(__attribute__((unused)) ProgramStack stack) {
    struct VooSchedule_SearchResult result = VooSchedule_findOffPeakTime(item);
    PRINTLN("Intervalo menos movimentado:"
            "\n> Decolagem %02dH"
            "\n> Pouso %02dH"
            "\n> Numero de voos: %d",
            result.takeOff, result.landing,
            VooScheduleItem_num(result.list)
    );
}


static void OperationK(__attribute__((unused)) ProgramStack stack) {
    struct VooSchedule_SearchResult result = VooSchedule_findMostRecentUpdated(item);
    Time t = VooScheduleItem_getLastUpdate(result.list);
    PRINTLN("Ultima lista alterada:"
            "\n> Decolagem %02dH"
            "\n> Pouso %02dH"
            "\n> Horario: %02d:%02d",
            result.takeOff, result.landing,
            Time_getHour(t), Time_getMinute(t)
    );
}


static void OperationL(__attribute__((unused)) ProgramStack stack) {
    struct VooSchedule_SearchResult result = VooSchedule_findLessRecentUpdated(item);
    Time t = VooScheduleItem_getLastUpdate(result.list);
    PRINTLN("Lista a mais tempo sem alterar:"
            "\n> Decolagem %02dH"
            "\n> Pouso %02dH"
            "\n> Horario: %02d:%02d",
            result.takeOff, result.landing,
            Time_getHour(t), Time_getMinute(t)
    );
}


static void OperationM(__attribute__((unused)) ProgramStack stack) {
    bool s = VooSchedule_isSparse(item);
    PRINTLN("Esparca: %s", s ? "Sim" : "Nao");
}

static void RandTime(ProgramStack stack) {
    char time[6];
    time[5] = 0;
    sprintf(time, "%02d:%02d", rand() % 24, rand() % 60); // NOLINT(cert-msc30-c,cert-msc50-cpp)
    PStack_push(stack, STACK_STR(DString_new(time)));
}

static void RandAir(ProgramStack stack) {
    char air[4];
    air[3] = 0;
    static uint8_t n = 'Z' - 'A' + 1;
    for (int i = 0; i < 3; ++i) {
        air[i] = (char) ('A' + rand() % n); // NOLINT(cert-msc30-c,cert-msc50-cpp)
    }
    PStack_push(stack, STACK_STR(DString_new(air)));
}

static void StartInteractive(__attribute__((unused)) ProgramStack stack) {
    interactive(item);
}

static void RandNum(ProgramStack stack) {
    number_t max;
    POP_NUMBER(max, stack);
    PStack_push(stack, STACK_NUMBER(rand() % ((uint64_t) max))); // NOLINT(cert-msc30-c,cert-msc50-cpp)
}

void RegisterAirportWords() {
    struct WordEntry wordEntry[] = {
            {"TA",       OperationA},
            {"TB",       OperationB},
            {"TC",       OperationC},
            {"TD",       OperationD},
            {"TE",       OperationE},
            {"TF",       OperationF},
            {"TG",       OperationG},
            {"TH",       OperationH},
            {"TI",       OperationI},
            {"TJ",       OperationJ},
            {"TK",       OperationK},
            {"TL",       OperationL},
            {"TM",       OperationM},
            {"RANDTIME", RandTime},
            {"RANDAIR",  RandAir},
            {"RANDNUM",  RandNum},
            {"GUI",      StartInteractive}
    };
    RegisterWords(wordEntry, sizeof(wordEntry) / sizeof(struct WordEntry));
}
