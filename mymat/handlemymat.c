/* Written by Lior Shaked 326584125 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "handlemymat.h"
#include "mat.h"

/*returns 0 for MAT_A, 1 for MAT_B, ..., 5 for MAT_F
 * returns -1 if unrecognized matrix name
 */
int mat_to_idx(char *mat_name) {
    int prefix_len = strlen(PREFIX);

    /* if the string is longer/shorter than "MAT_(char)" 
     * OR if the string does not contain "MAT_" at the beggining of it
     * OR if the last character of the string is not a letter between A and F
     */
    if ((strlen(mat_name) != prefix_len + 1) || 
        (strncmp(mat_name, PREFIX, prefix_len)) ||
        (mat_name[prefix_len] < 'A' || mat_name[prefix_len] > 'F')
    ) { 
        printf("* ERROR: invalid mat name [%s]\n", mat_name);
        return -1;
    }

    /* converting the last character to an index */
    return mat_name[prefix_len] - 'A';
}

int valid_string_to_double(char *s) {
    int itemsread;
    int charsread;
    double d;

    /* scanning the a double into d, the number of items read into itemsread and the number of chars read into charsread */
    itemsread = sscanf(s, "%lf %n", &d, &charsread);

    /* if we didn't read exactly one item 
     * OR if the number of chars we read isn't the number of chars in the string
     * (meaning: there are extra characters in the string, for example: "hi 3.2")
     */
    if (itemsread != 1 || s[charsread] != '\0') {
        printf("ERROR, [%s] is not a valid number\n", s);
        return 0;
    }
    return 1;
}


