#include "interactive_actions.h"
#include <stdio.h>
#include <memory.h>
#include "terminal.h"
#include "../FIFTH/src/dynamic_string.h"

#ifdef _WIN32
#define BACKSPACE '\b'
#else
#define BACKSPACE ((char) 127)
#endif

#define READ_TEXT 1u
#define READ_NUMBER (1u << 1u)
#define READ_TEXT_UPPER (1u << 2u)
#define N lineN++

static Time readTime(int line, bool optional) {
    RAW();
    uint8_t time[4] = {0, 0, 0, 0};
    int index = 0;

    color(A_BOLD, F_WHITE, B_MAGENTA);
    while (true) {
        pos(2, line);
        for (int i = 0; i < 4; ++i) {
            PC(i < index ? time[i] + '0' : ' ');
            if (i == 1) {
                PC(':');
            }
        }
        pos((index > 1 ? 3 : 2) + index, line);
        char c = (char) readCh();
        if (c == '\r') {
            Time t = index == 4 ? Time_new((uint8_t) (time[0] * 10 + time[1]), (uint8_t) (time[2] * 10 + time[3]))
                                : NULL;
            if (index == 4 || (optional && index == 0)) {
                DEFAULT_COLOR_RUNNING();
                UNRAW();
                return t;
            }
        } else if (c == BACKSPACE) {
            if (index > 0) {
                time[--index] = 0;
            }
        } else if ('0' <= c && c <= '9' && index < 4) {
            uint8_t d = (uint8_t) (c - '0');
#define C(x, y) if(index == (x) && (y)) continue;
            C(0, d > 2);
            C(1, time[0] == 2 && d > 3);
            C(2, d > 5);
#undef C
            time[index++] = d;
        }
    }
}

static DString readText(int line, int min, int max, uint8_t textType) {
    RAW();
    char *buffer = malloc(sizeof(char) * max + 1);
    memset(buffer, 0, max + 1UL);
    int index = 0;
    color(A_BOLD, F_WHITE, B_MAGENTA);
    pos(2, line);
    PF("%*c", max, ' ');
    while (true) {
        pos(2 + index, line);

        char c = (char) readCh();
        if (c == '\r') {
            if (index >= min) {
                buffer[index] = 0;
                DString d = DString_new(buffer);
                free(buffer);
                DEFAULT_COLOR_RUNNING();
                UNRAW();
                return d;
            }
        } else if (c == BACKSPACE && index > 0) {
            pos(1 + index, line);
            PC(' ');
            buffer[index--] = 0;
        } else if (index < max) {
            bool ok = false;
            if (textType & READ_TEXT && (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))) {
                if (textType & READ_TEXT_UPPER) {
                    c = UPPER(c);
                }
                ok = true;
            } else if (textType & READ_NUMBER && ('0' <= c && c <= '9')) {
                ok = true;
            }
            if (ok) {
                PC(c);
                buffer[index++] = c;
            }
        }
    }
}

static void printText(int line, char *text) {
    pos(1, line);
    P(text);
}

static int logCounter = 0;

static void LogVoo(Voo v) {
    uint32_t max = (uint32_t) rows / 6;
    if (!max) {
        max = 1;
    }
    if (logCounter++ == 0) {
        CLEAR();
        pos(0, 0);
    }
    if (logCounter > max) {
        logCounter = 0;
        readCh();
    }
    Voo_print(v);
}

static void InsertVoo(VooSchedule schedule) {
    uint8_t lineN = 2;

    printText(N, "Horario de decolagem");
    Time takeOffTime = readTime(N, false);
    printText(N, "Aeroporto de decolagem");
    DString takeOffAir = readText(N, 3, 3, READ_TEXT | READ_TEXT_UPPER);

    printText(N, "Horario de pouso");
    Time landingTime = readTime(N, false);
    printText(N, "Aeroporto de pouso");
    DString landingAir = readText(N, 3, 3, READ_TEXT | READ_TEXT_UPPER);

    printText(N, "Pista de pouso");
    DString pistaDePousoRaw = readText(N, 1, 2, READ_NUMBER);

    Voo voo = Voo_new(
            FlightData_new(
                    takeOffTime,
                    Aeroporto_get(DString_raw(takeOffAir)),
                    -1
            ),
            FlightData_new(
                    landingTime,
                    Aeroporto_get(DString_raw(landingAir)),
                    (int8_t) strtol(DString_raw(pistaDePousoRaw), NULL, 10)
            )
    );
    VooSchedule_insert(schedule, voo);

    DString_delete(pistaDePousoRaw);
    DString_delete(landingAir);
    DString_delete(takeOffAir);

    PF("\n\nVoo criado com o id %08X", Voo_getVid(voo).bits);
}

static void RemoveVoo(VooSchedule schedule) {
    printText(2, "ID do voo");
    DString id = readText(3, 8, 8, READ_TEXT | READ_NUMBER | READ_TEXT_UPPER);
    Voo voo = VooSchedule_remove(schedule, (VID) {
            .bits = (uint32_t) strtoul(DString_raw(id), NULL, 16)
    });
    pos(0, 5);
    if (voo) {
        PF("\nO voo %s foi removido\n", DString_raw(id));
        Voo_print(voo);
    } else {
        P("\nVoo nao encontrado");
    }
    DString_delete(id);
}

static void ProcuraVoo(VooSchedule schedule) {
    printText(2, "ID do voo");
    DString id = readText(3, 8, 8, READ_TEXT | READ_NUMBER | READ_TEXT_UPPER);
    Voo voo = VooSchedule_find(schedule, (VID) {
            .bits = (uint32_t) strtoul(DString_raw(id), NULL, 16)
    });
    pos(0, 5);
    if (voo) {
        Voo_print(voo);
    } else {
        P("\nVoo nao encontrado");
    }
    DString_delete(id);
}

