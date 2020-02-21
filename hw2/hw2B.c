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

    double *ijkB;
    double *kijB;
    double *jkiB;
    double *jikB;
    double *ikjB;
    double *kjiB;



    a = (double *)calloc(sizeof(double), n*n);
    b = (double *)calloc(sizeof(double), n*n);

    ijkB = (double *)calloc(sizeof(double), n*n);
    kijB = (double *)calloc(sizeof(double), n*n);
    jkiB = (double *)calloc(sizeof(double), n*n);
    jikB = (double *)calloc(sizeof(double), n*n);
    ikjB = (double *)calloc(sizeof(double), n*n);
    kjiB = (double *)calloc(sizeof(double), n*n);



    for (int i=0; i<n*n; i++) {
        a[i] = (double)(rand() % 13);
        b[i] = (double)(rand() % 13);
    }

    printf("\n\nTesting with n = %d, b = %d\n", n, blockSize);

    printf("Starting ijkB\n");

    clock_gettime(CLOCK_MONOTONIC, &requestStart);

    for (int i = 0; i < n; i += blockSize) {
        for (int j = 0; j < n; j += blockSize) {
            for (int k = 0; k < n; k += blockSize) {
                for (int i1 = i; i1 < i + blockSize; ++i1) {
                    for (int j1 = j; j1 < j + blockSize; ++j1) {
                        register double r = ijkB[i1*n+j1];
                        for (int k1 = k; k1< k + blockSize; ++k1) {
                            r += a[i1*n + k1] * b[k1*n + j1];
                        }
                        ijkB[i1*n + j1] = r;
                    }
                }
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &requestEnd);
    double ijkBTime; 
    ijkBTime = (requestEnd.tv_sec - requestStart.tv_sec) * 1e9; 
    ijkBTime = (ijkBTime + (requestEnd.tv_nsec - requestStart.tv_nsec)) * 1e-6; 

    printf("Starting jikB\n");

    clock_gettime(CLOCK_MONOTONIC, &requestStart);

    for (int j = 0; j < n; j += blockSize) {
        for (int i = 0; i < n; i += blockSize) {
            for (int k = 0; k < n; k += blockSize) {
                for (int j1 = j; j1 < j + blockSize; ++j1) {
                    for (int i1 = i; i1 < i + blockSize; ++i1) {
                        register double r = jikB[i1*n+j1];
                        for (int k1 = k; k1< k + blockSize; ++k1) {
                            r += a[i1*n + k1] * b[k1*n + j1];
                        }
                        jikB[i1*n + j1] = r;
                    }
                }
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &requestEnd);
    double jikBTime; 
    jikBTime = (requestEnd.tv_sec - requestStart.tv_sec) * 1e9; 
    jikBTime = (jikBTime + (requestEnd.tv_nsec - requestStart.tv_nsec)) * 1e-6; 


    printf("Starting kijB\n");

    clock_gettime(CLOCK_MONOTONIC, &requestStart);


    for (int k = 0; k < n; k += blockSize) {
        for (int i = 0; i < n; i += blockSize) {
            for (int j = 0; j < n; j += blockSize) {
                for (int k1 = k; k1 < k+blockSize; k1++){
                    for (int i1 = i; i1 < i+blockSize; i1++) {
                        register double r = a[i1*n+k1];
                        for (int j1 = j; j1 < j+blockSize; j1++) {
                            kijB[i1*n+j1] += r * b[k1*n+j1];
                        }
                    }
                }
            }
        } 
    }

    clock_gettime(CLOCK_MONOTONIC, &requestEnd);
    double kijBTime; 
    kijBTime = (requestEnd.tv_sec - requestStart.tv_sec) * 1e9; 
    kijBTime = (kijBTime + (requestEnd.tv_nsec - requestStart.tv_nsec)) * 1e-6; 

    printf("Starting ikjB\n");

    clock_gettime(CLOCK_MONOTONIC, &requestStart);


    for (int i = 0; i < n; i += blockSize) {
        for (int k = 0; k < n; k += blockSize) {
            for (int j = 0; j < n; j += blockSize) {
                for (int i1 = i; i1 < i+blockSize; i1++){
                    for (int k1 = k; k1 < k+blockSize; k1++) {
                        register double r = a[i1*n+k1];
                        for (int j1 = j; j1 < j+blockSize; j1++) {
                            ikjB[i1*n+j1] += r * b[k1*n+j1];
                        }
                    }
                }
            }
        } 
    }

    clock_gettime(CLOCK_MONOTONIC, &requestEnd);
    double ikjBTime; 
    ikjBTime = (requestEnd.tv_sec - requestStart.tv_sec) * 1e9; 
    ikjBTime = (ikjBTime + (requestEnd.tv_nsec - requestStart.tv_nsec)) * 1e-6; 


    printf("Starting jkiB\n");

    clock_gettime(CLOCK_MONOTONIC, &requestStart);

    for (int j = 0; j < n; j += blockSize) {
        for (int k = 0; k < n; k += blockSize) {
            for (int i = 0; i < n; i += blockSize) {
                for (int j1 = j; j1 < j + blockSize; ++j1) {
                    for (int k1 = k; k1 < k + blockSize; ++k1) {
                        double r = b[k1*n+j1];
                        for (int i1 = i; i1< i + blockSize; ++i1) {
                            jkiB[i1*n+j1] += a[i1*n+k1] * r;
                        }
                    }
                }
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &requestEnd);
    double jkiBTime; 
    jkiBTime = (requestEnd.tv_sec - requestStart.tv_sec) * 1e9; 
    jkiBTime = (jkiBTime + (requestEnd.tv_nsec - requestStart.tv_nsec)) * 1e-6; 

    printf("Starting kjiB\n");

    clock_gettime(CLOCK_MONOTONIC, &requestStart);

    for (int k = 0; k < n; k += blockSize) {
        for (int j = 0; j < n; j += blockSize) {
            for (int i = 0; i < n; i += blockSize) {
                for (int k1 = k; k1 < k + blockSize; ++k1) {
                    for (int j1 = j; j1 < j + blockSize; ++j1) {
                        double r = b[k1*n+j1];
                        for (int i1 = i; i1< i + blockSize; ++i1) {
                            kjiB[i1*n+j1] += a[i1*n+k1] * r;
                        }
                    }
                }
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &requestEnd);
    double kjiBTime; 
    kjiBTime = (requestEnd.tv_sec - requestStart.tv_sec) * 1e9; 
    kjiBTime = (kjiBTime + (requestEnd.tv_nsec - requestStart.tv_nsec)) * 1e-6; 

    printf("\nijkB: %lf ms\n", ijkBTime);
    printf("jikB: %lf ms\n", jikBTime);
    printf("kijB: %lf ms\n", kijBTime);
    printf("ikjB: %lf ms\n", ikjBTime);
    printf("jkiB: %lf ms\n", jkiBTime);
    printf("kjiB: %lf ms\n", kjiBTime);



    double diff = 0.0;

    for (int i = 0; i < n*n; ++i) {
        diff += fabs(ijkB[i] - jikB[i]);
        diff += fabs(ijkB[i] - kijB[i]);
        diff += fabs(ijkB[i] - ikjB[i]);
        diff += fabs(ijkB[i] - jkiB[i]);
        diff += fabs(ijkB[i] - kjiB[i]);

    }

    printf("\nMaximum difference = %lf\n", diff);

    free(a);free(b);free(ijkB);free(jikB);free(kijB);free(ikjB);free(jkiB);free(kjiB);

    return 0;
}
