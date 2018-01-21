//
// Created by yakov on 26.11.17.
//
#include <stdio.h>
#include <stdlib.h>
#include <psmove_tracker.h>
#include <assert.h>
#include "frontend_jni_PSMoveManager.h"

size_t count;

PSMove **controllers;

PSMoveTracker* tracker;


typedef struct point {
    float x;
    float y;
    int buttons;
} point;


point get_point() {
    float x, y, radius;
    int click;
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

int init() {
    count = psmove_count_connected();

    printf("### Found %lu controllers.\n", count);

    controllers = (PSMove **)calloc(count, sizeof(PSMove *));
    tracker = psmove_tracker_new();

    if (!tracker)
    {
        fprintf(stderr, "Could not init PSMoveTracker.\n");
        return 1;
    }

    printf("OK\n");

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

int clear_all() {
    for (int i=0; i<count; i++) {
        printf("Closing controller %d\n" , i);
        psmove_disconnect(controllers[i]);
    }
    psmove_tracker_free(tracker);
    free(controllers);
}


JNIEXPORT void JNICALL Java_frontend_jni_PSMoveManager_close0(JNIEnv * env, jobject obj) {
    clear_all();
}


JNIEXPORT jint JNICALL Java_frontend_jni_PSMoveManager_init0(JNIEnv * env, jobject obj) {
    return  init();
}

JNIEXPORT jintArray JNICALL Java_frontend_jni_PSMoveManager_getPoint0(JNIEnv * env, jobject obj) {
    jintArray array = (*env)->NewIntArray(env,3);
    if (!array) {
        return NULL; /* out of memory error thrown */
    }
    jint arr[3];
    point p = get_point();
    arr[0] = (int)p.x;
    arr[1] = (int)p.y;
    arr[2] = p.buttons;
    (*env)->SetIntArrayRegion(env, array, 0, 3, arr);
    return array;
}
