//
// Created by yakov on 23.01.18.
//

#include "move.h"

static size_t count;

static PSMove **controllers;

static PSMoveTracker* tracker;

state get_point(void) {
    float x, y, radius;
    int click;
    int again;
    state p;

    do {
        again = 0;

        for (size_t i=0; i<count; i++) {

            int res = psmove_poll(controllers[i]);

            if (!res) {
                continue;
            }

            again++;

            psmove_tracker_get_position(tracker, controllers[i] , &x, &y, &radius);
            click = psmove_get_trigger(controllers[i]);
        }
    } while (again);

    psmove_tracker_update_image(tracker);
    psmove_tracker_update(tracker, NULL);
    p.x = x;
    p.y = y;
    p.buttons = click;
    return p;
}

int init_move(void) {
    count = psmove_count_connected();

    printf("### Found %lu controllers.\n", count);

    controllers = (PSMove **)calloc(count, sizeof(PSMove *));
    tracker = psmove_tracker_new();

    if (!tracker)
    {
        fprintf(stderr, "Could not init PSMoveTracker.\n");
        return 1;
    }

    puts("OK");

    for (size_t i=0; i < count; i++) {
        printf("Opening controller %lu\n", i);
        controllers[i] = psmove_connect_by_id(i);
        if(controllers[i] == NULL)
            return 1;
    }

    for (size_t i=0; i<count; i++) {
        while (psmove_tracker_enable(tracker, controllers[i]) != Tracker_CALIBRATED) {
            puts("ERROR - retrying");
        }
    }
}

int free_move(void) {
    for (size_t i=0; i<count; i++) {
        printf("Closing controller %lu\n" , i);
        psmove_disconnect(controllers[i]);
    }
    psmove_tracker_free(tracker);
    free(controllers);
}
