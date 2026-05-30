#define INTEGRATION_C

#include "integration.h"
#include <math.h>
bool setQuadFormula(QuadFormula* qf, char* name){
    if(strcmp(name, "left")==0){
    strcpy(qf->name, name);
    return true;
    }
    else if(strcmp(name, "right")==0){
    strcpy(qf->name, name);
    return true;
    }
    else if(strcmp(name, "middle")==0){
    strcpy(qf->name, name);
    return true;
    }
    else if(strcmp(name, "trapezes")==0){
    strcpy(qf->name, name);
    return true;
    }
    else if(strcmp(name, "simpson")==0){
    strcpy(qf->name, name);
    return true;
    }
    else if(strcmp(name, "gauss2")==0){
    strcpy(qf->name, name);
    return true;
    }
    else if(strcmp(name, "gauss3")==0){
    strcpy(qf->name, name);
    return true;
    }
    else return false;
}

/* This function is not required ,but it may useful to debug */
void printQuadFormula(QuadFormula* qf)
{
  printf("Quadratic formula: %s\n", qf->name);
  /* Print everything else that may be useful */
}


/* Approximate the integral of function f from a to b.
   - f is a pointer to a function pointer
   - a and b are the integration bounds
   - Interval [a,b] is split in N subdivisions [ai,bi]
   - Integral of f on each subdivision [ai,bi] is approximated by the quadrature formula qf.
*/
double integrate(double (*f)(double), double a, double b, int N, QuadFormula* qf)
{
    if(f == NULL || qf == NULL) return 0.0;
    double h = fabs(b-a)/N;
    double app = 0.0;
    if(strcmp(qf->name, "left")==0){
    for(int i = 0; i < N; i++){
    app+=(f(a+i*h)*h);
    }
    }
    else if(strcmp(qf->name, "right")==0){
    for(int i = 0; i < N; i++){
    app+=(f(a+(i+1)*h)*h);
    }
    }
    else if(strcmp(qf->name, "middle")==0){
    for(int i = 0; i < N; i++){
    app+=(f((a+(i+1)*h+a+i*h)/2.0)*h);
    }
    }
    else if(strcmp(qf->name, "trapezes") == 0){
    for(int i=0; i < N; i++){
    double s = 0.0;
    for(int k = 0; k<=1;k++){
    s+=(f(a+i*h+k*h)/2.0);
    }
    app+=s*h;
    }
    }
    else if(strcmp(qf->name, "simpson") == 0){
    for(int i=0; i < N; i++){
    app+=(h*(1.0/6.0*f(a+i*h)+2.0/3.0*f((a+i*h+a+(i+1)*h)/2.0)+1.0/6.0*f(a+(i+1)*h)));
    }}
    else if(strcmp(qf->name, "gauss2") == 0){
    for(int i=0; i < N; i++){
    app+=(f(a+i*h+h*((1.0-1.0/sqrt(3.0))/2.0))+f(a+i*h+h*((1.0+1.0/sqrt(3.0))/2.0)))/2.0*h;
    }}
    else if(strcmp(qf->name, "gauss3") == 0){
    for(int i=0; i < N; i++){
    app+=(5.0/18.0*f(a+i*h+1.0/2.0*(1.0-sqrt(3.0/5.0))*h)+4.0/9.0*f(a+i*h+1.0/2.0*h)+5/18.0*f(a+i*h+1.0/2.0*(1.0+sqrt(3.0/5.0))*h))*h;
    }}
    return app;
}


double integrate_dx(double (*f)(double), double a, double b, double dx, QuadFormula* qf)
{
    if(f == NULL || qf == NULL) return 0.0;
    int N = (int)round(fabs(b-a)/dx);
    if(N==0) N=1;
    double app = 0.0;
    if(strcmp(qf->name, "left")==0){
    for(int i = 0; i < N; i++){
    app+=(f(a+i*dx)*dx);
    }
    }
    else if(strcmp(qf->name, "right")==0){
    for(int i = 0; i < N; i++){
    app+=(f(a+(i+1)*dx)*dx);
    }
    }
    else if(strcmp(qf->name, "middle")==0){
    for(int i = 0; i < N; i++){
    app+=(f((a+(i+1)*dx+a+i*dx)/2.0)*dx);
    }
    }
    else if(strcmp(qf->name, "trapezes") == 0){
    for(int i=0; i < N; i++){
    double s = 0.0;
    for(int k = 0; k<=1;k++){
    s+=(f(a+i*dx+k*dx)/2.0);
    }
    app+=s*dx;
    }
    }
    else if(strcmp(qf->name, "simpson") == 0){
    for(int i=0; i < N; i++){
    app += dx*(1.0/6.0*f(a+i*dx)+2.0/3.0*f((a+i*dx+a+(i+1)*dx)/2)+1.0/6.0*f(a+(i+1)*dx));
    }}
    else if(strcmp(qf->name, "gauss2") == 0){
    for(int i=0; i < N; i++){
    app+=(f(a+i*dx+dx*((1.0-1.0/sqrt(3.0))/2.0))+f(a+i*dx+dx*((1.0+1.0/sqrt(3.0))/2.0)))/2.0*dx;
    }}
    else if(strcmp(qf->name, "gauss3") == 0){
    for(int i=0; i < N; i++){
    app+=(5.0/18.0*f(a+i*dx+1.0/2.0*(1.0-sqrt(3.0/5.0))*dx)+4.0/9.0*f(a+i*dx+1.0/2.0*dx)+5/18.0*f(a+i*dx+1.0/2.0*(1.0+sqrt(3.0/5.0))*dx))*dx;
    }}
    return app;
}