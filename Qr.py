import numpy as np
import GramSchmidt

epsilon = 0.0001


def qr_iter(a, n):
    q_ort = np.eye(n)
    a_diag = a.copy()
    for i in range(n):
        # TODO: replace with our GS implementation
        q, r = GramSchmidt.modified_gram_schmidt_np(a_diag)
        a_diag = np.matmul(r, q)
        new_q = np.matmul(q, q_ort)
        if np.max(np.abs(np.abs(new_q) - np.abs(q_ort))) < epsilon:
            return a_diag, new_q
        q_ort = new_q.copy()
    return q_ort, a_diag
