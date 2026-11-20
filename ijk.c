#include "matmul.h"

void mm_ijk(const double* A, const double* B, double* C, size_t N) {
    for (size_t i = 0; i < N; i++)
        for (size_t j = 0; j < N; j++) {
            double sum = 0.0;
            for (size_t k = 0; k < N; k++) sum += A[i * N + k] * B[k * N + j];
            C[i * N + j] = sum;
        }
}