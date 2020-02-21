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

    if (n < blockSize) {
        printf("\nBlock size must be <= n\n\n");
        return -1;
    }

    struct timespec requestStart, requestEnd;

    srand(time(0));

    double *a;
    double *b;

    double *ijk;
    double *jik;
    double *kij;
    double *ikj;
    double *jki;
    double *kji;

    a = (double *)calloc(sizeof(double), n*n);
    b = (double *)calloc(sizeof(double), n*n);
    
    ijk = (double *)calloc(sizeof(double), n*n);
    kij = (double *)calloc(sizeof(double), n*n);
    jki = (double *)calloc(sizeof(double), n*n);
    jik = (double *)calloc(sizeof(double), n*n);
    ikj = (double *)calloc(sizeof(double), n*n);
    kji = (double *)calloc(sizeof(double), n*n);

    for (int i=0; i<n*n; i++) {
        a[i] = (double)(rand() % 13);
        b[i] = (double)(rand() % 13);
    }

    printf("\n\nTesting with n = %d, b = %d\n", n, blockSize);

    printf("Starting ijk\n");


    clock_gettime(CLOCK_MONOTONIC, &requestStart);


    for (int i = 0; i < n; i += blockSize) {
        for (int j = 0; j < n; j += blockSize) {
            for (int k = 0; k < n; k += blockSize){
                for (int i1 = i; i1 < i+blockSize; i1 += 2) {
                    for (int j1 = j; j1 < j+blockSize; j1 += 2) {
                        register int c00Index = i1*n + j1;
                        register int c10Index = c00Index + n;

                        register double c00 = ijk[c00Index];
                        register double c01 = ijk[c00Index+1];
                        register double c10 = ijk[c10Index];
                        register double c11 = ijk[c10Index+1];

                        for (int k1 = k; k1 < k+blockSize; k1 += 2) {
                            register int a00Index = i1*n + k1;
                            register int a10Index = a00Index + n;
                            register int b00Index = k1*n + j1;
                            register int b10Index = b00Index + n;

                            register double a00 = a[a00Index];
                            register double a01 = a[a00Index+1];
                            register double a10 = a[a10Index];
                            register double a11 = a[a10Index+1];
                            register double b00 = b[b00Index];
                            register double b01 = b[b00Index+1];
                            register double b10 = b[b10Index];
                            register double b11 = b[b10Index+1];

                            c00 += a00*b00 + a01 * b10;
                            c01 += a00*b01 + a01 * b11;
                            c10 += a10*b00 + a11 * b10;
                            c11 += a10*b01 + a11 * b11;
                        }
                        ijk[c00Index] = c00;
                        ijk[c00Index+1] = c01;
                        ijk[c10Index] = c10;
                        ijk[c10Index+1] = c11;
                  
                    }
                }
            }
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &requestEnd);
    

    double ijkTime; 
    ijkTime = (requestEnd.tv_sec - requestStart.tv_sec) * 1e9; 
    ijkTime = (ijkTime + (requestEnd.tv_nsec - requestStart.tv_nsec)) * 1e-6; 

    printf("Starting jik\n");


    clock_gettime(CLOCK_MONOTONIC, &requestStart);


    for (int j = 0; j < n; j += blockSize) {
        for (int i = 0; i < n; i += blockSize) {
            for (int k = 0; k < n; k += blockSize){
                for (int j1 = j; j1 < j+blockSize; j1 += 2) {
                    for (int i1 = i; i1 < i+blockSize; i1 += 2) {
                        register int c00Index = i1*n + j1;
                        register int c10Index = c00Index + n;

                        register double c00 = jik[c00Index];
                        register double c01 = jik[c00Index+1];
                        register double c10 = jik[c10Index];
                        register double c11 = jik[c10Index+1];

                        for (int k1 = k; k1 < k+blockSize; k1 += 2) {
                            register int a00Index = i1*n + k1;
                            register int a10Index = a00Index + n;
                            register int b00Index = k1*n + j1;
                            register int b10Index = b00Index + n;

                            register double a00 = a[a00Index];
                            register double a01 = a[a00Index+1];
                            register double a10 = a[a10Index];
                            register double a11 = a[a10Index+1];
                            register double b00 = b[b00Index];
                            register double b01 = b[b00Index+1];
                            register double b10 = b[b10Index];
                            register double b11 = b[b10Index+1];

                            c00 += a00*b00 + a01 * b10;
                            c01 += a00*b01 + a01 * b11;
                            c10 += a10*b00 + a11 * b10;
                            c11 += a10*b01 + a11 * b11;
                        }
                        jik[c00Index] = c00;
                        jik[c00Index+1] = c01;
                        jik[c10Index] = c10;
                        jik[c10Index+1] = c11;
                  
                    }
                }
            }
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &requestEnd);
    

    double jikTime; 
    jikTime = (requestEnd.tv_sec - requestStart.tv_sec) * 1e9; 
    jikTime = (jikTime + (requestEnd.tv_nsec - requestStart.tv_nsec)) * 1e-6; 

    printf("Starting kij\n");

    clock_gettime(CLOCK_MONOTONIC, &requestStart);

    for (int k = 0; k < n; k += blockSize) {
        for (int i = 0; i < n; i += blockSize) {
            for (int j = 0; j < n; j += blockSize){
                for (int k1 = k; k1 < k+blockSize; k1 += 2) {
                    for (int i1 = i; i1 < i+blockSize; i1 += 2) {
                        register int a00Index = i1*n + k1;
                        register int a10Index = a00Index + n;

                        register double a00 = a[a00Index];
                        register double a01 = a[a00Index+1];
                        register double a10 = a[a10Index];
                        register double a11 = a[a10Index+1];

                        for (int j1 = j; j1 < j+blockSize; j1 += 2) {
                            register int c00Index = i1*n + j1;
                            register int c10Index = c00Index + n;
                            register int b00Index = k1*n + j1;
                            register int b10Index = b00Index + n;

                            register double b00 = b[b00Index];
                            register double b01 = b[b00Index+1];
                            register double b10 = b[b10Index];
                            register double b11 = b[b10Index+1];

                            kij[c00Index] += a00*b00 + a01 * b10;
                            kij[c00Index+1] += a00*b01 + a01 * b11;
                            kij[c10Index] += a10*b00 + a11 * b10;
                            kij[c10Index+1] += a10*b01 + a11 * b11;

                        }
                  
                    }
                }
            }
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &requestEnd);
    

    double kijTime; 
    kijTime = (requestEnd.tv_sec - requestStart.tv_sec) * 1e9; 
    kijTime = (kijTime + (requestEnd.tv_nsec - requestStart.tv_nsec)) * 1e-6; 

    printf("Starting ikj\n");

    clock_gettime(CLOCK_MONOTONIC, &requestStart);

    for (int i = 0; i < n; i += blockSize) {
        for (int k = 0; k < n; k += blockSize) {
            for (int j = 0; j < n; j += blockSize){
                for (int i1 = i; i1 < i+blockSize; i1 += 2) {
                    for (int k1 = k; k1 < k+blockSize; k1 += 2) {
                        register int a00Index = i1*n + k1;
                        register int a10Index = a00Index + n;

                        register double a00 = a[a00Index];
                        register double a01 = a[a00Index+1];
                        register double a10 = a[a10Index];
                        register double a11 = a[a10Index+1];

                        for (int j1 = j; j1 < j+blockSize; j1 += 2) {
                            register int c00Index = i1*n + j1;
                            register int c10Index = c00Index + n;
                            register int b00Index = k1*n + j1;
                            register int b10Index = b00Index + n;

                            register double b00 = b[b00Index];
                            register double b01 = b[b00Index+1];
                            register double b10 = b[b10Index];
                            register double b11 = b[b10Index+1];

                            ikj[c00Index] += a00*b00 + a01 * b10;
                            ikj[c00Index+1] += a00*b01 + a01 * b11;
                            ikj[c10Index] += a10*b00 + a11 * b10;
                            ikj[c10Index+1] += a10*b01 + a11 * b11;

                        }
                  
                    }
                }
            }
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &requestEnd);
    

    double ikjTime; 
    ikjTime = (requestEnd.tv_sec - requestStart.tv_sec) * 1e9; 
    ikjTime = (ikjTime + (requestEnd.tv_nsec - requestStart.tv_nsec)) * 1e-6; 

    printf("Starting kji\n");

    clock_gettime(CLOCK_MONOTONIC, &requestStart);

    for (int k = 0; k < n; k += blockSize) {
        for (int j = 0; j < n; j += blockSize) {
            for (int i = 0; i < n; i += blockSize){
                for (int k1 = k; k1 < k+blockSize; k1 += 2) {
                    for (int j1 = j; j1 < j+blockSize; j1 += 2) {
                        register int b00Index = k1*n + j1;
                        register int b10Index = b00Index + n;

                        register double b00 = b[b00Index];
                        register double b01 = b[b00Index+1];
                        register double b10 = b[b10Index];
                        register double b11 = b[b10Index+1];

                        for (int i1 = i; i1 < i+blockSize; i1 += 2) {
                            register int c00Index = i1*n + j1;
                            register int c10Index = c00Index + n;
                            register int a00Index = i1*n + k1;
                            register int a10Index = a00Index + n;

                            register double a00 = a[a00Index];
                            register double a01 = a[a00Index+1];
                            register double a10 = a[a10Index];
                            register double a11 = a[a10Index+1];

                            kji[c00Index] += a00*b00 + a01 * b10;
                            kji[c00Index+1] += a00*b01 + a01 * b11;
                            kji[c10Index] += a10*b00 + a11 * b10;
                            kji[c10Index+1] += a10*b01 + a11 * b11;

                        }
                  
                    }
                }
            }
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &requestEnd);
    

    double kjiTime; 
    kjiTime = (requestEnd.tv_sec - requestStart.tv_sec) * 1e9; 
    kjiTime = (kjiTime + (requestEnd.tv_nsec - requestStart.tv_nsec)) * 1e-6; 

    printf("Starting jki\n");

    clock_gettime(CLOCK_MONOTONIC, &requestStart);

    for (int j = 0; j < n; j += blockSize) {
        for (int k = 0; k < n; k += blockSize) {
            for (int i = 0; i < n; i += blockSize){
                for (int j1 = j; j1 < j+blockSize; j1 += 2) {
                    for (int k1 = k; k1 < k+blockSize; k1 += 2) {
                        register int b00Index = k1*n + j1;
                        register int b10Index = b00Index + n;

                        register double b00 = b[b00Index];
                        register double b01 = b[b00Index+1];
                        register double b10 = b[b10Index];
                        register double b11 = b[b10Index+1];

                        for (int i1 = i; i1 < i+blockSize; i1 += 2) {
                            register int c00Index = i1*n + j1;
                            register int c10Index = c00Index + n;
                            register int a00Index = i1*n + k1;
                            register int a10Index = a00Index + n;

                            register double a00 = a[a00Index];
                            register double a01 = a[a00Index+1];
                            register double a10 = a[a10Index];
                            register double a11 = a[a10Index+1];

                            jki[c00Index] += a00*b00 + a01 * b10;
                            jki[c00Index+1] += a00*b01 + a01 * b11;
                            jki[c10Index] += a10*b00 + a11 * b10;
                            jki[c10Index+1] += a10*b01 + a11 * b11;

                        }
                  
                    }
                }
            }
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &requestEnd);
    

    double jkiTime; 
    jkiTime = (requestEnd.tv_sec - requestStart.tv_sec) * 1e9; 
    jkiTime = (jkiTime + (requestEnd.tv_nsec - requestStart.tv_nsec)) * 1e-6; 


    printf("\nijk: %lf ms\n", ijkTime);
    printf("jik: %lf ms\n", jikTime);
    printf("kij: %lf ms\n", kijTime);
    printf("ikj: %lf ms\n", ikjTime);
    printf("kji: %lf ms\n", kjiTime);
    printf("jki: %lf ms\n", jkiTime);

    double diff = 0.0;

    for (int i = 0; i < n*n; ++i) {
        diff += fabs(ijk[i] - jik[i]);
        diff += fabs(ijk[i] - kij[i]);
        diff += fabs(ijk[i] - ikj[i]);
        diff += fabs(ijk[i] - kji[i]);
        diff += fabs(ijk[i] - jki[i]);
    }

    printf("\nMaximum difference = %lf\n", diff);

    free(a);free(b);free(ijk);free(jik);free(kij);free(ikj);free(kji);free(jki);
}