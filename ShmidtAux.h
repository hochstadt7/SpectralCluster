#ifndef SPECTURALCLUSTER_SHMIDTAUX_H
#define SPECTURALCLUSTER_SHMIDTAUX_H

double **allocate_matrix(int dimension_1, int dimension_2);

void set_col(double **U, double *ret_col, int i, int n);

double get_norm(const double *col, int n);

double mult_vectors(const double *first, const double *second, int n);

void copy_matrix(double **copy, double **paste, int n);

void free_matrix(double **U, int n);

void mult_matrices(const double **first, const double **second, double **res, int n);

void err_message(char *err);

#endif //SPECTURALCLUSTER_SHMIDTAUX_H
