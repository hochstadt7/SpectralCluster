#include <stdio.h>
#include <stdlib.h>
#include "GramShmidt.h"
#include "ShmidtAux.h"
#include <math.h>
#include <assert.h>

#define EPSILON 0.0001

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
    double pos_first,pos_sec,res;
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            pos_first=fabs(first[i][j]); pos_sec=fabs(second[i][j]);
//printf("-- %lf --",(pos_first-pos_sec));
            res=pos_first-pos_sec;
            if(res>EPSILON || res<(-EPSILON) ){
                printf("yey\n");
                return 1;
            }
        }
        printf("\n");
    }
    return 0;
}


/*QR iteration*/
double ***qr_iter(double** A,int n){
    double **A_tag,**Q_tag,**update,**Q,**R;
    double ***ret,***obtain_q_r;
    int i,j,k;
    A_tag=my_alloc(n,n);
    update=my_alloc(n,n);
    Q_tag=get_identity(n);
    Q=my_alloc(n,n);R=my_alloc(n,n);
    ret=(double***)malloc(2*sizeof(double **));
    obtain_q_r=(double***)malloc(2*sizeof(double **));

    assert(ret!=NULL);
    copy_arrays(A_tag,A,n);
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            update[i][j]=0;


        }
    }

    for(i=0;i<n;i++){
        modifeied_gram_shmidt(A_tag,n,obtain_q_r);

        copy_arrays(Q,obtain_q_r[0],n);copy_arrays(R,obtain_q_r[1],n);
        free_arrays(obtain_q_r[0],n); free_arrays(obtain_q_r[1],n);

        mult_matrices(R,Q,A_tag,n);

        mult_matrices(Q_tag,Q,update,n);


        if (!epsilon_diff(Q_tag,update,n)){
            printf("finish");
            ret[0]=A_tag;ret[1]=Q_tag;
            free_arrays(update,n);
            free_arrays(Q,n);free_arrays(R,n);
            free(obtain_q_r);

            return ret;
        }
        printf("still run\n\n");



        copy_arrays(Q_tag,update,n);

    }
    printf("all iterations passed\n");
    //need do not free if n=0 (possible?)
    ret[0]=A_tag;ret[1]=Q_tag;
    free(obtain_q_r);

    free_arrays(update,n);
    free_arrays(Q,n);free_arrays(R,n);
    return ret;
}
