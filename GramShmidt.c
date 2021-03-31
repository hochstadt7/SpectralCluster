
#include <stdlib.h>
#include <stdio.h>
#include "ShmidtAux.h"
#include <assert.h>


void modified_gram_schmidt(double **A,int n,double ***obtain_q_r){
    int i,j,k;
    double **R,**Q;
    double **U;
    double *curr_column,*sec_column;

    U=my_alloc(n,n);
    R=my_alloc(n,n);
    Q=my_alloc(n,n);
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            R[i][j]=0;
            Q[i][j]=0;
            U[i][j]=0;
        }
    }

    curr_column=(double *)malloc(n*sizeof (double ));
    assert(curr_column!=NULL);
    sec_column=(double *)malloc(n*sizeof (double ));
    assert(sec_column!=NULL);
    copy_arrays(U,A,n);

    for(i=0; i<n; i++){
        set_col(U,curr_column,i,n);
        R[i][i]=get_norm(curr_column,n);
        for(j=0;j<n;j++){
            Q[j][i]=((curr_column[j])/(R[i][i]));
        }
        for(j=i+1; j<n;j++){
            set_col(Q,curr_column,i,n);
            set_col(U,sec_column,j,n);
            R[i][j]=mult_vectors(curr_column,sec_column,n);
            for(k=0; k<n; k++){
                U[k][j]-=((R[i][j])*(curr_column[k]));
            }
        }
    }
    free_arrays(U,n);
    free(curr_column);
    free(sec_column);


    obtain_q_r[0]=Q; obtain_q_r[1]=R;

}
