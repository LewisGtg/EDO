#include "edo.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define e 2.718281828459045235360287

// Inicializa Edo
edo * iniciaEdo(int n, double a, double b, double ya, double yb, double (p) (double), double (q) (double), double (r) (double)) {
    edo * edoeq = (edo *) malloc(sizeof(edo));

    if (!edoeq) {
        fprintf(stderr, "Erro ao alocar edo.");
        return NULL;
    }

    edoeq->n = n;
    edoeq->a = a;
    edoeq->b = b;
    edoeq->ya = ya;
    edoeq->yb = yb;
    edoeq->p = p;
    edoeq->q = q;
    edoeq->r = r;

    return edoeq;
}

// Funções auxiliares 
double p(double x) {
    return (x+1);
}

double q(double x) {
    return 2;
}

double r(double x) {
    return ((1-x*x)*pow(e, -x));
}
