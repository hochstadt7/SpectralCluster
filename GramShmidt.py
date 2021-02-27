import numpy as np
from numpy import linalg as la


def modified_gram_schmidt(A, n):
    ret = [None, None]
    R = np.zeros((n, n))
    Q = np.zeros((n, n))
    U = A.copy()
    for i in range(n):
        my_norm = la.norm(U[:, i])
        R[i, i] = my_norm * my_norm
        Q[:, i] = np.divide(U[:, i], R[i, i])
        for j in range(i + 1, n):
            R[i, j] = np.dot(Q[:, i].T, U[:, j])
            U[:, j] = np.subtract(U[:, j], np.multiply(R[i, j], Q[:, i]))
    ret[0] = Q
    ret[1] = R
    return ret


def modified_gram_schmidt_np(A):
    ret = [None, None]
    ret[0], ret[1] = np.linalg.qr(A)
    return ret
