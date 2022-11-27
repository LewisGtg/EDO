#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "sist.h"
#include "edo.h"

#define e 2.718281828459045235360287

void gaussSeidel(edo * edoeq, double * y) {
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
}

int main() {
    int sizes[] = {5, 10, 100};
    double * y = malloc(sizeof(double) * 100);


    for (int i = 0; i < 3; ++i) {
        printf("N = %d\n", sizes[i]);

        SistLinear * sl = inciaSist(sizes[i]);
        edo * edoeq = iniciaEdo(sizes[i], 0, 1, -1, 0, p, q, r); 
        geraSist(edoeq, sl);
        imprimeSist(sl);

        gaussSeidel(edoeq, y);

        for (int k = 0; k < sizes[i]; ++k)
            printf("%.4e ", y[k] * 1.0e10);
        printf("\n");

        liberaSist(sl);
        free(edoeq);
    }

}