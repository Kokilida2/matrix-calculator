#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "handlemymat.h"
#include "mat.h"

/*returns 0 for MAT_A, 1 for MAT_B, ..., 5 for MAT_F
 * returns -1 if unrecognized matrix name
 */
int mattoidx(char *mat_name) {
    char* prefix = "MAT_";
    int prefix_len = strlen(prefix);
    if (strlen(mat_name) != prefix_len + 1) {
        printf("* ERROR: invalid mat name [%s]\n", mat_name);
        return -1;
    }
    if (strncmp(mat_name, prefix, prefix_len)) {
        printf("* ERROR: invalid mat name [%s]\n", mat_name);
        return -1;
    }
    if (mat_name[prefix_len] < 'A' || mat_name[prefix_len] > 'F') {
        printf("* ERROR: invalid mat name [%s]\n", mat_name);
        return -1;
    }
    return mat_name[prefix_len] - 'A';
}

/* returns 1 if the string is a double, 0 if not */
int valid_string_to_double(char *s) {
    int itemsread;
    int charsread;
    double d;

    itemsread = sscanf(s, "%lf %n", &d, &charsread);
    if (itemsread != 1 || s[charsread] != '\0') {
        printf("ERROR, [%s] is not a number", s);
        return 0;
    }
    return 1;
}


char* strip(char* s) {
	char *retval;
	char *p;
    char* cpy;
    if (s == NULL)
		return NULL;
    cpy = (char*)malloc(sizeof(char) * (strlen(s) + 1));
    strcpy(cpy, s);
	/* init */
	p = cpy;

	/* skip initial whitespace */
	while (*p && (*p == ' ' || *p == '\t'))
        p++;
    retval = p;

	/* find end of token by going back from end */
	/* reach the end */
	while (*p++);

	while (p > retval && (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\0')) {
		p--;
    }
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
    return strip(strtok(NULL, ","));
}

int no_more_args() {
    char *extraarg;
    if ((extraarg = read_next_arg()) != NULL) {
		printf("ERROR: extra arg: [%s]", extraarg);
		return 0;
	}
	return 1;
}

int read_mat_idx() {
    char *mat_name = read_next_arg();
	if (strlen(mat_name) != strlen("MAT_") + 1) {
		printf("* ERROR: invalid mat name [%s]\n", mat_name);
		return -1;
	}
    return mattoidx(mat_name);
}

int handlereadmat(mat **mats) {
    int i = 0;
    double nums[MAT_LENGTH*MAT_LENGTH] = {0};
    char *token;
    int matidx;

    matidx = read_mat_idx();
    while ((token = read_next_arg()) != NULL) {
        if (!valid_string_to_double(token)) {
            printf("ERROR, expected a number but got %s\n", token);
            return 0;
        }
        if (i < MAT_LENGTH * MAT_LENGTH) {
            sscanf(token, "%lf", &(nums[i++]));
        }
    }
    readmat(mats[matidx], nums);
    return 1;
}

int handleprintmat(mat **mats) {
    int matidx = read_mat_idx();
    if (matidx == -1) return 0;
    printf("MAT_%c : \n\t", ('A' + matidx));
    printmat(mats[matidx]);
    return 1;
}

int handleaddmat(mat **mats) {
    int matidx1, matidx2, matidx3;
    if ((matidx1 = read_mat_idx()) == -1) return 0;
	if ((matidx2 = read_mat_idx()) == -1) return 0;
	if ((matidx3 = read_mat_idx()) == -1) return 0;
	if (!no_more_args()) return 0;
    addmat(mats[matidx1], mats[matidx2], mats[matidx3]);
    return 1;
}

int handlesubmat(mat **mats) {
    /* getting the 3 mats */
    int matidx1, matidx2, matidx3;
    if ((matidx1 = read_mat_idx()) == -1) return 0;
	if ((matidx2 = read_mat_idx()) == -1) return 0;
	if ((matidx3 = read_mat_idx()) == -1) return 0;
    if (!no_more_args()) return 0;
    submat(mats[matidx1], mats[matidx2], mats[matidx3]);
    return 1;
}

int handlemulmat(mat **mats) {
    /* getting the 3 mats */
    int matidx1, matidx2, matidx3;
    if ((matidx1 = read_mat_idx()) == -1) return 0;
	if ((matidx2 = read_mat_idx()) == -1) return 0;
	if ((matidx3 = read_mat_idx()) == -1) return 0;
    if(!no_more_args()) return 0;
    mulmat(mats[matidx1], mats[matidx2], mats[matidx3]); 
    return 1;
}

int handlemulscalar(mat **mats) {
    int matidx1, matidx2;
    double scalar;
    char *scalarstr;
    if ((matidx1 = read_mat_idx()) == -1) return 0;

    scalarstr = read_next_arg();
	if (!valid_string_to_double(scalarstr)) return 0;

	if ((matidx2 = read_mat_idx()) == -1) return 0;

    sscanf(scalarstr, "%lf", &scalar);
    mulscalar(mats[matidx1], scalar, mats[matidx2]);
    return 1;
}

int handletransmat(mat **mats) {
    int matidx1, matidx2;
    if ((matidx1 = read_mat_idx()) == -1) return 0;
	if ((matidx2 = read_mat_idx()) == -1) return 0;
    if(!no_more_args()) return 0;

    transmat(mats[matidx1], mats[matidx2]);
    return 1;
}