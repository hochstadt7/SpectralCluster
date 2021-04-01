from matplotlib.backends.backend_pdf import PdfPages
import matplotlib.pyplot as plt
import numpy as np


def data_txt(data, labels):
    f = open("data.txt", "w")
    n, d = data.shape
    for i in range(n):
        f.write(",".join([str(data[i][j]) for j in range(d)]) + "," + str(labels[i]) + "\n")
    f.close()


def cluster_txt(data, labels_normalized, labels_k_means):
    f = open("clusters.txt", "w")
    num_of_clusters = len(data)  # number of clusters
    f.write(str(num_of_clusters) + '\n')
    for i in range(num_of_clusters):
        f.write(
            ",".join([str(labels_normalized[j]) for j in range(num_of_clusters) if labels_normalized[j] == i]) + "\n")
    for i in range(num_of_clusters):
        f.write(",".join([str(labels_k_means[j]) for j in range(num_of_clusters) if labels_k_means[j] == i]) + "\n")
    f.close()

