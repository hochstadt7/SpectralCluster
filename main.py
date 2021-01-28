import DataGen
import GraphGen
from sklearn.datasets import make_blobs
import argparse
parser = argparse.ArgumentParser()
parser.add_argument("k", type=int)
parser.add_argument("n", type=int)
parser.add_argument("Random", type=bool)
args = parser.parse_args()
k = int(args.k)
n = int(args.n)

d = 2
data = DataGen.generate_data(n, d, k)
weights = GraphGen.get_weight_matrix(n, data)
print(weights)
diagonal = GraphGen.get_diagonal_degree_matrix(n, weights)
print(diagonal)
laplacian = GraphGen.get_laplacian_matrix(n, diagonal, weights)
print(laplacian)
