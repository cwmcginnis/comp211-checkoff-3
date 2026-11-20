#include "matmul.h"

void mm_ikj(const double* A, const double* B, double* C, size_t N) {
    for (size_t i = 0; i < N; i++)
        for (size_t k = 0; k < N; k++) {
            double aik = A[i * N + k];
            for (size_t j = 0; j < N; j++) C[i * N + j] += aik * B[k * N + j];
        }
}