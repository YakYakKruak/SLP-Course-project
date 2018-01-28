//
// Created by yakov on 23.01.18.
//

#include "recognizer.h"

static TessBaseAPI *tess;

int init_recognizer(void) {
    tess = TessBaseAPICreate();
    if(TessBaseAPIInit3(tess, NULL, "eng") != 0)
        return 1;
    return 0;
}

char * recognize_text(void) {
    PIX *img;
    char *text;

    if((img = pixRead("paint.png")) == NULL)
        return NULL;

    TessBaseAPISetImage2(tess, img);

    if(TessBaseAPIRecognize(tess, NULL) != 0)
        return NULL;

    if((text = TessBaseAPIGetUTF8Text(tess)) == NULL)
        return NULL;

    pixDestroy(&img);

    return text;
}

void free_recognizer(void) {
    TessBaseAPIEnd(tess);
    TessBaseAPIDelete(tess);
}
