#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <x86intrin.h>

#include "time.h"

#define IDX(i, j, n) ((i) * ((i) + 1) / 2 + (j))

#define BLKSIZE 16 // <- OPT 7 FULL SSE

static int max(int a, int b)
{
    if (a > b)
        return (a);
    else
        return (b);
}

int chol(double *A, unsigned int n)
{
    register unsigned int i;
    register unsigned int j;
    register unsigned int k;

    register double tmp, s;
    register __m128d tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
    register __m128d tmp8, tmp9, tmp10, tmp11, tmp12, tmp13, tmp14, tmp15;
    for (j = 0; j < n; j++)
    {
        for (i = j; i < n; i++)
        {
            tmp = A[IDX(i, j, n)]; /* <- OPT 1 */
            for (k = 0; k < j;)
            {
                if (k < max(j - BLKSIZE, 0))
                {                                          // <- OPT 3
                    tmp0 = _mm_loadu_pd(A + IDX(i, k, n)); // <- OPT 4
                    tmp1 = _mm_loadu_pd(A + IDX(j, k, n));
                    tmp2 = _mm_loadu_pd(A + IDX(i, k + 2, n));
                    tmp3 = _mm_loadu_pd(A + IDX(j, k + 2, n));
                    tmp4 = _mm_loadu_pd(A + IDX(i, k + 4, n));
                    tmp5 = _mm_loadu_pd(A + IDX(j, k + 4, n));
                    tmp6 = _mm_loadu_pd(A + IDX(i, k + 6, n));
                    tmp7 = _mm_loadu_pd(A + IDX(j, k + 6, n));
                    tmp8 = _mm_loadu_pd(A + IDX(i, k + 8, n));
                    tmp9 = _mm_loadu_pd(A + IDX(j, k + 8, n));
                    tmp10 = _mm_loadu_pd(A + IDX(i, k + 10, n));
                    tmp11 = _mm_loadu_pd(A + IDX(j, k + 10, n));
                    tmp12 = _mm_loadu_pd(A + IDX(i, k + 12, n));
                    tmp13 = _mm_loadu_pd(A + IDX(j, k + 12, n));
                    tmp14 = _mm_loadu_pd(A + IDX(i, k + 14, n));
                    tmp15 = _mm_loadu_pd(A + IDX(j, k + 14, n));

                    tmp0 = _mm_mul_pd(tmp0, tmp1); // <- OPT 5
                    tmp2 = _mm_mul_pd(tmp2, tmp3);
                    tmp4 = _mm_mul_pd(tmp4, tmp5);
                    tmp6 = _mm_mul_pd(tmp6, tmp7);
                    tmp8 = _mm_mul_pd(tmp8, tmp9);
                    tmp10 = _mm_mul_pd(tmp10, tmp11);
                    tmp12 = _mm_mul_pd(tmp12, tmp13);
                    tmp14 = _mm_mul_pd(tmp14, tmp15);

                    tmp0 = _mm_add_pd(tmp0, tmp2); // <- OPT 6
                    tmp4 = _mm_add_pd(tmp4, tmp6);
                    tmp8 = _mm_add_pd(tmp8, tmp10);
                    tmp12 = _mm_add_pd(tmp12, tmp14);

                    tmp0 = _mm_add_pd(tmp0, tmp4);
                    tmp8 = _mm_add_pd(tmp8, tmp12);

                    tmp0 = _mm_add_pd(tmp0, tmp8);

                    tmp -= tmp0[0] + tmp0[1];
                    k += BLKSIZE;
                }
                else
                {
                    tmp -= A[IDX(i, k, n)] *
                           A[IDX(j, k, n)];
                    k++;
                }
            }

            if (i == j)
            { // <- OPT 7
                if (tmp <= 0)
                    return (1);
                s = sqrt(tmp);
                A[IDX(j, j, n)] = s;
            }
            else
            {
                A[IDX(i, j, n)] = tmp / s;
            }
        }
    }

    return (0);
}

double *alloc_matrix(int n)
{
    double *ret;

    ret = calloc(n * (n + 1) / 2, sizeof(double));
    assert(ret != NULL);

    return (ret);
}

int main(int argc, char **argv)
{
    double *A;
    double t1, t2;
    int i, j, n, ret;

    n = atoi(argv[1]);
    A = alloc_matrix(n);

    for (i = 0; i < n; i++)
        A[IDX(i, i, n)] = 1.0;

    t1 = stamp();
    if (chol(A, n))
        fprintf(stderr, "Error: matrix is either not symmetric or not positive definite.\n");
    t2 = stamp();
    fprintf(stdout, "C:\t%lg [s]\n", t2 - t1);

    free(A);
    return 0;
}
