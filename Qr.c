#include <stdio.h>
#include <stdlib.h>
#include "GramShmidt.h"
#include "ShmidtAux.h"
#include <math.h>

#define EPSILON 0.01

/*identity matrix*/
double** get_identity(int n){
    int i,j;
    double **res=my_alloc(n,n);
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            res[i][j]=(i==j)?1:0;
        }
    }
    return res;
}

/*check difference smaller than EPSILON*/
int epsilon_diff(double **first,double **second,int n){
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(fabs(first[i][j]-second[i][j])<=EPSILON)
                return 1;
        }
    }
    return 0;
}

/*QR iteration*/
double ***qr_iter(double** A,int n){
    double **A_tag,**Q_tag,**update,**Q,**R;
    double ***ret,***obtain_q_r;
    int i;
    A_tag=my_alloc(n,n);
    update=my_alloc(n,n);
    Q_tag=get_identity(n);
    Q=my_alloc(n,n);R=my_alloc(n,n);
    ret=(double***)malloc(2*sizeof(double **));
    copy_arrays(A_tag,A,n);

    for(i=0;i<n;i++){
        obtain_q_r=modifeied_gram_shmidt(A_tag,n);
        copy_arrays(Q,obtain_q_r[0],n);copy_arrays(R,obtain_q_r[1],n);
        mult_matrices(R,Q,A_tag,n);
        mult_matrices(Q_tag,Q,update,n);
        if (!epsilon_diff(Q_tag,update,n)){
            ret[0]=A_tag;ret[1]=Q_tag;
            for(i=0;i<2;i++){
                free_arrays(obtain_q_r[i],n);
            }
            free(obtain_q_r);
            free_arrays(update,n);
            free_arrays(Q,n);free_arrays(R,n);
            return ret;
        }
        copy_arrays(Q_tag,update,n);

    }
    //need do not free if n=0
    ret[0]=A_tag;ret[1]=Q_tag;
    for(i=0;i<2;i++){
        free_arrays(obtain_q_r[i],n);
    }
    free(obtain_q_r);
    free_arrays(update,n);
    free_arrays(Q,n);free_arrays(R,n);
    return ret;
}

