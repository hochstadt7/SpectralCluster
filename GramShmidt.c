#include <stdlib.h>
#include <stdio.h>
#include "SchmidtAux.h"
#define EPSILON 0.0001

/* modified gram_schmidt algorithm */
/* the function is passed Q, R, U, rather than create them, in order to minimize memory allocations */
/* similarly, the results aren't returned, but pointed to through the QR array */
int modified_gram_schmidt(double **A, int n, double ***QR, double **R, double **Q, double **U) {
    int i, j, k;
    double *curr_column, *sec_column;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            R[i][j] = 0;
            Q[i][j] = 0;
            U[i][j] = 0;
        }
    }

    curr_column = (double *) malloc(n * sizeof(double));
    sec_column = (double *) malloc(n * sizeof(double));
    if(curr_column==NULL||sec_column==NULL){
        printf("Error: allocation failed\n");
        return 0;
    }
    copy_matrix(U, A, n);
    for (i = 0; i < n; i++) {
        set_col(U, curr_column, i, n);
        R[i][i] = get_norm(curr_column, n);
        /* prevent division by 0 - which shouldn't happen anyway */
        if(R[i][i] > 0) {
            for (j = 0; j < n; j++) {
                Q[j][i] = ((curr_column[j]) / (R[i][i]));
            }
        }
        set_col(Q, curr_column, i, n);
        for (j = i + 1; j < n; j++) {
            set_col(U, sec_column, j, n);
            R[i][j] = mult_vectors(curr_column, sec_column, n);

            for (k = 0; k < n; k++) {
                U[k][j] =U[k][j]- ((R[i][j]) * (curr_column[k]));
            }
        }
    }
    free(curr_column);
    free(sec_column);

    QR[0] = Q;
    QR[1] = R;
    return 1;
}
