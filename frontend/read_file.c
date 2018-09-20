#include "read_file.h"
#include "../base.h"
#include "../FIFTH/src/vm.h"
#include "../FIFTH/src/lexer.h"
#include "custom_words.h"

static DString ReplaceHour(DString line) {
    char *rawLine = DString_raw(line);
    unsigned long rawLength = DString_length(line);

    DString newLine = DString_new("");

    int start = 0;
    int end = (int) rawLength;

    while (rawLine[start++] == ' ');
    while (rawLine[end--] == ' ' || rawLine[end] == '\n' || rawLine[end] == '\r');
    start--;
    end++;

    for (int i = 0; i < start; ++i) {
        DString_appendChar(newLine, ' ');
    }
    enum {
        NONE, STR
    } state = NONE;
    for (int i = start; i < end - 2; ++i) {
        char c = rawLine[i];
        switch (state) {
            case NONE: {
                if (c == ' ') {
                    DString_appendChar(newLine, c);
                } else {
                    DString_appendChar(newLine, '"');
                    DString_appendChar(newLine, c);
                    state = STR;
                }
            }
                break;
            case STR: {
                if (c == ' ') {
                    DString_appendChar(newLine, '"');
                    state = NONE;
                }
                DString_appendChar(newLine, c);
            }
                break;
        }
    }
    DString sub = DString_substr(line, -3, -1);
    DString_append(newLine, sub);
    DString_delete(sub);
    DString_delete(line);
    return newLine;
}

static void RunCode(DString data, char *fileName) {
    VmState vm = CreateVm();
    RegisterAirportWords();
    Lexer(vm, fileName, DString_raw(data), DString_length(data));
    RunVm(vm);
}

int ParseFile(char *fileName) {

    char *buffer;
    {
        FILE *f;
        if ((f = fopen(fileName, "r")) == NULL) {
            ERRORLN("Could not open %s for reading", fileName);
            return 1;
        }
        fseek(f, 0, SEEK_END);
        unsigned long length = (unsigned long) ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = malloc(length + 2);
        if (buffer == NULL)
            FATAL("Could not allocate memory for file reading");
        buffer[length] = '\n';
        buffer[length + 1] = 0;
        fread(buffer, 1, length, f);
        fclose(f);
    }
    //  file reading

    DString input = DString_create(buffer);
    DString output = DString_new("");

    enum {
        NEW_LINE,
        CUSTOM, NORMAL
    } state = NEW_LINE;

    unsigned long start = 0;
    unsigned long pos = 0;

    char c = UPPER(buffer[0]);
    do {
        if (state == NEW_LINE) {
            if (c != '\n' && c != '\r' && c != ' ') {
                char cNext = buffer[pos + 1];
                state = ('a' <= c && c <= 'm' && (cNext == ' ' || cNext == '\n' || cNext == '\r')) ? CUSTOM : NORMAL;
                start = pos;
            } else {
                DString_appendChar(output, c);
            }
        } else if (c == '\n') {
            char tmp = buffer[pos];
            buffer[pos] = 0;
            if (state == NORMAL) {
                DString line = DString_create(buffer + start);
                DString_append(output, line);
                free(line); // Free instead of DString_delete to not clear internal buffer
            } else { // CUSTOM
                DString line = DString_new(buffer + start);
                DString customLine = DString_substr(line, buffer[start + 1] == ' ' ? 2 : 1, -1);
                DString_appendChar(customLine, ' ');
                DString_appendChar(customLine, 'T');
                DString_appendChar(customLine, DString_raw(line)[0]);
                DString_delete(line);
                customLine = ReplaceHour(customLine);
                DString_append(output, customLine);
                DString_delete(customLine);
            }
            DString_appendChar(output, '\n');
            buffer[pos] = tmp;
            state = NEW_LINE;
        }
    } while ((c = buffer[++pos]) != '\0');

    DString_delete(input);
    RunCode(output, fileName);
    DString_delete(output);
    return 0;
}
