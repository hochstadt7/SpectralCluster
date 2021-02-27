import numpy as np


def eigen_gap_heuristic(e_vectors, e_values_diag, n):
    e_values = np.diagonal(e_values_diag)
    e_values_sort = np.argsort(e_values)
    e_vectors_sorted = e_vectors[e_values_sort]
    e_values_sorted = np.around(np.sort(e_values), 2)
    e_values_diff = np.diff(e_values_sorted)
    e_values_diff = e_values_diff[:int(n/2)]
    k = np.argmax(e_values_diff) + 1
    selected_e_vectors = e_vectors_sorted[0:k]
    return k, np.transpose(selected_e_vectors)
