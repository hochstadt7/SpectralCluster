from matplotlib.backends.backend_pdf import PdfPages
import matplotlib.pyplot as plt
import numpy as np
import random


def random_color():
    return random.random(), random.random(), random.random()


# dimension is either 2 or 3
def visualization_output(data, labels_spectral, labels_k_means, k, real_k, dimension, jaccard_spectral, jaccard_kmeans):
    colors = [[random_color()] for c in range(k)]
    with PdfPages('clusters.pdf') as pdf:
        fig = plt.figure()
        if dimension == 2:
            ax = fig.add_subplot(2, 2, 1)
            for i in range(k):
                points = np.array([data[j] for j in range(len(data)) if labels_spectral[j] == i])
                ax.scatter(points[:, 0], points[:, 1], s=7, c=colors[i % len(colors)])
            ax.set_title('Normal Spectral Clustering')
            ax = fig.add_subplot(2, 2, 2)
            for i in range(k):
                points = np.array([data[j] for j in range(len(data)) if labels_k_means[j] == i])
                ax.scatter(points[:, 0], points[:, 1], s=7, c=colors[i % len(colors)])
            ax.set_title('K-means')
        else:
            ax = fig.add_subplot(2, 2, 1, projection='3d')
            for i in range(k):
                points = np.array([data[j] for j in range(len(data)) if labels_spectral[j] == i])
                ax.scatter(points[:, 0], points[:, 1], points[:, 2], s=7, c=colors[i % len(colors)])
            ax.set_title('Normal Spectral Clustering')
            ax = fig.add_subplot(2, 2, 2, projection='3d')
            for i in range(k):
                points = np.array([data[j] for j in range(len(data)) if labels_k_means[j] == i])
                ax.scatter(points[:, 0], points[:, 1], points[:, 2], s=7, c=colors[i % len(colors)])
            ax.set_title('K-means')

        plt.figtext(0.5, 0.01,
                    "Data was generated from the values:\n" +
                    "n=" + str(len(data)) + ", k=" + str(real_k) + "\n" +
                    "The k that used for both algorithms was " + str(k) + "\n" +
                    "The Jaccard measure for Spectral Clustering: " + str(round(jaccard_spectral, 2)) + "\n" +
                    "The Jaccard measure for K-means: " + str(round(jaccard_kmeans, 2))
                    , ha="center", fontsize=10,
                    bbox={"facecolor": "orange", "alpha": 0.5, "pad": 5})
        pdf.savefig()
