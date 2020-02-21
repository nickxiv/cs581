#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("\nInvalid number of arguments.\n\n");
        return -1;
    }
    
    
    const int n = atoi(argv[1]);
    const int blockSize = atoi(argv[2]);

    struct timespec requestStart, requestEnd;

    srand(time(0));

    double *a;
    double *b;

    double *ijkUB;
    double *jikUB;
    double *kijUB;
    double *ikjUB;
    double *jkiUB;
    double *kjiUB;

    a = (double *)calloc(sizeof(double), n*n);
    b = (double *)calloc(sizeof(double), n*n);
    
    ijkUB = (double *)calloc(sizeof(double), n*n);
    kijUB = (double *)calloc(sizeof(double), n*n);
    jkiUB = (double *)calloc(sizeof(double), n*n);
    jikUB = (double *)calloc(sizeof(double), n*n);
    ikjUB = (double *)calloc(sizeof(double), n*n);
    kjiUB = (double *)calloc(sizeof(double), n*n);


    for (int i=0; i<n*n; i++) {
        a[i] = (double)(rand() % 13);
        b[i] = (double)(rand() % 13);
    }

    printf("\n\nTesting with n = %d, b = %d\n", n, blockSize);

    printf("Starting ijkUB\n");


    clock_gettime(CLOCK_MONOTONIC, &requestStart);


    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            register double r = ijkUB[i*n+j] ;
            for (int k=0; k<n; k++) {
                r += a[i*n+k] * b[k*n+j];
            }
            ijkUB[i*n+j] = r;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &requestEnd);
    double ijkUBTime; 
    ijkUBTime = (requestEnd.tv_sec - requestStart.tv_sec) * 1e9; 
    ijkUBTime = (ijkUBTime + (requestEnd.tv_nsec - requestStart.tv_nsec)) * 1e-6; 


    printf("Starting jikUB\n");


    clock_gettime(CLOCK_MONOTONIC, &requestStart);


    for (int j=0; j<n; j++) {
        for (int i=0; i<n; i++) {
            register double r = jikUB[i*n+j] ;
            for (int k=0; k<n; k++) {
                r += a[i*n+k] * b[k*n+j];
            }
            jikUB[i*n+j] = r;
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &requestEnd);
    double jikUBTime; 
    jikUBTime = (requestEnd.tv_sec - requestStart.tv_sec) * 1e9; 
    jikUBTime = (jikUBTime + (requestEnd.tv_nsec - requestStart.tv_nsec)) * 1e-6; 

    printf("Starting kijUB\n");


    clock_gettime(CLOCK_MONOTONIC, &requestStart);


    for (int k=0; k<n; k++) {
        for (int i=0; i<n; i++) {
            register double r = a[i*n+k] ;
            for (int j=0; j<n; j++) {
                kijUB[i*n+j] += r * b[k*n+j];
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &requestEnd);
    double kijUBTime; 
    kijUBTime = (requestEnd.tv_sec - requestStart.tv_sec) * 1e9; 
    kijUBTime = (kijUBTime + (requestEnd.tv_nsec - requestStart.tv_nsec)) * 1e-6; 

    printf("Starting ikjUB\n");


    clock_gettime(CLOCK_MONOTONIC, &requestStart);


    for (int i=0; i<n; i++) {
        for (int k=0; k<n; k++) {
            register double r = a[i*n+k] ;
            for (int j=0; j<n; j++) {
                ikjUB[i*n+j] += r * b[k*n+j];
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &requestEnd);
    double ikjUBTime; 
    ikjUBTime = (requestEnd.tv_sec - requestStart.tv_sec) * 1e9; 
    ikjUBTime = (ikjUBTime + (requestEnd.tv_nsec - requestStart.tv_nsec)) * 1e-6; 


    printf("Starting jkiUB\n");


    clock_gettime(CLOCK_MONOTONIC, &requestStart);


    for (int j=0; j<n; j++) {
        for (int k=0; k<n; k++) {
            register double r = b[k*n+j] ;
            for (int i=0; i<n; i++) {
                jkiUB[i*n+j] += r * a[i*n+k];
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &requestEnd);
    double jkiUBTime; 
    jkiUBTime = (requestEnd.tv_sec - requestStart.tv_sec) * 1e9; 
    jkiUBTime = (jkiUBTime + (requestEnd.tv_nsec - requestStart.tv_nsec)) * 1e-6;

    printf("Starting kjiUB\n");


    clock_gettime(CLOCK_MONOTONIC, &requestStart);


    for (int j=0; j<n; j++) {
        for (int k=0; k<n; k++) {
            register double r = b[k*n+j] ;
            for (int i=0; i<n; i++) {
                kjiUB[i*n+j] += r * a[i*n+k];
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &requestEnd);
    double kjiUBTime; 
    kjiUBTime = (requestEnd.tv_sec - requestStart.tv_sec) * 1e9; 
    kjiUBTime = (kjiUBTime + (requestEnd.tv_nsec - requestStart.tv_nsec)) * 1e-6; 

    printf("\nijkUB: %lf ms\n", ijkUBTime);
    printf("jikUB: %lf ms\n", jikUBTime);
    printf("kijUB: %lf ms\n", kijUBTime);
    printf("ikjUB: %lf ms\n", ikjUBTime);
    printf("kjiUB: %lf ms\n", kjiUBTime);
    printf("jkiUB: %lf ms\n", jkiUBTime);

    double diff = 0.0;

    for (int i = 0; i < n*n; ++i) {
        diff += fabs(ijkUB[i] - kijUB[i]);
        diff += fabs(ijkUB[i] - jikUB[i]);
        diff += fabs(ijkUB[i] - kjiUB[i]);
        diff += fabs(ijkUB[i] - ikjUB[i]);
        diff += fabs(ijkUB[i] - jkiUB[i]);

    }

    printf("\nMaximum difference = %lf\n", diff);

    free(a);free(b);free(ijkUB);free(jikUB);free(kijUB);free(ikjUB);free(jkiUB);free(kjiUB);

    return 0;
}
