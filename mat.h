#ifndef _MAT_H
#define _MAT_H
#define MAT_LENGTH 4
typedef double mat[4][4];
void readmat(mat *, double[MAT_LENGTH*MAT_LENGTH]);
void printmat(mat *);
void addmat(mat *, mat *, mat *);
void submat(mat *, mat *, mat *);
void mulmat(mat *, mat *, mat *);
void mulscalar(mat *, double, mat *);
void transmat(mat *, mat *);
#endif