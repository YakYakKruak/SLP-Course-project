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
} point;

int init() {
    count = psmove_count_connected();

    printf("### Found %d controllers.\n", count);
    if (count != 1) {
        return 1;
    }

    controllers = (PSMove **)calloc(count, sizeof(PSMove *));

    int result;

    fprintf(stderr, "Trying to init PSMoveTracker...");
    PSMoveTrackerSettings settings;
    psmove_tracker_settings_set_default(&settings);
    settings.color_mapping_max_age = 0;
    settings.exposure_mode = Exposure_LOW;
    settings.camera_mirror = PSMove_True;
    tracker = psmove_tracker_new_with_settings(&settings);

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

        for (;;) {
            printf("Calibrating controller %d...", i);
            fflush(stdout);
            result = psmove_tracker_enable(tracker, controllers[i]);

            if (result == Tracker_CALIBRATED) {
                enum PSMove_Bool auto_update_leds =
                        psmove_tracker_get_auto_update_leds(tracker,
                                                            controllers[i]);
                printf("OK, auto_update_leds is %s\n",
                       (auto_update_leds == PSMove_True)?"enabled":"disabled");
                break;
            } else {
                printf("ERROR - retrying\n");
            }
        }
    }

    return 0;
}

point get_point() {
    psmove_tracker_update_image(tracker);
    psmove_tracker_update(tracker, NULL);
    psmove_tracker_annotate(tracker);
    float x, y, r;
    psmove_tracker_get_position(tracker, controllers[0], &x, &y, &r);
    printf("x: %10.2f, y: %10.2f, r: %10.2f\n", x, y, r);
    point p;
    p.x = x;
    p.y = y;
    p.r = r;
    return p;

}

JNIEXPORT jint JNICALL Java_frontend_jni_PSMoveManager_init(JNIEnv * env, jobject obj) {
    return  init();
}


JNIEXPORT jintArray JNICALL Java_frontend_jni_PSMoveManager_getPoint(JNIEnv * env, jobject obj) {
    jintArray array = (*env)->NewIntArray(env,3);
    if (!array) {
        return NULL; /* out of memory error thrown */
    }
    jint arr[3];
    point p = get_point();
    arr[0] = (int)p.x;
    arr[1] = (int)p.y;
    arr[2] = (int)p.r;
    (*env)->SetIntArrayRegion(env, array, 0, 3, arr);
    return array;
}




int clear_all() {
    for (int i=0; i<count; i++) {
        psmove_disconnect(controllers[i]);
    }
    psmove_tracker_free(tracker);
    free(controllers);
}