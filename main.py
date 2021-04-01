import DataGen
import GraphGen
import kmeans_pp
from sklearn.cluster import KMeans
import argparse
import time
#from KMeans import *
from Qr import *
from TextualOutput import *
from JaccardMeasure import *
from VisualizeResults import *
from EigenGapSelection import *
from matplotlib import pyplot as plt
import section_four as foury
import numpy as np

# todo: find real values
MAX_CAPACITY_N_2D = 1000
MAX_CAPACITY_K_2D = 10
MAX_CAPACITY_N_3D = 1000
MAX_CAPACITY_K_3D = 10

parser = argparse.ArgumentParser()
parser.add_argument("k", type=int)
parser.add_argument("n", type=int)
parser.add_argument("Random", type=bool)
args = parser.parse_args()
k = int(args.k)
n = int(args.n)
d = 2

data, cluster_designation = DataGen.generate_data(n, d, k)
# data = DataGen.generate_circles(n, k)

# clusters = KMeans(n_clusters=k).fit(data)
# print(clusters.labels_)

clusters = kmeans_pp.process_pp(data, k, n, d)
print(clusters)

# generate weight matrix from observations
weights = GraphGen.get_weight_matrix(n, data)
# create diagonal matrix based on weight matrix
diagonal = GraphGen.get_diagonal_degree_matrix(n, weights)
# calculate the graph laplacian
laplacian = GraphGen.get_laplacian_matrix(n, diagonal, weights)

# ret = foury.calc_eigen_values_vectors(laplacian.tolist(), n)
# e_vectors = np.array(ret[1])
# e_values_diag = np.array(ret[0])

# use QR iteration to find eigen values/vectors
e_vectors, e_values_diag = qr_iter(laplacian, n)

# with np.printoptions(precision=3, suppress=True):
#   print(e_values_diag)

# place eigen values in a diagonal matrix
e_values = np.diagonal(e_values_diag)
# calculate k based on the eigen gaps, and select the first k eigen vectors
k, vectors = eigen_gap_heuristic(e_vectors, e_values, n)

# clusters = KMeans(n_clusters=k).fit(vectors.tolist())

# calculate clusters directly on data using k-means
labels_k_means = np.array(kmeans_pp.process_pp(data, k, n, d))
# calculate clusters using k-means on the eigen vectors
labels_spectral = np.array(kmeans_pp.process_pp(vectors, k, n, k))
jaccard_k_means = calculate_jaccard(cluster_designation, labels_k_means)
jaccard_spectral = calculate_jaccard(cluster_designation, labels_spectral)

data_txt(data, labels_spectral)
cluster_txt(data, labels_k_means, labels_spectral)
visualization_output(data, labels_spectral, labels_k_means, k, d, jaccard_spectral, jaccard_k_means)