static void ListVoo(VooSchedule schedule) {
    uint8_t lineN = 2;

    printText(N, "Horario de decolagem (opcional)");
    Time takeOffTime = readTime(N, true);
    printText(N, "Horario de pouso (opcional)");
    Time landingTime = readTime(N, true);
    DEFAULT_COLOR();
    pos(1, 1);
    P("Nenhum voo neste horario");
    DEFAULT_COLOR_RUNNING();
    logCounter = 0;
    VooSchedule_forEach(schedule, takeOffTime, landingTime, LogVoo);
}

static void PeakTime(VooSchedule schedule) {
    struct VooSchedule_SearchResult result = VooSchedule_findPeakTime(schedule);
    if (!VooScheduleItem_num(result.list)) {
        pos(1, 1);
        P("Nenhum voo cadastrado");
        return;
    }
    PF("Intervalo de pico:"
       "\n> Decolagem %02dH"
       "\n> Pouso %02dH"
       "\n> Numero de voos: %d",
       result.takeOff, result.landing,
       VooScheduleItem_num(result.list)
    );
}


static void OffPeakTime(VooSchedule schedule) {
    struct VooSchedule_SearchResult result = VooSchedule_findOffPeakTime(schedule);
    if (!VooScheduleItem_num(result.list)) {
        pos(1, 1);
        P("Nenhum voo cadastrado");
        return;
    }
    PF("Intervalo menos movimentado:"
       "\n> Decolagem %02dH"
       "\n> Pouso %02dH"
       "\n> Numero de voos: %d",
       result.takeOff, result.landing,
       VooScheduleItem_num(result.list)
    );
}


static void MostRecentUpdated(VooSchedule schedule) {
    struct VooSchedule_SearchResult result = VooSchedule_findMostRecentUpdated(schedule);
    Time t = VooScheduleItem_getLastUpdate(result.list);
    if (!VooScheduleItem_num(result.list)) {
        pos(1, 1);
        P("Nenhum voo cadastrado");
        return;
    }
    PF("Ultima lista alterada:"
       "\n> Decolagem %02dH"
       "\n> Pouso %02dH"
       "\n> Horario: %02d:%02d",
       result.takeOff, result.landing,
       Time_getHour(t), Time_getMinute(t)
    );
}


static void LessMostRecentUpdated(VooSchedule schedule) {
    struct VooSchedule_SearchResult result = VooSchedule_findLessRecentUpdated(schedule);
    Time t = VooScheduleItem_getLastUpdate(result.list);
    if (!VooScheduleItem_num(result.list)) {
        pos(1, 1);
        P("Nenhum voo cadastrado");
        return;
    }
    PF("Lista a mais tempo sem alterar:"
       "\n> Decolagem %02dH"
       "\n> Pouso %02dH"
       "\n> Horario: %02d:%02d",
       result.takeOff, result.landing,
       Time_getHour(t), Time_getMinute(t)
    );
}

static void Sparse(VooSchedule schedule) {
    bool s = VooSchedule_isSparse(schedule);
    P("Esparca: ");
    DEFAULT_COLOR();
    P(s ? "Sim" : "Nao");
    DEFAULT_COLOR_RUNNING();
}

FILE *saving;

static void SaveIterator(Voo voo) {
    FlightData takeOff     = Voo_getTakeoff(voo);
    Time       takeOffTime = FlightData_getSchedule(takeOff);

    FlightData landing     = Voo_getLanding(voo);
    Time       landingTime = FlightData_getSchedule(landing);

    fprintf(
            saving,
            "b %02d:%02d %02d:%02d %s %s %d\n",
            Time_getHour(takeOffTime), Time_getMinute(takeOffTime),
            Time_getHour(landingTime), Time_getMinute(landingTime),
            Aeroporto_getName(FlightData_getAirport(takeOff)),
            Aeroporto_getName(FlightData_getAirport(landing)),
            FlightData_getRunway(landing)
    );
}

static void Save(VooSchedule schedule) {
    printText(2, "Nome do arquivo");
    DString fileName = readText(3, 1, 60, READ_TEXT | READ_NUMBER);
    saving = fopen(DString_raw(fileName), "w");
    DEFAULT_COLOR();
    pos(4, 4);
    if (!saving) {
        P("Nao foi possivel abrir o arquivo %s");
    } else {
        fprintf(saving, "a\n");
        VooSchedule_forEach(schedule, NULL, NULL, SaveIterator);
        fprintf(saving, "gui\n");
        P("Salvo com sucesso");
        fclose(saving);
    }
    DString_delete(fileName);
}

static void Exit(__attribute__((unused)) VooSchedule schedule) {
    exit(0);
}

struct Action actions[] = {
        {"Inserir voo",                   InsertVoo},
        {"Remover voo",                   RemoveVoo},
        {"Procurar voo",                  ProcuraVoo},
        {"Listar voos",                   ListVoo},
        {"Horario de maior movimentacao", PeakTime},
        {"Horario de menor movimentacao", OffPeakTime},
        {"Lista recentemente alterada",   MostRecentUpdated},
        {"Lista alterada a mais tempo",   LessMostRecentUpdated},
        {"Matriz esparca?",               Sparse},
        {"Salvar em arquivo",             Save},
        {"Sair",                          Exit}
};

int numOfActions() {
    return sizeof(actions) / sizeof(struct Action);
}
