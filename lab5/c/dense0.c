#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "time.h"

#define IDX(i, j, n) ((i) * ((i) + 1) / 2 + (j)) // <- OPT 2

int chol(double *A, const unsigned int n)
{
    register unsigned int i;
    register unsigned int j;
    register unsigned int k;

    register double tmp;

    for (j = 0; j < n; j++)
    {
        for (i = j; i < n; i++)
        {
            tmp = A[IDX(i, j, n)]; /* <- OPT 1 */
            for (k = 0; k < j; k++)
            {
                tmp -= A[IDX(i, k, n)] *
                       A[IDX(j, k, n)];
            }
            A[IDX(i, j, n)] = tmp;
        }

        if (A[IDX(j, j, n)] < 0.0)
            return (1);

        tmp = A[IDX(j, j, n)] = sqrt(A[IDX(j, j, n)]);
        for (i = j + 1; i < n; i++)
        {
            A[IDX(i, j, n)] /= tmp;
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
