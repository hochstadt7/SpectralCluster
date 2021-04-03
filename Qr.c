#include <stdio.h>
#include <stdlib.h>
#include "GramShmidt.h"
#include "ShmidtAux.h"
#include <math.h>
#include <assert.h>

#define EPSILON 0.0001

/*identity matrix*/
double **get_scalar_matrix(int n, int k) {
    int i, j;
    double **res = allocate_matrix(n, n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            res[i][j] = (i == j) ? k : 0;
        }
    }
    return res;
}

/*check difference smaller than EPSILON*/
int epsilon_diff(double **first, double **second, int n) {
    int i, j;
    double pos_first, pos_sec, res;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            pos_first = fabs(first[i][j]);
            pos_sec = fabs(second[i][j]);
            res = pos_first - pos_sec;
            if (res > EPSILON || res < (-EPSILON)) {
                return 1;
            }
        }
    }
    return 0;
}


/*QR iteration*/
double ***qr_iter(double **A, int n) {
    /* variable declaration */
    double **A_tag, **Q_tag, **updated_Q_tag, **Q, **R;
    double ***ret, ***obtain_q_r;
    int i;
    Q = allocate_matrix(n, n);
    R = allocate_matrix(n, n);
    ret = (double ***) malloc(2 * sizeof(double **));
    assert(ret != NULL);
    obtain_q_r = (double ***) malloc(2 * sizeof(double **));
    assert(obtain_q_r != NULL);
    /* initiate A_tag */
    A_tag = allocate_matrix(n, n);
    copy_matrix(A_tag, A, n);
    /* initiate Q_tag */
    Q_tag = get_scalar_matrix(n, 1);
    /* initiate updated_Q_tag */
    updated_Q_tag = get_scalar_matrix(n, 0);
    for (i = 0; i < n; i++) {
        modified_gram_schmidt(A_tag, n, obtain_q_r);
        /* move results from array to the Q, R variables */
        copy_matrix(Q, obtain_q_r[0], n);
        copy_matrix(R, obtain_q_r[1], n);
        free_matrix(obtain_q_r[0], n);
        free_matrix(obtain_q_r[1], n);
        /* updated A_tag matrix to be RQ */
        mult_matrices(R, Q, A_tag, n);
        /* multiply Q_tag with Q, store in updated_Q_tag  */
        mult_matrices(Q_tag, Q, updated_Q_tag, n);
        /* check epsilon difference */
        if (!epsilon_diff(Q_tag, updated_Q_tag, n)) {
            ret[0] = A_tag;
            ret[1] = Q_tag;
            free_matrix(updated_Q_tag, n);
            free_matrix(Q, n);
            free_matrix(R, n);
            free(obtain_q_r);
            return ret;
        }
        /* set Q_tag to updated_Q_tag */
        copy_matrix(Q_tag, updated_Q_tag, n);
    }
    ret[0] = A_tag;
    ret[1] = Q_tag;
    free(obtain_q_r);
    free_matrix(updated_Q_tag, n);
    free_matrix(Q, n);
    free_matrix(R, n);
    return ret;
}
