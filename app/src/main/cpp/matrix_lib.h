#ifndef MATRIX_LIB_H
#define MATRIX_LIB_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jobjectArray JNICALL
Java_com_example_matrixcalc_MainActivity_operateMatrices(
        JNIEnv *, jobject, jobjectArray, jobjectArray, jint);

#ifdef __cplusplus
}
#endif

#endif // MATRIX_LIB_H
