//
// Created by yakov on 26.11.17.
//
#include "move.h"

JNIEXPORT void JNICALL Java_frontend_jni_PSMoveManager_close0(JNIEnv * env, jobject obj) {
    free_move();
}


JNIEXPORT jint JNICALL Java_frontend_jni_PSMoveManager_init0(JNIEnv * env, jobject obj) {
    return  init_move();
}

JNIEXPORT jintArray JNICALL Java_frontend_jni_PSMoveManager_getPoint0(JNIEnv * env, jobject obj) {
    jintArray array = (*env)->NewIntArray(env,3);

    if (!array)
        return NULL; /* out of memory error thrown */

    jint arr[3];
    state s = get_state();
    arr[0] = (int)s.x;
    arr[1] = (int)s.y;
    arr[2] = s.buttons;
    (*env)->SetIntArrayRegion(env, array, 0, 3, arr);
    return array;
}
