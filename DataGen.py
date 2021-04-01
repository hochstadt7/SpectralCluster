from sklearn.datasets import make_blobs
import numpy as np


def generate_data(n, d, k):
    blobs = make_blobs(n_samples=n, n_features=d, centers=k)
    return blobs[0], blobs[1]


def generate_circle_sample_data(r, n, sigma):
    """Generate circle data with random Gaussian noise."""
    angles = np.random.uniform(low=0, high=2*np.pi, size=n)

    x_epsilon = np.random.normal(loc=0.0, scale=sigma, size=n)
    y_epsilon = np.random.normal(loc=0.0, scale=sigma, size=n)

    x = r*np.cos(angles) + x_epsilon
    y = r*np.sin(angles) + y_epsilon
    return x, y


def generate_concentric_circles_data(param_list):
    """Generates many circle data with random Gaussian noise."""
    coordinates = [[], []]
    for param in param_list:
        data = generate_circle_sample_data(param[0], param[1], param[2])
        coordinates[0].extend(data[0])
        coordinates[1].extend(data[1])
    return coordinates


def generate_circles(n, rings):
    # Radius
    r_list = [2 + 4*i for i in range(rings)]
    # Standard deviation (Gaussian noise).
    sigmas = [0.3]

    param_lists = [[(r, int(n/rings), sigma) for r in r_list] for sigma in sigmas]
    # We store the data on this list.
    coordinates_list = [[], []]
    for i, param_list in enumerate(param_lists):
        coordinates = generate_concentric_circles_data(param_list)
        coordinates_list[0].extend(coordinates[0])
        coordinates_list[1].extend(coordinates[1])
    return np.transpose(np.array(coordinates_list))
