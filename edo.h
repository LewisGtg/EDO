#ifndef __EDO__
#define __EDO__

typedef struct {
    int n;
    double a, b;
    double ya, yb;
    double (*p) (double), (*q) (double), (*r) (double);
} edo;

edo * iniciaEdo(int n, double a, double b, double ya, double yb, double (p) (double), double (q) (double), double (r) (double));

double p(double x);
double q(double x);
double r(double x);

#endif