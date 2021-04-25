from sklearn.datasets import make_blobs
import numpy as np


# generates a random set of blobs
def generate_data(n, d, k):
    blobs = make_blobs(n_samples=n, n_features=d, centers=k)
    return blobs[0], blobs[1]


# generates a ring of points
def generate_circle_sample_data(params, n):
    r = params["r"]
    sigma = params["s"]
    """Generate circle data with random Gaussian noise."""
    angles = np.random.uniform(low=0, high=2*np.pi, size=n)

    x_epsilon = np.random.normal(loc=0.0, scale=sigma, size=n)
    y_epsilon = np.random.normal(loc=0.0, scale=sigma, size=n)

    x = r*np.cos(angles) + x_epsilon
    y = r*np.sin(angles) + y_epsilon
    z = np.random.normal(loc=0.0, scale=0, size=n)
    return x, y, z


# generate concentric rings
def generate_circles(n, rings, d):
    # Radius
    r_list = [2 + 4*i for i in range(rings)]
    # Standard deviation (Gaussian noise).
    sigmas = [0.3]
    params = [{"r": 2 + 6*i, "s": 0.2} for i in range(rings)]
    # We store the data on this list.
    coordinates_list = [[] for i in range(d)]
    cluster_labels = []
    for i, param_list in enumerate(params):
        coordinates = generate_circle_sample_data(param_list, round(n/rings))
        coordinates_list[0].extend(coordinates[0])
        coordinates_list[1].extend(coordinates[1])
        if d == 3:
            coordinates_list[2].extend(coordinates[2])
        cluster_labels.extend([i for x in coordinates[0]])
    return np.transpose(np.array(coordinates_list)), np.array(cluster_labels)
