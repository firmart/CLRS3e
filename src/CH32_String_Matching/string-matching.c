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
    char *T = text->string, *P = pattern->string;

    for (int shift = 0; shift < n - m; shift++) {
        printf("%s\n%*s%s\n", T, shift, "",  P);

        if (strncmp(P, T + shift, m) == 0) {
            return shift;
        }
    }

    return -1;
}

// Exercise 32.1-2
int naiveStringMatcherAcc(const string_t *text, const string_t *pattern) {
    int n = text->length, m = pattern->length, shift = 0;
    char *T = text->string, *P = pattern->string;

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
int naiveStringMatcherWithGap(const string_t *text, const string_t *pattern, const char gap) {
    int n = text->length, m = pattern->length, firstShift = 0, shift = 0, len = 0, firstflag = 1;
    char *T = text->string, *P = pattern->string, *g1 = P, *g2 = P;
    string_t *subp;

    while (1) {
        g2 = strchr(g1, gap);

        if (!g2) {
            g2 = P + m;
        }

        if (g1 - 1 == g2) {
            break;
        }

        subp = initStringN(g1, g2 - g1);
        shift = naiveStringMatcher(initString(T + shift + len), subp) + shift + len;

        if (shift == -1) {
            return -1;
        }

        if (firstflag) {
            firstShift = shift;
            firstflag = 0;
        }

        len = g2 - g1;
        g1 = g2 + 1;
    }

    return firstShift;
}

static int powmod (int x, int power, int n) {
    int c = (x % n) * x;

    for (int i = 0; i < power - 1; i++) {
        c = (c % n) * x;
    }

    c /= x;
    return c;
}

// precondition : dq < MAX_INT to avoid overflow
int RabinKarpMatcher(const string_t *text, const string_t *pattern, int d, int q) {
    int n = text->length, m = pattern->length, h = powmod(d, m - 1, q), p = 0, t = 0;
    char *T = text->string, *P = pattern->string;

    // Preprocessing, compute p and t_0 with Horner, in fact this is hashing
    // O(m)
    for (int i = 0; i < m; i++) {
        p = (d * p + P[i]) % q;
        t = (d * t + T[i]) % q;
    }

    // Matching, O((n-m+1)*m)
    for (int shift = 0; shift <= n - m; shift++) {
        if (p == t) {
            if (strncmp(P, T + shift, m) == 0) {
                return shift;
            }
        }

        // compute t_(shift+1)
        if (shift < n - m) {
            t = (d * (t - T[shift] * h) + T[shift + m]) % q;
        }
    }

    return -1;
}

int main(void) {
    string_t *text = initString("abccbaabcabac");
    string_t *pattern = initString("bac");
    //string_t *text = initString("cskjabadfhabccbacbacab");
    //string_t *pattern = initString("ab*ba*c");
    int shift = RabinKarpMatcher(text, pattern, 26, 13);
    //int shift = naiveStringMatcherWithGap(text, pattern, '*');
    printf("pattern %s occurs with shift %d in %s\n", pattern->string, shift, text->string);
    return 0;
}
