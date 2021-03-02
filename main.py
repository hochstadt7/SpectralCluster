import DataGen
import GraphGen
from sklearn.cluster import KMeans
import argparse

from GramSchmidt import *
from KMeans import *
from Qr import *
from EigenGapSelection import *
from matplotlib import pyplot as plt


parser = argparse.ArgumentParser()
parser.add_argument("k", type=int)
parser.add_argument("n", type=int)
parser.add_argument("Random", type=bool)
args = parser.parse_args()
k = int(args.k)
n = int(args.n)

d = 2

data = DataGen.generate_data(n, d, k)


clusters = KMeans(n_clusters=k).fit(data)
print(clusters.labels_)
colors = ['r', 'g', 'b', 'y', 'c', 'm']
fig, ax = plt.subplots()
for i in range(k):
    points = np.array([data[j] for j in range(len(data)) if clusters.labels_[j] == i])
    ax.scatter(points[:, 0], points[:, 1], s=7, c=colors[i])
plt.savefig('line_plot2.pdf')


weights = GraphGen.get_weight_matrix(n, data)
diagonal = GraphGen.get_diagonal_degree_matrix(n, weights)
laplacian = GraphGen.get_laplacian_matrix(n, diagonal, weights)
e_vectors, e_values_diag = qr_iter(laplacian, n)
e_values = np.diagonal(e_values_diag)
# e_values, e_vectors = np.linalg.eig(laplacian)
k, vectors = eigen_gap_heuristic(e_vectors, e_values, n)
clusters = KMeans(n_clusters=k).fit(vectors.tolist())
print(clusters.labels_)
colors = ['r', 'g', 'b', 'y', 'c', 'm']
fig, ax = plt.subplots()
for i in range(k):
    points = np.array([data[j] for j in range(len(data)) if clusters.labels_[j] == i])
    ax.scatter(points[:, 0], points[:, 1], s=7, c=colors[i])
plt.savefig('line_plot.pdf')

