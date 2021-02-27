import numpy as np


def modified_gram_schmidt(a, n):
    r = np.zeros((n, n))
    q = np.zeros((n, n))
    u = a.copy()
    for i in range(n):
        r[i, i] = np.linalg.norm(u[:, i])
        q[:, i] = np.divide(u[:, i], r[i, i])
        for j in range(i + 1, n):
            r[i, j] = np.dot(q[:, i].T, u[:, j])
            u[:, j] = np.subtract(u[:, j], np.multiply(r[i, j], q[:, i]))
    return q, r


def modified_gram_schmidt_np(a):
    return np.linalg.qr(a)
