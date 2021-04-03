from matplotlib.backends.backend_pdf import PdfPages
import matplotlib.pyplot as plt
import numpy as np


def data_txt(data, labels):
    f = open("data.txt", "w")
    n, d = data.shape
    for i in range(n):
        f.write(",".join([str(data[i][j]) for j in range(d)]) + "," + str(labels[i]) + "\n")
    f.close()


def cluster_txt(data, labels_normalized, labels_k_means, k):
    f = open("clusters.txt", "w")
    f.write(str(k) + '\n')
    for i in range(k):
        f.write(",".join([str(j) for j in range(len(data)) if labels_normalized[j] == i]) + "\n")
    for i in range(k):
        f.write(",".join([str(j) for j in range(len(data)) if labels_k_means[j] == i]) + "\n")
    f.close()

