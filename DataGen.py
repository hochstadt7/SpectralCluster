from sklearn.datasets import make_blobs


def generate_data(n, d, k):
    return make_blobs(n_samples=n, n_features=d, centers=k)[0]
