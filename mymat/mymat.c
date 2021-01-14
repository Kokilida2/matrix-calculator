/* Written by Lior Shaked 326584125 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "handlemymat.h"

int main() {
    mat MAT_A = {{0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}},
        MAT_B = {{0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}},
        MAT_C = {{0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}},
        MAT_D = {{0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}},
        MAT_E = {{0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}},
        MAT_F = {{0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}};

    mat * mats[6];
    char *cmd;
    char input[INPUTLENGTH];
    char strippedinputarr[INPUTLENGTH];
    char *strippedinput;
    mats[0] = &MAT_A;
    mats[1] = &MAT_B;
    mats[2] = &MAT_C;
    mats[3] = &MAT_D;
    mats[4] = &MAT_E;
    mats[5] = &MAT_F;
    strippedinput = strippedinputarr;
    while (1) {
        printf(">> ");
        fgets(input, INPUTLENGTH, stdin);
        if (!strcmp(input, "")) {
            printf("ERROR, reached end of file without \"stop\" command\n");
            return 1;
        }
        strippedinput = strip(input, strippedinputarr);
        printf("Your command: [%s]\n", strippedinput);
        if (commas_valid(strippedinput)) {
            cmd = strtok(strippedinput, " \t\n");
            if(cmd !=  NULL) {
                /* read_mat command */
                if (!strcmp(cmd, READ_MAT_CMD)) {
                    handlereadmat(mats);
                } else if (!strcmp(cmd, PRINT_MAT_CMD)) {
                    handleprintmat(mats);
                } else if (!strcmp(cmd, ADD_MAT_CMD)) {
                    handleaddmat(mats);
                } else if (!strcmp(cmd, SUB_MAT_CMD)) {
                    handlesubmat(mats);
                } else if (!strcmp(cmd, MUL_MAT_CMD)) {
                    handlemulmat(mats);  
                } else if (!strcmp(cmd, MUL_SCALAR_CMD)) {
                    handlemulscalar(mats);
                } else if (!strcmp(cmd, TRANS_MAT_CMD)) { 
                    handletransmat(mats);
                } else if (!strcmp(cmd, STOP_CMD)) {
                    if (handlestop()) break;
                } else {
                    printf("Unrecognized command\n");
                }
            }
        }
    }
    printf("Goodbye!\n");
    printf("-Matrix Calculator by Lior Shaked-\n");
    return 0;
}