char* strip(char* s, char *dest) {
	char *retval;
	char *p;
    if (s == NULL)
		return NULL;
    /* copying the string into dest as to not change s. This is because changing s messes up strtok() */
    strcpy(dest, s);
	
    /* init */
	p = dest;
	
    /* skip initial whitespace */
	while (*p && (*p == ' ' || *p == '\t'))
        p++;
    retval = p;
    
    /* find end of token by going back from end */
	/* reach the end */
	while (*p) p++;
	
    /* go back as long as you see white space */
    while (p > retval && (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\0')) p--;
	
    *++p = '\0';
	
    return retval;
}

int commas_valid(char* p) {
	char last_char;
	char curr_char;

	/* for NULL, *the commas* are valid */
	if (p == NULL)
		return 1;

	/* init with first char */
	last_char = *p++;

	/* for one-char string, commas are valid no matter what */
	if (last_char == '\0')
		return 1;

	/* string is 2 or more chars: check no 2 consecutive commas */
	while ((curr_char = *p++) != 0) {
		if (curr_char == ',' && last_char == ',') {
			printf("ERROR: two consecutive commas\n");
            return 0;
        }
		last_char = curr_char;
	}

	/* check that the last char is not a comma */
	if (last_char == ',') {
		printf("ERROR: extra comma at end of line\n");
        return 0;
    }

	return 1;
}

char* read_next_arg() {
    /* to store the stripped argument */
    char stripped[INPUTLENGTH];
    /* returning the argument after stripping the string between the next two commmas
     * note that the commas are valid; comma validity is checked at the beggining of main
     */
    return strip(strtok(NULL, ","), stripped);
}

int no_more_args() {
    char *extraarg;

    /* if we managed to read another argument */
    if ((extraarg = read_next_arg()) != NULL) {
		printf("ERROR: extra arg: [%s]\n", extraarg);
		return 0;
	}

	return 1;
}

int read_mat_idx() {
    char *mat_name;

    /* if another argument couldn't be read */
    if (!(mat_name = read_next_arg())) {
        printf("ERROR, too little arguments.\n");
        return -1;
    }
	/* if the argument has a length more than "MAT_(char)" */
    if (strlen(mat_name) != strlen(PREFIX) + 1) {
		printf("* ERROR: invalid mat name [%s]\n", mat_name);
		return -1;
	}
    return mat_to_idx(mat_name);
}

int handlereadmat(mat **mats) {
    int i = 0;
    double nums[MAT_LENGTH*MAT_LENGTH] = {0};
    char *token;
    int matidx;

    /* reading the matrix to read to */
    matidx = read_mat_idx();

    /* if we couldn't find any number after the matrix name */
    if (!(token = read_next_arg())) {
        printf("ERROR, too little arguments\n");
        return 0;
    }
    do {
        /* if the argument isn't a valid double */
        if (!valid_string_to_double(token)) return 0;
        
        /* only if not more than 16 arguments were read. 
         * this is because we can read 30 arguments but only take the first 16.
         */
        if (i < MAT_LENGTH * MAT_LENGTH) {
            /* convert the token into a double and store it in the nums array */
            sscanf(token, "%lf", &(nums[i++]));
        }

    } while ((token = read_next_arg()));
    readmat(mats[matidx], nums);
    return 1;
}

int handleprintmat(mat **mats) {
    /* reading the matrix */
    int matidx = read_mat_idx();
    /* if this isn't a valid matrix */
    if (matidx == -1) return 0;
    /* printing the matrix name */
    printf("%s%c : \n\t", PREFIX, ('A' + matidx));
    /* printing the matrix */
    printmat(mats[matidx]);
    return 1;
}

int handleaddmat(mat **mats) {
    int matidx1, matidx2, matidx3;
    /* reading the three martices and making sure they are valid matrix names */
    if ((matidx1 = read_mat_idx()) == -1) return 0;
	if ((matidx2 = read_mat_idx()) == -1) return 0;
	if ((matidx3 = read_mat_idx()) == -1) return 0;
    /* if there are any arguments left to read */
	if (!no_more_args()) return 0;
    addmat(mats[matidx1], mats[matidx2], mats[matidx3]);
    return 1;
}

int handlesubmat(mat **mats) {
    int matidx1, matidx2, matidx3;
    /* reading the three martices and making sure they are valid matrix names */
    if ((matidx1 = read_mat_idx()) == -1) return 0;
	if ((matidx2 = read_mat_idx()) == -1) return 0;
	if ((matidx3 = read_mat_idx()) == -1) return 0;
    /* if there are any arguments left to read */
    if (!no_more_args()) return 0;
    submat(mats[matidx1], mats[matidx2], mats[matidx3]);
    return 1;
}

int handlemulmat(mat **mats) {
    int matidx1, matidx2, matidx3;
    /* reading the three martices and making sure they are valid matrix names */
    if ((matidx1 = read_mat_idx()) == -1) return 0;
	if ((matidx2 = read_mat_idx()) == -1) return 0;
	if ((matidx3 = read_mat_idx()) == -1) return 0;
    /* if there are any arguments left to read */
    if(!no_more_args()) return 0;
    mulmat(mats[matidx1], mats[matidx2], mats[matidx3]); 
    return 1;
}

int handlemulscalar(mat **mats) {
    int matidx1, matidx2;
    double scalar;
    char *scalarstr;
    /* reading the first matrix and checking validity */
    if ((matidx1 = read_mat_idx()) == -1) return 0;

    /* reading the scalar and checking validity */
    scalarstr = read_next_arg();
	if (!valid_string_to_double(scalarstr)) return 0;

    /* reading the second matrix and checking validity */
	if ((matidx2 = read_mat_idx()) == -1) return 0;

    /* converting the scalar into a float */
    sscanf(scalarstr, "%lf", &scalar);

    mulscalar(mats[matidx1], scalar, mats[matidx2]);
    return 1;
}

int handletransmat(mat **mats) {
    int matidx1, matidx2;
    /* reading the two martices and making sure they are valid matrix names */
    if ((matidx1 = read_mat_idx()) == -1) return 0;
	if ((matidx2 = read_mat_idx()) == -1) return 0;
    /* if there are any arguments left to read */
    if(!no_more_args()) return 0;
    transmat(mats[matidx1], mats[matidx2]);
    return 1;
}

int handlestop() {
    /* if there is anything after the stop command */
    if (!no_more_args()) return 0;
    return 1;
}