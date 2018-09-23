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
		for(int i = 0; i < 4; ++i) {
			PC(time[i] + '0');
			if(i == 1) {
				PC(':');
			}
		}
		pos((index > 1 ? 3 : 2) + index, line);
		char c = readCh();
		if (c == '\r') {
			Time t = index == 4 ? Time_new(time[0] * 10 + time[1], time[2] * 10 + time[3]) : NULL;
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
			int d = c - '0';
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
	memset(buffer, 0, max + 1);
	int index = 0;
	color(A_BOLD, F_WHITE, B_MAGENTA);
	pos(2, line);
	PF("%*c", max, ' ');
	while (true) {
		pos(2 + index, line);

		char c = readCh();
		if(c == '\r') {
			if(index >= min) {
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
		} else if(index < max) {
			bool ok = false;
            if (textType & READ_TEXT && (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'))) {
				if(textType & READ_TEXT_UPPER) {
					c = UPPER(c);
				}
				ok = true;
			} else if(textType & READ_NUMBER && ('0' <= c && c <= '9')) {
				ok = true;
			}
			if (ok) {
				PC(c);
				buffer[index++] = c;
			}
		}
	}
}

static void printText(int line, char* text) {
	pos(1, line);
	P(text);
}

static void PRINT3(__attribute__((unused)) VooSchedule nothing) {
    PRINTLN("TEST STR");
    PRINTLN("TEST STR");
    PRINTLN("TEST STR");
    PRINTLN("TEST STR");
	DString s = readText(6, 4, 30, READ_TEXT);
	PF("\nTyped %s\n", DString_raw(s));
	readTime(8, true);
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
			strtol(DString_raw(pistaDePousoRaw), NULL, 10)
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
		.bits = (uint32_t) strtol(DString_raw(id), NULL, 16)
	});
	if (voo) {
        PF("\nO voo %s foi removido\n", DString_raw(id));
		Voo_print(voo);
	}
	else {
		P("\nVoo nao encontrado");
	}
	DString_delete(id);
}

#define NOP PRINT3
struct Action actions[] = {
        {"Test", PRINT3},
        {"Inserir voo", InsertVoo},
        {"Remover voo", RemoveVoo},
        {"Procurar voo", NOP},
        {"Listar voos", NOP},
        {"Horario de maior movimentacao", NOP},
        {"Horario de menor movimentacao", NOP},
        {"Lista recentemente alterada", NOP},
        {"Lista alterada a mais tempo", NOP},
        {"Matriz esparca?", NOP},
		{"Salvar em arquivo", NOP}
};

int numOfActions() {
    return sizeof(actions) / sizeof(struct Action);
}
