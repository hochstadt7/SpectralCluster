
#include <stdlib.h>
#include <stdio.h>
#include "ShmidtAux.h"


double ***modifeied_gram_shmidt(double **A,int n){
    int i,j,k;
    double **R,**Q;
    double **U;
    double ***ret=(double***)malloc(2*sizeof(double **));
    double *curr_column,*sec_column;

    U=my_alloc(n,n);
    R=my_alloc(n,n);
    Q=my_alloc(n,n);

    curr_column=(double *)malloc(n*sizeof (double ));
    sec_column=(double *)malloc(n*sizeof (double ));
    copy_arrays(U,A,n);

    for(i=0; i<n; i++){
        set_col(U,curr_column,i,n);
        R[i][i]=get_norm(curr_column,n);
        for(j=0;j<n;j++){
            Q[j][i]=((curr_column[j])/(R[i][i]));
        }

        for(j=i+1; j<n;j++){
            //set_col(Q,curr_column,i,n); calculated already
            set_col(U,sec_column,j,n);
            R[i][j]=mult_vectors(curr_column,sec_column,n);
            
            for(k=0; k<n; k++){
                U[k][j]-=((R[i][j])*(curr_column[k]));
            }
        }
    }
    free_arrays(U,n);
    free(curr_column);free(sec_column);

    ret[0]=Q;ret[1]=R;
    return ret;

}
