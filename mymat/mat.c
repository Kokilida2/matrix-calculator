/* Written by Lior Shaked 326584125 */

#include <stdio.h>
#include "mat.h"

void readmat(mat *readinto, double input[MAT_LENGTH * MAT_LENGTH]) {
    /* pointers to the matrix */
    int i, j;

    /* pointer to the input array */
    int k = 0;

    for (i = 0; i < MAT_LENGTH; i++) {
        for (j = 0; j < MAT_LENGTH; j++) {
            (*readinto)[i][j] = input[k++];
        }
    }
}

void printmat(mat *m) {
    /* pointers to the matrix */
    int i, j;

    for (i = 0; i < MAT_LENGTH; i++) {
        for (j = 0; j < MAT_LENGTH; j++) {
            /* printing the matrix */
            printf("%7.2f ", (*m)[i][j]);
        }
        printf("\n\t");
    }
    printf("\n");
}

void addmat(mat *mata, mat *matb, mat *matc) {
    /* pointers to the matrix */
    int i, j;

    for (i = 0; i < MAT_LENGTH; i++) {
        for (j = 0; j < MAT_LENGTH; j++) {
            /* adding the matrices */
            (*matc)[i][j] = (*mata)[i][j] + (*matb)[i][j];
        }
    }
}

void submat(mat *mata, mat *matb, mat *matc) {
    /* pointers to the matrix */
    int i, j;

    for (i = 0; i < MAT_LENGTH; i++) {
        for (j = 0; j < MAT_LENGTH; j++) {
            /* subtracting the matrices */
            (*matc)[i][j] = (*mata)[i][j] - (*matb)[i][j];
        }
    }
}

void mulmat(mat *mata, mat *matb, mat *matc) {
    /* pointers to the matrix */
    int i, j, k;

    /* in order to not modify matc until the end of the calculation - 
     * in case mata or matb are matc and the would get altered in the calculation
     */
    mat temp = {0};


    for (i = 0; i < MAT_LENGTH; i++) {
        for (j = 0; j < MAT_LENGTH; j++) {
            /* to calculate the multiplication of the matrices */
            double t = 0;
            for (k = 0; k < MAT_LENGTH; k++) {
                t += (*mata)[i][k] * (*matb)[k][j];
            }
            temp[i][j] = t;
        }
    }
    /* storing the result in matc */
    for (i = 0; i < MAT_LENGTH; i++) {
        for (j = 0; j < MAT_LENGTH; j++) {
            (*matc)[i][j] = temp[i][j];
        }
    }
}
void mulscalar(mat *mata, double scalar, mat *matb) {
    /* pointers to the matrix */
    int i, j;

    for (i = 0; i < MAT_LENGTH; i++) {
        for (j = 0; j < MAT_LENGTH; j++) {
            /* multiplying the matrix by the scalar */
            (*matb)[i][j] = (*mata)[i][j] * scalar;
        }
    }   
}

void transmat(mat *mata, mat *matb) {
    /* pointers to the matrix */
    int i, j;

    /* in order to not modify matb until the end of the calculation - 
     * in case mata is matb and the would get altered in the calculation
     */
    mat temp = {0};
    for (i = 0; i < MAT_LENGTH; i++) {
        for (j = 0; j < MAT_LENGTH; j++) {
            temp[i][j] = (*mata)[j][i];
        }
    }
    /* storing the result in matb */
    for (i = 0; i < MAT_LENGTH; i++) {
        for (j = 0; j < MAT_LENGTH; j++) {
            (*matb)[i][j] = temp[i][j];
        }
    }
}