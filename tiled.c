#include "matmul.h"

void mm_tiled(const double* A, const double* B, double* C, size_t N, size_t T) {
    for (size_t ii = 0; ii < N; ii += T)
        for (size_t kk = 0; kk < N; kk += T)
            for (size_t jj = 0; jj < N; jj += T) {
                size_t imax = ii + T < N ? ii + T : N;
                size_t kmax = kk + T < N ? kk + T : N;
                size_t jmax = jj + T < N ? jj + T : N;

                for (size_t i = ii; i < imax; i++)
                    for (size_t k = kk; k < kmax; k++) {
                        double aik = A[i * N + k];
                        for (size_t j = jj; j < jmax; j++)
                            C[i * N + j] += aik * B[k * N + j];
                    }
            }
}