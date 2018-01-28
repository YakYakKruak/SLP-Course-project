//
// Created by yakov on 23.01.18.
//

#ifndef SLP_COURSE_PROJECT_MOVE_H
#define SLP_COURSE_PROJECT_MOVE_H

#include <stdio.h>
#include <stdlib.h>
#include <psmove_tracker.h>

struct state {
    float x;
    float y;
    int buttons;
};

struct state get_state(void);

int init_move(void);

void free_move(void);

#endif //SLP_COURSE_PROJECT_MOVE_H
