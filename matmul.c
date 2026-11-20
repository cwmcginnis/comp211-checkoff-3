#define _POSIX_C_SOURCE 200809L

#include "matmul.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static double now_sec(void) {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec + t.tv_nsec * 1e-9;
}

int main(int argc, char** argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s {ijk|ikj|tiled} N [T]\n", argv[0]);
        return 1;
    }

    const char* mode = argv[1];
    size_t N = strtoul(argv[2], NULL, 10);
    size_t T = 0;

    if (strcmp(mode, "tiled") == 0) {
        if (argc < 4) return 1;
        T = strtoul(argv[3], NULL, 10);
    }

    size_t count = N * N;

    double* A = malloc(count * sizeof(double));
    double* B = malloc(count * sizeof(double));
    double* C = calloc(count, sizeof(double));

    for (size_t i = 0; i < count; i++) {
        A[i] = (double)(i % 23) / 23.0;
        B[i] = (double)(i % 19) / 19.0;
    }

    double start = now_sec();

    if (strcmp(mode, "ijk") == 0)
        mm_ijk(A, B, C, N);
    else if (strcmp(mode, "ikj") == 0)
        mm_ikj(A, B, C, N);
    else if (strcmp(mode, "tiled") == 0)
        mm_tiled(A, B, C, N, T);
    else
        return 1;

    double elapsed = now_sec() - start;

    // Prevent compiler from eliminating the computation
    __asm__ __volatile__("" : : "r"(C) : "memory");

    if (strcmp(mode, "tiled") == 0)
        printf("tiled (T=%zu): %.6f s\n", T, elapsed);
    else
        printf("%s: %.6f s\n", mode, elapsed);

    free(A);
    free(B);
    free(C);

    return 0;
}