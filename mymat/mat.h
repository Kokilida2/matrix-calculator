/* in case of a double definition */
#ifndef _MAT_H
#define _MAT_H
/* defining matrices */
#define MAT_LENGTH 4
typedef double mat[MAT_LENGTH][MAT_LENGTH];

/* reads the array of 16 floats into the matrix */
void readmat(mat *, double[MAT_LENGTH*MAT_LENGTH]);
/* prints the matrix */
void printmat(mat *);
/*  adds the first two matrices and stores the result in the third matrix */
void addmat(mat *, mat *, mat *);
/*  subtracts the second matrix from the second and stores the result in the third */
void submat(mat *, mat *, mat *);
/*  multiplies the first two matrices and stores the result in the third matrix */
void mulmat(mat *, mat *, mat *);
/*  multiplies the first matrix by a float scalar and stores the result in the third matrix */
void mulscalar(mat *, double, mat *);
/*  transitions the first matrix and stores the result in the second matrix */
void transmat(mat *, mat *);

#endif /* mat.h */