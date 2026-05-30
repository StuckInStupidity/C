#include "integration.h"
#include <math.h>

double f(double t) {return exp(t*1/4);}

double g(double a, double b){
    return (a-b >= 0) ? a-b : b-a;
}

int main()
{
    QuadFormula qf, qf2, qf3, qf4, qf5, qf6, qf7;
    double I1, I3, I5, I7, I9, I11, I13; double I = 544.92266;
    setQuadFormula(&qf, "right");
    setQuadFormula(&qf2, "left");
    setQuadFormula(&qf3, "middle");
    setQuadFormula(&qf4, "trapezes");
    setQuadFormula(&qf5, "simpson");
    setQuadFormula(&qf6, "gauss2");
    setQuadFormula(&qf7, "gauss3");
    I1 = integrate(f, 10, 20, 10, &qf);
    I3 = integrate(f, 10, 20, 10, &qf2);
    I5 = integrate(f, 10, 20, 10, &qf3);
    I7 = integrate(f, 10, 20, 10, &qf4);
    I9 = integrate(f, 10, 20, 10, &qf5);
    I11 = integrate(f, 10, 20, 10, &qf6);
    I13 = integrate(f, 10, 20, 10, &qf7);
    printf("\n\nRectangle droit valeur calculee : quand N = 10 subdivisions : %lf\n", I1);
    printf("Rectangle droit marge d'erreur : %lf\n", g(I,I1));
    printf("\nRectangle gauche : quand N = 10 subdivisions : %lf\n", I3);
    printf("Rectangle gauche marge d'erreur : %lf\n", g(I,I3));
    printf("\nRectangle milieu valeur calculee : quand N = 10 subdivisions : %lf\n", I5);
    printf("Rectangle milieu marge d'erreur : %lf\n", g(I,I5));
    printf("\nRectangle trapezes valeur calculee : quand N = 10 subdivisions : %lf\n", I7);
    printf("Rectangle trapezes marge d'erreur : %lf\n", g(I,I7));
    printf("\nSimpson valeur calculee : quand N = 10 subdivisions : %lf\n", I9);
    printf("Simpson marge d'erreur : %lf\n", g(I,I9));
    printf("\nGauss 2 noeuds valeur calculee : quand N = 10 subdivisions : %lf\n", I11);
    printf("Gauss 2 noeuds marge d'erreur : %lf\n", g(I,I11));
    printf("\nGauss 3 noeuds valeur calculee : quand N = 10 subdivisions : %lf\n", I13);
    printf("Gauss 3 noeuds marge d'erreur : %lf\n\n", g(I,I13));
}