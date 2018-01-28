//
// Created by yakov on 26.11.17.
//
#include "move.h"
#include "recognizer.h"
#include "frontend_jni_JniHelper.h"


JNIEXPORT jstring JNICALL Java_frontend_jni_JniHelper_recognize0(JNIEnv * env, jobject obj) {
    char * string = recognize_text();
    if(!string)
        return NULL;
    jstring res = (*env)->NewStringUTF(env, string);
    return res;
}

JNIEXPORT void JNICALL Java_frontend_jni_JniHelper_close0(JNIEnv * env, jobject obj) {
    free_move();
    free_recognizer();
}


JNIEXPORT jint JNICALL Java_frontend_jni_JniHelper_init0(JNIEnv * env, jobject obj) {
    if(init_move())
        return 1;
    if(init_recognizer())
        return 1;
    return 0;
}

JNIEXPORT jintArray JNICALL Java_frontend_jni_JniHelper_getPoint0(JNIEnv * env, jobject obj) {
    jintArray array = (*env)->NewIntArray(env,3);

    if (!array)
        return NULL; /* out of memory error thrown */

    jint arr[3];
    struct state s = get_state();
    arr[0] = (int)s.x;
    arr[1] = (int)s.y;
    arr[2] = s.buttons;
    (*env)->SetIntArrayRegion(env, array, 0, 3, arr);
    return array;
}
