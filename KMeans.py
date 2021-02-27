import numpy as np
import my_kmeans as ckmeans


def dist(a, b):
    return np.sum(np.power(np.subtract(a, b), 2))


def k_means_pp(observations, k):
    np.random.seed(0)
    centroids = [np.random.choice(len(observations), 1)[0]]
    for j in range(1, k):
        dists = []
        for i in range(len(observations)):
            holder = []
            for c in centroids:
                holder.append(dist(observations[c], observations[i]))
            di = np.min(holder)
            dists.append(di)
        p = np.divide(dists, sum(dists))
        centroids.append(np.random.choice(len(observations), p=p, size=1)[0])
    return centroids


def get_clusters(data, n, k, d):
    centroids = k_means_pp(data, k)
    observations = data
    return ckmeans.k_means_api(observations, centroids, k, n, d, 300)
