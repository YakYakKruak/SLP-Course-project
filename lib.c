//
// Created by yakov on 26.11.17.
//
#include <stdio.h>
#include <stdlib.h>
#include <psmove_tracker.h>
#include <assert.h>
#include "psmove.h"
#include "frontend_jni_PSMoveManager.h"

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
    float x, y, radius;
    int butt;
    int again;
    point p;

    do {
        again = 0;

        for (int i=0; i<count; i++) {

            int res = psmove_poll(controllers[i]);

            if (!res) {
                continue;
            }

            again++;

            psmove_tracker_get_position(tracker, controllers[i] , &x, &y, &radius);
            butt = psmove_get_trigger(controllers[i]);
        }
    } while (again);

    psmove_tracker_update_image(tracker);
    psmove_tracker_update(tracker, NULL);
    p.x = x;
    p.y = y;
    p.r = radius;
    p.buttons = butt;
    return p;
}

int init() {
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
}


JNIEXPORT jint JNICALL Java_frontend_jni_PSMoveManager_init(JNIEnv * env, jobject obj) {
    return  init();
}


JNIEXPORT jintArray JNICALL Java_frontend_jni_PSMoveManager_getPoint(JNIEnv * env, jobject obj) {
    jintArray array = (*env)->NewIntArray(env,4);
    if (!array) {
        return NULL; /* out of memory error thrown */
    }
    jint arr[4];
    point p = get_point();
    arr[0] = (int)p.x;
    arr[1] = (int)p.y;
    arr[2] = (int)p.r;
    arr[3] = p.buttons;
    (*env)->SetIntArrayRegion(env, array, 0, 4, arr);
    return array;
}

int clear_all() {
    for (int i=0; i<count; i++) {
        psmove_disconnect(controllers[i]);
    }
    psmove_tracker_free(tracker);
    free(controllers);
}