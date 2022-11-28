#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "sist.h"
#include "edo.h"
#include "utils.h"

void gaussSeidel(edo * edoeq, double * y, double * t) {
    int n = edoeq->n;
    double h, xi, bi, yi, d, di ,ds;

    h =  (edoeq->b - edoeq->a) / (n+1);

    for (int i = 0; i < 50; ++i) {
        for (int k = 0; k < 50; k++) {
            xi = edoeq->a + (i+1) * h;
            bi = h*h * edoeq->r(xi);
            di = 1 - h * edoeq->p(xi) / 2;
            d = -2 + h*h * edoeq->q(xi);
            ds = 1 + h * edoeq->p(xi) / 2;

            if (i == 0)
                bi -= ds*y[i+1] + edoeq->ya * (1 - h * edoeq->p(edoeq->a+h) / 2);
            else if ( i == n-1)
                bi -= di*y[i-1] - edoeq->yb * (1 + h * edoeq->p(edoeq->b-h) / 2);
            else
                bi -= ds*y[i+1] + di * y[i-1];

            y[i] = bi / d;
        }
    }
    *t = timestamp() - *t;
}

void gaussSeidelVec(SistLinear * sl, edo * edoeq, double * y, double * t) {
    int n = sl->n;

    for (int i = 0; i < 50; ++i) {
       y[0] = (sl->B[0] - sl->Ds[0] * y[1]) / sl->D[0];

       for (int j = 1; j < n - 1; ++j) {
            y[j] = (sl->B[j] - sl->Di[j-1] * y[j-1] - sl->Ds[j] * y[j+1]) / sl->D[j];
       } 

       y[n - 1] = (sl->B[n-1] - sl->Di[n-2] * y[n-2]) / sl->D[n-1];
    }

    *t = timestamp() - *t;
}

int main() {
    int sizes[] = {5, 10, 100};
    double * y0 = malloc(sizeof(double) * 100);
    double * y1 = calloc(100, sizeof(double));

    for (int i = 0; i < 3; ++i) {
        printf("-------------------------------------------------------------\n");
        printf("N = %d\n", sizes[i]);

        SistLinear * sl = inciaSist(sizes[i]);
        edo * edoeq = iniciaEdo(sizes[i], 0, 1, -1, 0, p, q, r); 
        geraSist(edoeq, sl);
        imprimeSist(sl);

        double t0 = timestamp();
        gaussSeidel(edoeq, y0, &t0);

        double t1 = timestamp();
        gaussSeidelVec(sl, edoeq, y1, &t1);

        printf("Tempo Gauss Seidel: %.5f\n", t0);
        printf("Y0: \n");
        for (int k = 0; k < sizes[i]; ++k)
            printf("%.4e ", y0[k] * 1.0e10);
        printf("\n\n");

        printf("Tempo Guass Seidel com vetor: %.5f\n", t1);
        printf("Y1: \n");
        for (int k = 0; k < sizes[i]; ++k)
            printf("%.4e ", y1[k] * 1.0e10);
        printf("\n\n");

        liberaSist(sl);
        free(edoeq);
    }

}