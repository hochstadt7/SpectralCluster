#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
double **my_alloc(int first_layer, int second_layer){
    int counter;
    double **ret=(double **)malloc(first_layer*sizeof(double *));
    assert(ret!=NULL);
    for(counter=0; counter<first_layer; counter++){
        ret[counter]=(double *)malloc(second_layer*sizeof(double ));
        assert(ret[counter]!=NULL);
    }
    return ret;
}

/*set ret_col to be the i'th column of matrix U*/
void set_col(double** U,double* ret_col,int n,int i){
    int row;

    for(row=0; row<n; row++){
        ret_col[row]=U[row][i];
    }

}

/*calculate norm*/
double get_norm(double* col,int n){
    double ret_sum=0;
    int i;
    for(i=0;i<n;i++){
        ret_sum+=(col[i]*col[i]);
    }
    return sqrt(ret_sum);
}

/*multiply vectors*/
double mult_vectors(double** first,double** second,int n){
    double ret_sum=0;
    int i;
    for(i=0;i<n;i++){
        ret_sum+=((*first)[i])*((*second)[i]);
    }
    return ret_sum;
}

void copy_arrays(double **copy,double **paste,int n){
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            copy[i][j]=paste[i][j];
        }
    }
}

void free_arrays(double **U,int n){
    int i;
    for(i=0;i<n;i++){
        free(U[i]);
    }
    free(U);
}

void mult_matrices(double **first,double **second,double** res,int n){
    int i,j,k;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            res[i][j]=0;
            for(k=0;k<n;k++){
                res[i][j]+=first[i][k]*second[k][j];
            }
        }
    }
}
