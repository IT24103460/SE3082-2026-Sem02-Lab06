#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1000000
#define STRIP_SIZE 1024

int main() {

    double *A = aligned_alloc(64, N * sizeof(double));
    double *B = aligned_alloc(64, N * sizeof(double));
    double *C = aligned_alloc(64, N * sizeof(double));

    if (A == NULL || B == NULL || C == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Initialize arrays
    for (int i = 0; i < N; i++) {
        A[i] = 2.0;
        B[i] = 3.0;
    }

    double start = omp_get_wtime();

    // Strip mining + OpenMP
    #pragma omp parallel for schedule(static)
    for (int strip = 0; strip < N; strip += STRIP_SIZE) {

        int end = strip + STRIP_SIZE;

        if (end > N) {
            end = N;
        }

        #pragma omp simd aligned(A, B, C:64)
        for (int i = strip; i < end; i++) {
            C[i] = A[i] * B[i];
        }
    }

    double end = omp_get_wtime();

    printf("C[0] = %.2f\n", C[0]);
    printf("C[999999] = %.2f\n", C[N - 1]);
    printf("Execution time = %f seconds\n", end - start);

    free(A);
    free(B);
    free(C);

    return 0;
}