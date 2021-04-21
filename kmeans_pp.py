import numpy as np
import pandas as pd
import my_kmeans as ckmeans

def dist(a, b):
    return np.sum(np.power(np.subtract(a, b), 2))


def k_means_pp(observations, k):
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


def k_means_pp_np(observations, k):
    centroids = []
    new_centroid_index = np.random.choice(len(observations), 1)[0]
    new_centroid = observations[new_centroid_index]
    centroids.append(new_centroid_index)
    dists = np.power(observations - new_centroid, 2).sum(axis=1)
    for j in range(1, k):
        p = dists / sum(dists)
        new_centroid_index = np.random.choice(len(observations), p=p, size=1)[0]
        new_centroid = observations[new_centroid_index]
        centroids.append(new_centroid_index)
        new_dists = np.power(observations - new_centroid, 2).sum(axis=1)
        dists = np.minimum(dists, new_dists)
    return centroids


def process_pp(observations, k, n, d):
    np.random.seed(0)
    centroids = k_means_pp_np(observations, k)
    observations = observations.tolist()
    labels = ckmeans.k_means_api(observations, centroids, k, n, d)
    if labels is None:
        print("an error has occurred, the program will now shut down")
        exit(0)
    return labels

