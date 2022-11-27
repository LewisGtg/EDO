#include "edo.h"

#ifndef __SIS__
#define __SIS__

typedef struct {
    double * D;
    double * Di; 
    double * Ds;
    double * B;
    int n;
} SistLinear;

SistLinear * inciaSist(int n);

void liberaSist(SistLinear * sl);

void geraSist(edo * edoeq, SistLinear * sl);

void imprimeSist(SistLinear * sl);

#endif