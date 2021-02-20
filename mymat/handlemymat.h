/* Written by Lior Shaked 326584125 */

/* in case of a double definition */
#ifndef _HANDLEMYMAT_H
#define _HANDLEMYMAT_H

/* defining command names */
#define READ_MAT_CMD "read_mat"
#define PRINT_MAT_CMD "print_mat"
#define ADD_MAT_CMD "add_mat" 
#define SUB_MAT_CMD "sub_mat" 
#define MUL_MAT_CMD "mul_mat" 
#define MUL_SCALAR_CMD "mul_scalar" 
#define TRANS_MAT_CMD "trans_mat"
#define HELP_CMD "help" 
#define STOP_CMD "stop" 

/* matrix names form */
#define PREFIX "MAT_"

/* max line length */
#define INPUTLENGTH 10000

/* including mat.h in order to be able to use the matrix variable */
#include "mat.h"


/* NOTE: all handle functions except for the hadnlestop function must get the array of matrices as a parameter
 * also, their return values are "1" if the program was succesful and "0" if not. 
 */

/* reads the matrix from the user, handles errors, and prints the matrix */ 
int handleprintmat(mat **);

/* reads the matrix and the numbers from the user, handles errors, and reads them into the matrix */
int handlereadmat(mat **);

/* reads the matrices from the user, handles errors, and adds the matrices */
int handleaddmat(mat **);

/* reads the matrices from the user, handles errors, and subtracts the matrices */
int handlesubmat(mat **);

/* reads the matrices from the user, handles errors, and multiplies the matrices */
int handlemulmat(mat **);

/* reads the matrices and scalar from the user, handles errors, and multiplies the matrix by the scalar */
int handlemulscalar(mat **);

/* reads the matrix from the user, handles errors, and prints the matrix */
int handletransmat(mat **);

/* makes sure the stop command is valid */
int handlestop();

/* returns the index in the matrix array of the matrix with the name recieved. matrix names of the form "MAT_%c" */
int mat_to_idx(char *);

/* returns 1 if the string is a double, 0 if not */
int valid_string_to_double(char *);

/* reads a matrix and returns it's index. could be seen as: mattoidx(readnextarg()) */
int read_mat_idx();

/* return 1 if there are no more arguments into the input line. else returns 0 */
int no_more_args();

/* reads the next **argument** from the command line - not the first "string between commas" but also converts it into a variable. */
char* read_next_arg();

/* makes sure there are no two or more commas in a row and that there isn't an extra comma */
int commas_valid(char *);

/* strips the string: gets rid of white space in the start and end of the first string and stores the result in the second string*/
char* strip(char *, char *);

/* prints the commands */
int handlehelp();

#endif /* handlemymat.h */
