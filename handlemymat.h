#ifndef _HANDLEMYMAT_H
#define _HANDLEMYMAT_H
#define READ_MAT_CMD "read_mat"
#define PRINT_MAT_CMD "print_mat"
#define ADD_MAT_CMD "add_mat"
#define SUB_MAT_CMD "sub_mat"
#define MUL_MAT_CMD "mul_mat"
#define MUL_SCALAR_CMD "mul_scalar"
#define TRANS_MAT_CMD "trans_mat"
#define STOP_CMD "stop"
#include "mat.h"
int handleprintmat(mat **);
int handlereadmat(mat **);
int handleaddmat(mat **);
int handlesubmat(mat **);
int handlemulmat(mat **);
int handlemulscalar(mat **);
int handletransmat(mat **);
int no_more_args();
char* read_next_arg();
int commas_valid(char *);
char* strip(char *);
#endif /* handlemymat.h */
