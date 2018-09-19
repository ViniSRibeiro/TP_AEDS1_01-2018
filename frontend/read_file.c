#include "read_file.h"
#include "../base.h"
#include "../FIFTH/src/vm.h"
#include "../FIFTH/src/lexer.h"
#include "custom_words.h"

static DString ReplaceHour(DString line) {
    if (DString_indexOf(line, ':') == -1) {
        return line;
    }
    char *rawLine = DString_raw(line);
    unsigned long rawLength = DString_length(line);
    int c = 0;
    for (int i = 0; i < rawLength; ++i) {
        if (rawLine[i] == ':') {
            c += 2;
        }
    }
    c += DString_length(line);
    char *newLine = malloc(sizeof(char) * c + 1);
    newLine[sizeof(char) * c] = 0;
    int j = 0;
    for (int i = 0; i < rawLength; ++i) {
        if (rawLine[i + 2 < rawLength ? i + 2 : '\0'] == ':') {
            newLine[j++] = '"';
            newLine[j++] = rawLine[i++];
            newLine[j++] = rawLine[i++];
            newLine[j++] = rawLine[i++];
            newLine[j++] = rawLine[i++];
            newLine[j++] = rawLine[i];
            newLine[j++] = '"';
        } else {
            newLine[j++] = rawLine[i];
        }
    }
    return DString_create(newLine);
}

static void RunCode(DString data, char *fileName) {
    VmState vm = CreateVm();
    RegisterCustomWords();
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

    char c = buffer[0];
    do {
        if (state == NEW_LINE) {
            if (c != '\n' && c != '\r') {
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
