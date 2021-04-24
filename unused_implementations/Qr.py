import numpy as np
from unused_implementations import GramSchmidt

epsilon = 0.0001


def qr_iter(a, n):
    q_ort = np.eye(n)
    a_diag = a.copy()
    for i in range(n):
        q, r = GramSchmidt.modified_gram_schmidt(a_diag, n)
        a_diag = np.matmul(r, q)
        new_q = np.matmul(q_ort, q)
        if np.max(np.abs(np.abs(new_q) - np.abs(q_ort))) < epsilon:
            return new_q, a_diag
        q_ort = new_q.copy()
    return q_ort, a_diag
