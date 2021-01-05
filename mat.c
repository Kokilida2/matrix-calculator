#include <stdio.h>
#include "mat.h"

void readmat(mat *readinto, double input[MAT_LENGTH * MAT_LENGTH]) {
    int i, j;
    int k = 0;
    for (i = 0; i < MAT_LENGTH; i++) {
        for (j = 0; j < MAT_LENGTH; j++) {
            (*readinto)[i][j] = input[k++];
        }
    }
}

void printmat(mat *m) {
    int i, j;
    for (i = 0; i < MAT_LENGTH; i++) {
        for (j = 0; j < MAT_LENGTH; j++) {
            printf("%7.2f ", (*m)[i][j]);
        }
        printf("\n\t");
    }
    printf("\n");
}

void addmat(mat *mata, mat *matb, mat *matc) {
    int i, j;
    for (i = 0; i < MAT_LENGTH; i++) {
        for (j = 0; j < MAT_LENGTH; j++) {
            (*matc)[i][j] = (*mata)[i][j] + (*matb)[i][j];
        }
    }
}

void submat(mat *mata, mat *matb, mat *matc) {
    int i, j;
    for (i = 0; i < MAT_LENGTH; i++) {
        for (j = 0; j < MAT_LENGTH; j++) {
            (*matc)[i][j] = (*mata)[i][j] - (*matb)[i][j];
        }
    }
}

void mulmat(mat *mata, mat *matb, mat *matc) {
    int i, j, k;
    mat temp = {0};
    for (i = 0; i < MAT_LENGTH; i++) {
        for (j = 0; j < MAT_LENGTH; j++) {
            double t = 0;
            for (k = 0; k < MAT_LENGTH; k++) {
                t += (*mata)[i][k] * (*matb)[k][j];
            }
            temp[i][j] = t;
        }
    }
    for (i = 0; i < MAT_LENGTH; i++) {
        for (j = 0; j < MAT_LENGTH; j++) {
            (*matc)[i][j] = temp[i][j];
        }
    }
}
void mulscalar(mat *mata, double scalar, mat *matb) {
    int i, j;
    for (i = 0; i < MAT_LENGTH; i++) {
        for (j = 0; j < MAT_LENGTH; j++) {
            (*matb)[i][j] = (*mata)[i][j] * scalar;
        }
    }   
}

void transmat(mat *mata, mat *matb) {
    int i, j;
    mat temp = {0};
    for (i = 0; i < MAT_LENGTH; i++) {
        for (j = 0; j < MAT_LENGTH; j++) {
            temp[i][j] = (*mata)[j][i];
        }
    }
    for (i = 0; i < MAT_LENGTH; i++) {
        for (j = 0; j < MAT_LENGTH; j++) {
            (*matb)[i][j] = temp[i][j];
        }
    }
}