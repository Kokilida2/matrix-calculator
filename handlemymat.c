#include <stdio.h>
#include <string.h>
#include "handlemymat.h"
#include "mat.h"

/*returns 0 for MAT_A, 1 for MAT_B, ..., 5 for MAT_F
 * returns -1 if unrecognized matrix name
 */
int mattoidx(char *mat_name) {
    char* prefix = "MAT_";
    int prefix_len = strlen(prefix);
    if (strlen(mat_name) != prefix_len + 1) return -1;
    if (strncmp(mat_name, prefix, prefix_len)) return -1;
    if (mat_name[prefix_len] < 'A' || mat_name[prefix_len] > 'F') return -1;
    return mat_name[prefix_len] - 'A';
}

/* returns 1 if the string is a double, 0 if not */
int valid_string_to_double(char *s) {
    int itemsread;
    int charsread;
    double d;

    itemsread = sscanf(s, "%lf %n", &d, &charsread);
    if (itemsread != 1 || s[charsread] != '\0') {
        return 0;
    }
    return 1;
}


char* strip(char* s) {
	char *retval;
	char *p;

	if (s == NULL)
		return NULL;

	/* init */
	p = s;

	/* skip initial whitespace */
	while (*p && (*p == ' ' || *p == '\t'))
        p++;
    retval = p;

	/* find end of token by going back from end */
	/* reach the end */
	while (*p++);

	/* go back as long as we're seeing a whitespace */
	while (p > retval && (*p == ' ' || *p == '\t'))
		p--;
    printf("p = [%c]\n", *p);
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
		if (curr_char == ',' && last_char == ',')
			return 0;
		last_char = curr_char;
	}

	/* check that the last char is not a comma */
	if (last_char == ',')
		return 0;

	return 1;
}

char* read_next_arg() {
    char *s = strtok(NULL, ",");
    printf("In read_next_arg, s = (%s)\n", s);
	char *s2 = strip(s);
    printf("strip(s) = [%s]\n", s2);
    return s2;
}

int no_more_args() {
    if (read_next_arg()) {
		printf("ERROR: extra arg");
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
    char *toreadto;
    int matidx;

    toreadto = strtok(NULL, " \t");
    if ((matidx = mattoidx(toreadto)) == -1) {
        printf("ERROR: %s is not a valid matrix name\n", toreadto);
        return 0;
    }
    printf("strtok(NULL,) = %s", strtok(NULL, " \t"));
    while ((token = strtok(NULL, " \t")) != NULL && i < MAT_LENGTH * MAT_LENGTH) {
        if (!valid_string_to_double(token)) {
            printf("ERROR, expected a number but got %s\n", token);
            return 0;
        }
        sscanf(token, "%lf", &(nums[i++]));
        strtok(NULL, " \t");
    }
    /* printf("** HANDLE_READ_MAT: mats[matidx]=%p\n", (void*)mats[matidx]); */
    readmat(mats[matidx], nums);
    /* printmat(mats[matidx]); */
    return 1;
}

int handleprintmat(mat **mats) {
    char *toreadto;
    int matidx;

    toreadto = strtok(NULL, " ");
    if ((matidx = mattoidx(toreadto) == -1)) {
        printf("ERROR: %s is not a valid matrix name\n", toreadto);
        return 0;
    }
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
    char *toreadto1;
    int matidx1;
    char *toreadto2;
    int matidx2;
    char *toreadto3;
    int matidx3;

    toreadto1 = strtok(NULL, ",");
    if ((matidx1 = mattoidx(toreadto1) == -1)) {
        printf("ERROR: %s is not a valid matrix name\n", toreadto1);
        return 0;
    }
    
    toreadto2 = strtok(NULL, ",");
    if ((matidx2 = mattoidx(toreadto2) == -1)) {
        printf("ERROR: %s is not a valid matrix name\n", toreadto2);
        return 0;
    }

    
    toreadto3 = strtok(NULL, " ");
    if ((matidx3 = mattoidx(toreadto3) == -1)) {
        printf("ERROR: %s is not a valid matrix name\n", toreadto3);
        return 0;
    }

    submat(mats[matidx1], mats[matidx2], mats[matidx3]);
    return 1;
}

int handlemulmat(mat **mats) {
    /* getting the 3 mats */
    char *toreadto1;
    int matidx1;
    char *toreadto2;
    int matidx2;
    char *toreadto3;
    int matidx3;

    toreadto1 = strtok(NULL, ",");
    if ((matidx1 = mattoidx(toreadto1) == -1)) {
        printf("ERROR: %s is not a valid matrix name\n", toreadto1);
        return 0;
    }
    
    toreadto2 = strtok(NULL, ",");
    if ((matidx2 = mattoidx(toreadto2) == -1)) {
        printf("ERROR: %s is not a valid matrix name\n", toreadto2);
        return 0;
    }

    toreadto3 = strtok(NULL, " ");
    if ((matidx3 = mattoidx(toreadto3) == -1)) {
        printf("ERROR: %s is not a valid matrix name\n", toreadto3);
        return 0;
    }

    mulmat(mats[matidx1], mats[matidx2], mats[matidx3]); 
    return 1;  
}

int handlemulscalar(mat **mats) {
    char *toreadto1;
    int matidx1;
    char *scalarptr;
    double scalar;
    char *toreadto2;
    int matidx2;

    toreadto1 = strtok(NULL, ",");
    if ((matidx1 = mattoidx(toreadto1) == -1)) {
        printf("ERROR: %s is not a valid matrix name\n", toreadto1);
        return 0;
    }
    scalarptr = strtok(NULL, ",");
    if (!valid_string_to_double(scalarptr)) {
        printf("ERROR: %s is not a valid double scalar", scalarptr);
        return 0;
    }

    sscanf(scalarptr, "%lf", &scalar);
    toreadto2 = strtok(NULL, ",");
    if ((matidx2 = mattoidx(toreadto2) == -1)) {
        printf("ERROR: %s is not a valid matrix name\n", toreadto2);
        return 0;
    }

    mulscalar(mats[matidx1], scalar, mats[matidx2]);
    return 1;
}

int handletransmat(mat **mats) {
    char *toreadto1;
    int matidx1;
    char *toreadto2;
    int matidx2;
    toreadto1 = strtok(NULL, ",");
    if ((matidx1 = mattoidx(toreadto1) == -1)) {
        printf("ERROR: %s is not a valid matrix name\n", toreadto1);
        return 0;
    }

    toreadto2 = strtok(NULL, ",");
    if ((matidx2 = mattoidx(toreadto2) == -1)) {
        printf("ERROR: %s is not a valid matrix name\n", toreadto2);
        return 0;
    }

    transmat(mats[matidx1], mats[matidx2]);
    return 1;
}