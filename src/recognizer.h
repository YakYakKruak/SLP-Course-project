//
// Created by yakov on 23.01.18.
//

#ifndef SLP_COURSE_PROJECT_RECOGNIZER_H
#define SLP_COURSE_PROJECT_RECOGNIZER_H

#include <capi.h>
#include <allheaders.h>

int init_recognizer();

char * recognize_text();

void free_recognizer();

#endif //SLP_COURSE_PROJECT_RECOGNIZER_H
