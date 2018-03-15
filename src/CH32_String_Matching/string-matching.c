#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

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
void naiveStringMatcherAcc(const string_t *text, const string_t *pattern) {
    int n = text->length, m = pattern->length, shift = 0;
    char *T = text->string, *P = pattern->string;

    while (shift <= n - m) {
        //printf("%s\n%*s%s\n", T, shift, "", P);
        if (strncmp(P, T + shift, m) == 0) {
            printf("pattern %s occurs with shift %d in %s\n", P, shift, T);
            shift += m;

        } else {
            shift ++;
        }

    }
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

int gapPartition(const string_t *pattern, const char gap, string_t ***patternsArray) {
    char *P = pattern->string, *q = P, *begin = NULL;
    int patternsNumber = 0, allocateSize = pattern->length / 10 + 1;
    *patternsArray = malloc(allocateSize * sizeof(string_t *));

    while (*q) {
        while (*q == gap) {
            q++;
        }

        begin = q;

        while (*q != gap && *q != '\0') {
            q++;
        }

        if (patternsNumber > allocateSize) {
            allocateSize += 5;
            *patternsArray = realloc(*patternsArray, allocateSize * sizeof(string_t *));
        }

        (*patternsArray)[patternsNumber++] = initStringN(begin, q - begin);
    }

    return patternsNumber;
}

int naiveStringMatcherWithGap2(const string_t *text, const string_t *pattern, const char gap) {
    int n = text->length, m_i = 0, s = 0, patternsNumber;
    char *T = text->string, *P_i;
    string_t **patternsPartition;
    patternsNumber = gapPartition(pattern, gap, &patternsPartition);
    int *shift = calloc(patternsNumber, sizeof(int));

    for (int i = 0; i < patternsNumber; i++) {
        m_i = patternsPartition[i]->length;
        P_i = patternsPartition[i]->string;
        printf("P_%d = %s, m_%d=%d\n", i, P_i, i, m_i);

        while (s++ < n - m_i) {
            if (strncmp(P_i, T + s, m_i) == 0) {
                printf("%s\n%*c%s\n", T,  s, ' ', P_i);
                shift[i] = s;
                s += m_i - 1;
                break;
            }
        }
    }

    return s <= shift[patternsNumber - 1] ? shift[0] : -1;
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

// Exercise 32.2-2 : k patterns which have equal length
void RabinKarpMatcherEqualLength(const string_t *text, const string_t **pattern, int k, int d, int q) {
    int n = text->length, m = pattern[0]->length, h = powmod(d, m - 1, q), *p, t = 0;
    char *T = text->string, **P;
    P = malloc (k * sizeof(char *));
    p = malloc (k * sizeof(int));

    for (int i = 0; i < k; i++) {
        P[i] = pattern[i]->string;
    }

    // Preprocessing, compute p and t_0 with Horner, in fact this is hashing
    // O(m)
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < k; j++) {
            p[j] = (d * p[j] + P[j][i]) % q;
        }

        t = (d * t + T[i]) % q;
    }

    // Matching, O((n-m+1)*m)
    for (int shift = 0; shift <= n - m; shift++) {
        for (int j = 0; j < k; j++) {
            if (p[j] == t) {
                if (strncmp(P[j], T + shift, m) == 0) {
                    printf("pattern %s occurs with shift %d in %s\n", P[j], shift, T);
                }
            }
        }

        // compute t_(shift+1)
        if (shift < n - m) {
            t = (d * (t - T[shift] * h) + T[shift + m]) % q;
        }
    }

}

// Exercise 32.2-2 : k patterns which have different length
void RabinKarpMatcherDiffLength(const string_t *text, const string_t **pattern, int k, int d, int q) {
    int n = text->length, *h, *p, *t, *m, max = 0, min = INT_MAX;
    char *T = text->string, **P;
    P = malloc (k * sizeof(char *));
    p = calloc (k , sizeof(int));
    m = malloc (k * sizeof(int));
    t = calloc (k , sizeof(int));
    h = malloc (k * sizeof(int));

    for (int i = 0; i < k; i++) {
        m[i] = pattern[i]->length;
        P[i] = pattern[i]->string;
        max = max > m[i] ? max : m[i];
        min = min < m[i] ? min : m[i];
        h[i] = powmod(d, m[i] - 1, q);
    }

    // Preprocessing
    for (int i = 0; i < max; i++) {
        for (int j = 0; j < k; j++) {
            if (m[j] > i) {
                p[j] = (d * p[j] + P[j][i]) % q;
                t[j] = (d * t[j] + T[i]) % q;
            }
        }
    }

    for (int shift = 0; shift <= n - min; shift++) {
        for (int j = 0; j < k; j++) {
            //printf("%s\n%*s%s\np=%d, t=%d\n", T, shift, "", P[j], p[j], t[j]);
            if (p[j] == t[j]) {
                if (strncmp(P[j], T + shift, m[j]) == 0) {
                    printf("pattern %s occurs with shift %d in %s\n", P[j], shift, T);
                }
            }
        }

        // compute t_(shift+1)
        if (shift < n - min) {
            for (int i = 0; i < k; i++) {
                t[i] = (d * (t[i] - T[shift] * h[i]) + T[shift + m[i]]) % q;
            }
        }
    }
}

int main(void) {
    //string_t *text = initString("abccbacbcabac");
    //string_t *pattern = initString("bac");
    //string_t *pattern = initString("ab**ba*c*c*b");
    //int shift = RabinKarpMatcher(text, pattern, 26, 13);
    //naiveStringMatcherAcc(text, pattern);
    //int shift = naiveStringMatcherWithGap2(text, pattern, '*');
    //printf("pattern %s occurs with shift %d in %s\n", pattern->string, shift, text->string);

    string_t *text = initString("cabcbacbbacbacbabbacbcababcbcababccbacbacab");
    const string_t **pattern = malloc(10 * sizeof(string_t *));
    pattern[0] = initString("abcb");
    pattern[1] = initString("ba");
    pattern[2] = initString("badf");
    pattern[3] = initString("bb");
    pattern[4] = initString("ca");
    pattern[5] = initString("cb");
    pattern[6] = initString("ab");
    pattern[7] = initString("bcab");
    pattern[8] = initString("bbac");
    pattern[9] = initString("bca");
    RabinKarpMatcherDiffLength(text, pattern, 10, 26, 13);


    return 0;
}
