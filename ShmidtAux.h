//
// Created by LENOVO on 15/01/2021.
//

#ifndef SPECTURALCLUSTER_SHMIDTAUX_H
#define SPECTURALCLUSTER_SHMIDTAUX_H

double **my_alloc(int first_layer,int second_layer);
void set_col(double** U,double* ret_col,int n,int col);
double get_norm(double* col,int n);
double mult_vectors(double** first,double** second,int n);
void copy_arrays(double **copy,double **paste,int n);
void free_arrays(double **U,int n);
void mult_matrices(double **first,double **second,double** res,int n);

#endif //SPECTURALCLUSTER_SHMIDTAUX_H
