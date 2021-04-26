import DataGen
import GraphGen
import kmeans_pp
import argparse
from TextualOutput import *
from JaccardMeasure import *
from VisualizeResults import *
from EigenGapSelection import *
import numpy as np
import section_four as qr_c

print("Welcome!\n")

MAX_CAPACITY = {
    2: {"n": 380, "k": 20, "d": "2d"},
    3: {"n": 345, "k": 20, "d": "3d"}
}

for capacity in MAX_CAPACITY.values():
    print("In " + str(capacity["d"]) + " mode, the program can handle up to n="+str(capacity["n"])+" points," +
          " and up to k=" + str(capacity["k"]) + " clusters\n")

d = np.random.choice(2, 1)[0] + 2
print(str(d)+"d Mode\n")

parser = argparse.ArgumentParser()
parser.add_argument("k", type=int)
parser.add_argument("n", type=int)
parser.add_argument("Random", type=int)
args = parser.parse_args()
random = args.Random

# if in Random mode, generate random N and K values
if random:
    print("Random = True\n")
    n = np.random.choice(round(MAX_CAPACITY[d]["n"] / 2), 1)[0] + round(MAX_CAPACITY[d]["n"] / 2)
    real_k = min(np.random.choice(round(MAX_CAPACITY[d]["k"] / 2), 1)[0] + round(MAX_CAPACITY[d]["k"] / 2), n)
    # real_k stores the K value used to generate the clusters
    # k is initialized to real_k, but may later store the k value calculated via the eigen gap heuristic
    k = real_k
# otherwise, use the supplied N, K arguments
else:
    print("Random = False\n")
    n = int(args.n)
    real_k = int(args.k)
    if(real_k==0 or n==0):
        print("K and N should be positive\n")
        exit(0)
    if real_k >= n:
        print("K must be less than N\n")
        exit(0)
    k = None
print("N = "+str(n)+"\n")
print("K = "+str(real_k)+"\n")

# generate blob clusters
data, cluster_designation = DataGen.generate_data(n, d, real_k)

# generate concentric circles
# data, cluster_designation = DataGen.generate_circles(n, k, d)

# generate weight matrix from observations
weights = GraphGen.get_weight_matrix(n, data)
# create diagonal matrix based on weight matrix
diagonal = GraphGen.get_diagonal_degree_matrix(n, weights)
# calculate the graph laplacian
laplacian = GraphGen.get_laplacian_matrix(n, diagonal, weights)

# use QR iteration to find eigen values/vectors
# e_vectors, e_values_diag = qr_iter(laplacian, n)
try:
    ret = qr_c.calc_eigen_values_vectors(laplacian.tolist(), n)
except:
    exit(0)
e_vectors = np.array(ret[1])
e_values_diag = np.array(ret[0])

# place eigen values in a diagonal matrix
e_values = np.diagonal(e_values_diag)
# calculate k based on the eigen gaps, and select the first k eigen vectors
k, vectors = eigen_gap_heuristic(e_vectors, e_values, n, real_k, random)

# calculate clusters directly on data using k-means
try:
    temp=kmeans_pp.process_pp(data, k, n, d)
except:
    exit(0)
labels_k_means = np.array(temp)
# calculate clusters using k-means on the eigen vectors
try:
    temp=kmeans_pp.process_pp(vectors, k, n, k)
except:
    exit(0)
labels_spectral = np.array(temp)
# jaccard value for direct k-means algorithm

jaccard_k_means = calculate_jaccard(cluster_designation, labels_k_means)
# jaccard value for spectral clustering algorithm

jaccard_spectral = calculate_jaccard(cluster_designation, labels_spectral)
# output data as text

data_txt(data, cluster_designation)
# output clusters as text
cluster_txt(data, labels_k_means, labels_spectral, k)
# output pdf visualization
visualization_output(data, labels_spectral, labels_k_means, k, real_k, d, jaccard_spectral, jaccard_k_means)
