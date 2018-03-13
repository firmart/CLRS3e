#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int length;
    char *string;
} string_t;


string_t *initStringN(const char *str, int n) {
    string_t *s = malloc(sizeof(string_t));
    s->string = strndup(str, n);
    s->length = n;
    return s;
}

string_t *initString(const char *str) {
    return initStringN(str, strlen(str));
}

// Section 32.1
int naiveStringMatcher(const string_t *text, const string_t *pattern) {
    int n = text->length, m = pattern->length;
    char* T = text->string, *P = pattern->string;

    for (int shift = 0; shift < n - m; shift++) {
        //printf("%s\n%*s%s\n", T, shift, "",  P);

        if (strncmp(P, T + shift, m) == 0) {
            return shift;
        }
    }

    return -1;
}

// Exercise 32.1-2
int naiveStringMatcherAcc(const string_t *text, const string_t *pattern) {
    int n = text->length, m = pattern->length, shift = 0;
    char* T = text->string, *P = pattern->string;

    while (*(T + shift)) {
        printf("%s\n%*s%s\n", T, shift, "", P);

        if (*(T + shift) != *P) {
            shift++;

        } else if (strncmp(P, T + shift, m) == 0) {
            return shift;

        } else {
            shift += m;
        }
    }

    return -1;
}

// Exercise 32.1-4
//int naiveStringMatcherWithGap(const string_t *text, const string_t *pattern, const char gap) {
//    int n = text->length, m = pattern->length, shift = 0, sgap = -1;
//    char* T = text->string, *P = pattern->string, *g;
//    string_t* pgap1 = NULL, pgap2 = NULL;
//    while(g = strchr(P + sgap + 1, gap)){
//        sgap = g - ;
//        pgap2 = initStringN(P, sgap);
//        printf("pgap=%s\n", pgap2->string);
//        shift = naiveStringMatcher(text, pgap2);
//        pgap1 = pgap2;
//        pgap2 = P + strlen(P);
//    }
//    return -1;
//}


int main(void) {
    string_t *text = initString("abccbaabcabac");
    string_t *pattern = initString("cab");
    int shift = naiveStringMatcherAcc(text, pattern);
    //naiveStringMatcherWithGap(text, pattern, '*');
    printf("pattern %s occurs with shift %d in %s\n", pattern->string, shift, text->string);
    return 0;
}
