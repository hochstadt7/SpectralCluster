#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ShmidtAux.h"


double **allocate_matrix(int dimension_1, int dimension_2) {
    int counter;
    double **ret = (double **) malloc(dimension_1 * sizeof(double *));
    if(ret==NULL){
        printf("Error: allocation failed\n");
        return NULL;

    }
    for (counter = 0; counter < dimension_1; counter++) {
        ret[counter] = (double *) malloc(dimension_2 * sizeof(double));
        if(ret[counter]==NULL){
            return NULL;
        }
    }
    return ret;
}

/*set ret_col to be the i'th column of matrix U*/
void set_col(double **U, double *ret_col, int i, int n) {
    int row;
    for (row = 0; row < n; row++) {
        ret_col[row] = U[row][i];
    }
}

/*calculate norm*/
double get_norm(const double *col, int n) {
    double ret_sum = 0;
    int i;
    for (i = 0; i < n; i++) {
        ret_sum += (col[i] * col[i]);
    }
    /*TODO find a way to remove sqrt*/
    return sqrt(ret_sum);
}

/*multiply vectors*/
double mult_vectors(const double *first, const double *second, int n) {
    double ret_sum = 0;
    int i;
    for (i = 0; i < n; i++) {
        ret_sum += ((first[i]) * (second[i]));
    }
    return ret_sum;
}

void copy_matrix(double **copy, double **paste, int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            copy[i][j] = paste[i][j];
        }
    }
}

void free_matrix(double **U, int n) {
    int i;
    for (i = 0; i < n; i++) {
        free(U[i]);
    }
    free(U);
}

void mult_matrices(const double **first, const double **second, double **res, int n) {
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            res[i][j] = 0;
            for (k = 0; k < n; k++) {
                res[i][j] += ((first[i][k]) * (second[k][j]));
            }
        }
    }
}

void print_matrix(const double **mat, int n){
    int k, j;
    printf("MATRIX:\n");
    for(k=0; k<n; k++){
        for(j=0; j<n; j++){
            printf("%.2f ", mat[k][j]);
        }
        printf("\n");
    }
    printf("--\n\n");
}
