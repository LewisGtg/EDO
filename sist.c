#include "sist.h"
#include <stdlib.h>
#include <stdio.h>

SistLinear * inciaSist(int n) {
    SistLinear * sl = (SistLinear *) malloc(sizeof(SistLinear));

    if (!sl) {
        fprintf(stderr, "Erro ao alocar sistema linear.");
        return NULL;
    }

    sl->n = n;
    sl->D = malloc(sizeof(double) * n);
    sl->Di = malloc(sizeof(double) * n-1);
    sl->Ds = malloc(sizeof(double) * n-1);
    sl->B = malloc(sizeof(double) * n);

    if (!sl->D || !sl->Di || !sl->Ds || !sl->B) {
        fprintf(stderr, "Erro ao alocar vetores.");
        return NULL;
    }

    return sl;
}

void liberaSist(SistLinear * sl) {
    free(sl->D);
    free(sl->Di);
    free(sl->Ds);
    free(sl->B);
    free(sl);

    sl = NULL;
}

void geraSist(edo * edoeq, SistLinear * sl) {
    double xi, h;

    h = (edoeq->b - edoeq-> a) / (edoeq->n+1);
    
    for (int i=0; i < edoeq->n; ++i) {
        xi = edoeq->a + (i+1)*h; 
        sl->Di[i] = 1 - h * edoeq->p(xi)/2.0;
        sl->D[i] = -2 + h*h * edoeq->q(xi); 
        sl->Ds[i] = 1 + h * edoeq->p(xi)/2.0; 
        sl->B[i] = h*h * edoeq->r(xi); 
    }

    sl->B[0] -= edoeq->ya * (1 - h*edoeq->p(edoeq->a+h)/2.0);
    sl->B[edoeq->n-1] -= edoeq->yb * (1 + h*edoeq->p(edoeq->b-h)/2.0);
}

void imprimeSist(SistLinear * sl) {
    printf("Diagonal principal:\n");
    for (int i = 0; i < sl->n; ++i) {
        printf("%f ", sl->D[i]);
    }
    printf("\n\n");

    printf("Diagonal superior:\n");
    for (int i = 0; i < sl->n-1; ++i) {
        printf("%f ", sl->Ds[i]);
    }
    printf("\n\n");

    printf("Diagonal inferior:\n");
    for (int i = 0; i < sl->n-1; ++i) {
        printf("%f ", sl->Di[i]);
    }
    printf("\n\n");
    
    printf("Termos independentes:\n");
    for (int i = 0; i < sl->n; ++i) {
        printf("%f ", sl->B[i]);
    }
    printf("\n\n");
}
