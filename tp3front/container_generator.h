//
// Created by vinic on 12/6/2018.
//

#ifndef AIRPORT_CONTROL_FILE_PARSER_H
#define AIRPORT_CONTROL_FILE_PARSER_H

#include <stdio.h>
#include "../common/VooScheduleContainer.h"

struct DataInfo {
    size_t vectorSize, toFill, eachMatrix;
};

bool parse_file(struct DataInfo info, FILE *file, VSContainer* output);

VSContainer random_data(struct DataInfo info);

#endif //AIRPORT_CONTROL_FILE_PARSER_H
