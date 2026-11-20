#ifndef MATMUL_H
#define MATMUL_H

#include <stddef.h>

void mm_ijk(const double* A, const double* B, double* C, size_t N);

void mm_ikj(const double* A, const double* B, double* C, size_t N);

void mm_tiled(const double* A, const double* B, double* C, size_t N, size_t T);

#endif