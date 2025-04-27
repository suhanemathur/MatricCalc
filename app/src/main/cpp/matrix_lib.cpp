#include <jni.h>
#include <vector>
#include <stdexcept>

using namespace std;

extern "C"
JNIEXPORT jobjectArray JNICALL
Java_com_example_matrixcalc_MainActivity_operateMatrices(
        JNIEnv *env, jobject, jobjectArray mat1, jobjectArray mat2, jint opCode) {

    jsize rows1 = env->GetArrayLength(mat1);
    jsize cols1 = env->GetArrayLength((jdoubleArray) env->GetObjectArrayElement(mat1, 0));
    jsize rows2 = env->GetArrayLength(mat2);
    jsize cols2 = env->GetArrayLength((jdoubleArray) env->GetObjectArrayElement(mat2, 0));

    // For Add/Subtract/Divide, dimensions must match
    if ((opCode == 0 || opCode == 1 || opCode == 3) &&
        (rows1 != rows2 || cols1 != cols2)) {
        throw runtime_error("Matrix dimensions must match for Add, Subtract, or Divide.");
    }

    // For Multiply: cols1 must equal rows2
    if (opCode == 2 && cols1 != rows2) {
        throw runtime_error("Invalid dimensions for multiplication: cols of Matrix 1 must equal rows of Matrix 2.");
    }

    vector<vector<double>> result;

    if (opCode == 2) {
        // Matrix multiplication: result = rows1 x cols2
        result.resize(rows1, vector<double>(cols2, 0.0));

        for (int i = 0; i < rows1; ++i) {
            jdoubleArray rowA = (jdoubleArray) env->GetObjectArrayElement(mat1, i);
            jdouble* a = env->GetDoubleArrayElements(rowA, nullptr);

            for (int j = 0; j < cols2; ++j) {
                for (int k = 0; k < cols1; ++k) {
                    jdoubleArray rowB = (jdoubleArray) env->GetObjectArrayElement(mat2, k);
                    jdouble* b = env->GetDoubleArrayElements(rowB, nullptr);

                    result[i][j] += a[k] * b[j];

                    env->ReleaseDoubleArrayElements(rowB, b, 0);
                }
            }

            env->ReleaseDoubleArrayElements(rowA, a, 0);
        }
    } else {
        // Element-wise Add/Subtract/Divide
        result.resize(rows1, vector<double>(cols1));

        for (int i = 0; i < rows1; ++i) {
            jdoubleArray rowA = (jdoubleArray) env->GetObjectArrayElement(mat1, i);
            jdoubleArray rowB = (jdoubleArray) env->GetObjectArrayElement(mat2, i);

            jdouble* a = env->GetDoubleArrayElements(rowA, nullptr);
            jdouble* b = env->GetDoubleArrayElements(rowB, nullptr);

            for (int j = 0; j < cols1; ++j) {
                switch (opCode) {
                    case 0: result[i][j] = a[j] + b[j]; break;
                    case 1: result[i][j] = a[j] - b[j]; break;
                    case 3:
                        if (b[j] == 0) throw runtime_error("Division by zero at element [$i][$j]");
                        result[i][j] = a[j] / b[j];
                        break;
                }
            }

            env->ReleaseDoubleArrayElements(rowA, a, 0);
            env->ReleaseDoubleArrayElements(rowB, b, 0);
        }
    }

    // Convert result to Java array
    jclass doubleArrayClass = env->FindClass("[D");
    jobjectArray resultArray = env->NewObjectArray(result.size(), doubleArrayClass, nullptr);

    for (int i = 0; i < result.size(); ++i) {
        jdoubleArray row = env->NewDoubleArray(result[i].size());
        env->SetDoubleArrayRegion(row, 0, result[i].size(), result[i].data());
        env->SetObjectArrayElement(resultArray, i, row);
    }

    return resultArray;
}
