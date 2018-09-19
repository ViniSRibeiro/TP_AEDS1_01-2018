//
// Created by viniciuslrangel on 19/09/18.
//

#include "custom_words.h"
#include "../FIFTH/src/words.h"
#include "../common/VooSchedule.h"

static VooSchedule item = NULL;

static void OperationA() {
    if(item != NULL) {
        VooSchedule_delete(item);
    }
    item = VooSchedule_new();
}

static void OperationB() {

}

void RegisterCustomWords() {
    struct WordEntry wordEntry[] = {
            {"TA", OperationA},
            {"TB", OperationB},
            {"TC", OperationC},
            {"TD", OperationD},
            {"TE", OperationE},
            {"TF", OperationF},
            {"TG", OperationG},
            {"TH", OperationH},
            {"TI", OperationI},
            {"TJ", OperationJ},
            {"TK", OperationK},
            {"TL", OperationL},
            {"TM", OperationM},
    };
    RegisterWords(wordEntry, sizeof(wordEntry) / sizeof(struct WordEntry));
}
