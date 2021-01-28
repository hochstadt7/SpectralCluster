import numpy as np


def get_weight_matrix(n, data):
    x = np.array(data)[:, None, :]
    y = np.array(data)[None, :, :]
    return np.exp(-(np.power(np.linalg.norm(x-y, axis=-1), 2)/2)) - np.identity(n)


def get_diagonal_degree_matrix(n, weights):
    d = np.identity(n) * np.power(np.sum(weights, axis=1), -1/2)
    return d


def get_laplacian_matrix(n, diagonal, weights):
    return np.identity(n) - diagonal.dot(weights).dot(diagonal)