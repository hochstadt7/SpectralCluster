import math
import numpy as np


def normalize(x):
    norm = np.linalg.norm(x)
    epsilon = 0.0001
    if abs(norm) < epsilon:
        print("Error: division by zero")
        exit(0)
    return x / norm

# heurisitic for determine k
def eigen_gap_heuristic(e_vectors, e_values, n, k, random):
    e_values_sort = np.argsort(e_values)
    e_vectors_sorted = np.transpose(e_vectors)[e_values_sort]
    e_values_sorted = np.sort(e_values)
    e_values_diff = np.diff(e_values_sorted)
    e_values_diff = e_values_diff[:math.ceil(int(n/2))]
    if random:
        k = np.argmax(e_values_diff) + 1
    selected_e_vectors = e_vectors_sorted[0:k]
    eigen_matrix = np.transpose(selected_e_vectors)
    norm_eigen_matrix = np.apply_along_axis(normalize, 1, eigen_matrix)
    # print(k)
    return k, norm_eigen_matrix