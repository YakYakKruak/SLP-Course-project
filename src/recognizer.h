//
// Created by yakov on 23.01.18.
//

#ifndef SLP_COURSE_PROJECT_RECOGNIZER_H
#define SLP_COURSE_PROJECT_RECOGNIZER_H

#include <capi.h>
#include <allheaders.h>

int init_recognizer(void);

char * recognize_text(void);

void free_recognizer(void);

#endif //SLP_COURSE_PROJECT_RECOGNIZER_H
