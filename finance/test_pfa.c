#include "pfa.h"
#include <stdio.h>

int main()
{
  InsuredClient c = {.m = 2.0, .s = 0.5};
    double p[3] = {0.333, 0.333, 0.333};
    c.p = p;
    init_integration("gauss2", 0.01);
    double arr[] = {1, 100};
    int n = 2;
    printf("Test de la densite de probabilite du remboursement d un seul sinistre:\n");
    for(int i=0;i<n;i++) printf("pour x=%lf PDF_X=%g\n", arr[i], clientPDF_X(&c, arr[i]));
    printf("\nTest de la fonction de repartition du remboursement d un seul sinistre:\n");
    for(int i=0;i<n;i++) printf("pour x=%lf  CDF_X=%g\n", arr[i], clientCDF_X(&c, arr[i]));
    printf("\nTest de la densite de probabilite du remboursement de la somme de deux sinistres:\n");
    for(int i=0;i<n;i++) printf("pour x=%lf  PDF_X1X2=%g\n", arr[i], clientPDF_X1X2(&c, arr[i]));
    printf("\nTest de la fonction de repartition du remboursement de la somme de deux sinistres:\n");
    for(int i=0;i<n;i++) printf("pour x=%lf  CDF_X1X2=%g\n", arr[i], clientCDF_X1X2(&c, arr[i]));
    printf("\nTest de la fonction de repartition du total annuel des remboursements:\n");
    for(int i=0;i<n;i++) printf("pour x=%lf  CDF_S=%g\n", arr[i], clientCDF_S(&c, arr[i]));
}