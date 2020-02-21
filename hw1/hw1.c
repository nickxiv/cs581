#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(int argc, char *argv[]) {
    if (argc != 2) return -1;

    
    
    const int n = atoi(argv[1]);
    struct timespec requestStart, requestEnd;

    srand(time(0));

    double *a;
    double *b;
    double *dgemm0;
    double *dgemm1;
    double *dgemm2;
    double *dgemm3;


    a = (double *)calloc(sizeof(double), n*n);
    b = (double *)calloc(sizeof(double), n*n);
    dgemm0 = (double *)calloc(sizeof(double), n*n);
    dgemm1 = (double *)calloc(sizeof(double), n*n);
    dgemm2 = (double *)calloc(sizeof(double), n*n);
    dgemm3 = (double *)calloc(sizeof(double), n*n);


    for (int i=0; i<n*n; i++) {
        a[i] = (double)(rand() % 13);
        b[i] = (double)(rand() % 13);
    }

    printf("\n\nTesting with n = %d\n", n);

    clock_gettime(CLOCK_MONOTONIC, &requestStart);

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            for (int k=0; k<n; k++) {
                dgemm0[i*n+j] += a[i*n+k] * b[k*n+j];
            }
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &requestEnd);
    double dgemm0Time; 
    dgemm0Time = (requestEnd.tv_sec - requestStart.tv_sec) * 1e9; 
    dgemm0Time = (dgemm0Time + (requestEnd.tv_nsec - requestStart.tv_nsec)) * 1e-6; 

    clock_gettime(CLOCK_MONOTONIC, &requestStart);


    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            register double r = dgemm1[i*n+j] ;
            for (int k=0; k<n; k++) {
                r += a[i*n+k] * b[k*n+j];
            }
            dgemm1[i*n+j] = r;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &requestEnd);
    double dgemm1Time; 
    dgemm1Time = (requestEnd.tv_sec - requestStart.tv_sec) * 1e9; 
    dgemm1Time = (dgemm1Time + (requestEnd.tv_nsec - requestStart.tv_nsec)) * 1e-6; 


    clock_gettime(CLOCK_MONOTONIC, &requestStart);

    printf("Starting dgemm2\n");
    for (int i = 0; i < n; i+= 2) {
        for (int j = 0; j < n; j+= 2) {
            register int t = i*n+j; register int tt = t+n; 
            register double c00 = dgemm2[t]; register double c01 = dgemm2[t+1];  register double c10 = dgemm2[tt]; register double c11 = dgemm2[tt+1];

            for(int k = 0; k < n; k += 2) {
                register int ta = i*n+k; register int tta = ta+n; register int tb = k*n+j; register int ttb = tb+n;
                register double a00 = a[ta]; register double a01 = a[ta+1]; register double a10 = a[tta]; register double a11 = a[tta+1];
                register double b00 = b[tb]; register double b01 = b[tb+1]; register double b10 = b[ttb]; register double b11 = b[ttb+1];

                c00 += a00*b00 + a01*b10;
                c01 += a00*b01 + a01*b11;
                c10 += a10*b00 + a11*b10;
                c11 += a10*b01 + a11*b11;
             }
             dgemm2[t] = c00;
             dgemm2[t+1] = c01;
             dgemm2[tt] = c10;
             dgemm2[tt+1] = c11;
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &requestEnd);
    double dgemm2Time; 
    dgemm2Time = (requestEnd.tv_sec - requestStart.tv_sec) * 1e9; 
    dgemm2Time = (dgemm2Time + (requestEnd.tv_nsec - requestStart.tv_nsec)) * 1e-6; 


    printf("dgemm0: %lf ms\n", dgemm0Time);
    printf("dgemm1: %lf ms\n", dgemm1Time);
    printf("dgemm2: %lf ms\n", dgemm2Time);

    double diff = 0.0;

    for (int i = 0; i < n*n; ++i) {
        diff += fabs(dgemm0[i] - dgemm1[i]);
    }

    printf("\nMaximum difference between dgemm0 and dgemm1 = %lf\n", diff);
    return 0;
}