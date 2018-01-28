//
// Created by yakov on 23.01.18.
//

#include "move.h"

struct global_state {
    size_t count;
    PSMove **controllers;
    PSMoveTracker* tracker;
};

static struct global_state current_state;

struct state get_state(void) {
    float x, y, radius;
    int click;
    int again;
    struct state s;

    do {
        again = 0;

        for (size_t i = 0; i < current_state.count; i++) {

            int res = psmove_poll(current_state.controllers[i]);

            if (!res) {
                continue;
            }

            again++;

            psmove_tracker_get_position(current_state.tracker, current_state.controllers[i] , &x, &y, &radius);
            click = psmove_get_trigger(current_state.controllers[i]);
        }
    } while (again);

    psmove_tracker_update_image(current_state.tracker);
    psmove_tracker_update(current_state.tracker, NULL);
    s.x = x;
    s.y = y;
    s.buttons = click;
    return s;
}

int init_move(void) {
    current_state.count = psmove_count_connected();

    fprintf(stderr,"### Found %lu controllers.\n", current_state.count);

    current_state.controllers = (PSMove **)calloc(current_state.count, sizeof(PSMove *));
    current_state.tracker = psmove_tracker_new();

    if (!current_state.tracker)
    {
        fprintf(stderr, "Could not init PSMoveTracker.\n");
        return 1;
    }

    fputs("OK",stderr);

    for (size_t i = 0; i < current_state.count; i++) {
        fprintf(stderr,"Opening controller %lu\n", i);
        current_state.controllers[i] = psmove_connect_by_id(i);
        if(current_state.controllers[i] == NULL)
            return 1;
    }

    for (size_t i = 0; i < current_state.count; i++) {
        while (psmove_tracker_enable(current_state.tracker, current_state.controllers[i]) != Tracker_CALIBRATED) {
            fputs("ERROR - retrying",stderr);
        }
    }
    return 0;
}

void free_move(void) {
    for (size_t i = 0; i < current_state.count; i++) {
        fprintf(stderr,"Closing controller %lu\n" , i);
        psmove_disconnect(current_state.controllers[i]);
    }
    psmove_tracker_free(current_state.tracker);
    free(current_state.controllers);
}
