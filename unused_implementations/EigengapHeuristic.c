s#include <math.h>

int get_eigen_gap(double** board,int n){

    double curr_max,total_max=0;
    int i,total_index;

    for(i=0; i<n/2; i++){
        curr_max=fabs(board[i][i]-board[i+1][i+1]);
        if(curr_max>total_max){
            total_max=curr_max;
            total_index=i;
        }
    }
    return total_index;
}

