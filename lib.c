//
// Created by yakov on 26.11.17.
//
#include <stdio.h>
#include <stdlib.h>
#include <psmove_tracker.h>
#include <assert.h>
#include "psmove.h"

int count;

PSMove **controllers;

PSMoveTracker* tracker;


typedef struct point {
    float x;
    float y;
    float r;
    int buttons;
} point;

point get_point() {
    int res = psmove_poll(controllers[0]);
    point p;

    if (!res) {
        return p;
    }

    float x, y, r;
    psmove_tracker_get_position(tracker, controllers[0], &x, &y, &r);
    p.x = x;
    p.y = y;
    p.r = r;
    p.buttons = psmove_get_trigger(controllers[0]);
    psmove_tracker_update_image(tracker);
    psmove_tracker_update(tracker, NULL);

    return p;
}

int main() {
    count = psmove_count_connected();

    printf("### Found %d controllers.\n", count);
    if (count != 1) {
        return 1;
    }

    controllers = (PSMove **)calloc(count, sizeof(PSMove *));
    tracker = psmove_tracker_new();

    if (!tracker)
    {
        fprintf(stderr, "Could not init PSMoveTracker.\n");
        return 1;
    }

    fprintf(stderr, "OK\n");

    for (int i=0; i < count; i++) {
        printf("Opening controller %d\n", i);
        controllers[i] = psmove_connect_by_id(i);
        assert(controllers[i] != NULL);
    }

    for (int i=0; i<count; i++) {
        while (psmove_tracker_enable(tracker, controllers[i]) != Tracker_CALIBRATED) {
                printf("ERROR - retrying\n");

        }
    }

    while (1) {
        int again;

        do {
            again = 0;

            for (int i=0; i<count; i++) {

                int res = psmove_poll(controllers[i]);

                if (!res) {
                    continue;
                }

                again++;

                float x, y, radius;
                int butt;
                psmove_tracker_get_position(tracker, controllers[i] , &x, &y, &radius);
                butt = psmove_get_trigger(controllers[i]);
                printf("x: %f , y: %f , r: %f , buttons : %d\n",x,y,radius,butt);

            }
        } while (again);

        psmove_tracker_update_image(tracker);
        psmove_tracker_update(tracker, NULL);

    }


//    while (1) {
//        point p = get_point();
//        printf("x: %f , y: %f , r: %f , buttons : %d\n",p.x,p.y,p.r,p.buttons);
//        printf("buttons : %d\n", p.buttons);
//    }

}

int clear_all() {
    for (int i=0; i<count; i++) {
        psmove_disconnect(controllers[i]);
    }
    psmove_tracker_free(tracker);
    free(controllers);
}