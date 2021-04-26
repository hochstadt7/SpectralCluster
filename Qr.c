#include <stdio.h>
#include <stdlib.h>
#include "GramShmidt.h"
#include "SchmidtAux.h"
#include <math.h>
#define EPSILON 0.0001


/* diagonal matrix with k on the diagonal */
double **get_scalar_matrix(int n, int k) {
    int i, j;
    double **res = allocate_matrix(n, n);
    if(res==NULL){
        return NULL;
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            res[i][j] = (i == j) ? k : 0;
        }
    }
    return res;
}

/* check whether the difference between two matrices is smaller than EPSILON */
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


/* QR iteration algorithm */
double ***qr_iter(double **A, int n) {
    /* variable declaration */
    double **A_tag, **Q_tag, **updated_Q_tag, **Q, **R;
    double **GS_R, **GS_Q, **GS_U;
    double ***ret, ***obtain_q_r;
    int i;
    Q = allocate_matrix(n, n);
    R = allocate_matrix(n, n);
    /* memory for matrices used in the Gram Schmidt algorithm are allocated once, here */
    GS_U = allocate_matrix(n, n);
    GS_R = allocate_matrix(n, n);
    GS_Q = allocate_matrix(n, n);
    ret = (double ***) malloc(2 * sizeof(double **));
    obtain_q_r = (double ***) malloc(2 * sizeof(double **));
    A_tag = allocate_matrix(n, n);
    /* initiate Q_tag */
    Q_tag = get_scalar_matrix(n, 1);
    /* initiate updated_Q_tag */
    updated_Q_tag = get_scalar_matrix(n, 0);
    if(ret==NULL||GS_U==NULL||GS_R==NULL||GS_Q==NULL||Q==NULL||R==NULL||obtain_q_r==NULL||A_tag==NULL||Q_tag==NULL||updated_Q_tag==NULL){
        printf("Error: allocation failed\n");
        return NULL;
    }
    /* initiate A_tag */
    copy_matrix(A_tag, A, n);

    for (i = 0; i < n; i++) {
        if(!(modified_gram_schmidt(A_tag, n, obtain_q_r,GS_R, GS_Q, GS_U)))
        {
            return NULL;
        }
        /* move results from array to the Q, R variables */
        copy_matrix(Q, obtain_q_r[0], n);
        copy_matrix(R, obtain_q_r[1], n);
        /* updated A_tag matrix to be RQ */
        mult_matrices((const double **) R, (const double **) Q, A_tag, n);
        /* multiply Q_tag with Q, store in updated_Q_tag  */
        mult_matrices((const double **) Q_tag, (const double **) Q, updated_Q_tag, n);
        /* if the new Q_tag matrix is very similar to the previous Q_tag, return the QR decomposition */
        if (!epsilon_diff(Q_tag, updated_Q_tag, n)) {
            ret[0] = A_tag;
            ret[1] = Q_tag;
            free_matrix(updated_Q_tag, n);
            free_matrix(Q, n);
            free_matrix(R, n);
            free_matrix(GS_Q, n);
            free_matrix(GS_R, n);
            free_matrix(GS_U, n);
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
    free_matrix(GS_Q, n);
    free_matrix(GS_R, n);
    free_matrix(GS_U, n);
    return ret;
}
