import numpy as np
import GramShmidt

def epsilon_diff(first,second,n):
    for i in range(n):
        for j in range(n):
            if abs(first[i,j]-second[i,j])>0.01:
                return True
    return False

def qr_iter(A,n):

    Q_tag=np.eye(n)
    A_tag=A.copy()
    ret=[None,None]
    for i in range(n):
        obtain_q_r = GramShmidt.modified_gram_shmidt(Q_tag, n)# not sure what is the parameter passed to gram_shmidt
        Q=obtain_q_r[0].copy()
        R=obtain_q_r[1].copy()
        A_tag=np.matmul(R,Q)
        update = np.matmul(Q_tag, Q)
        if not epsilon_diff(Q_tag,update,n):
            ret[0]=A_tag
            ret[1]=Q_tag
            return ret
        Q_tag=update.copy()
    ret[0] = A_tag
    ret[1] = Q_tag
    return ret

