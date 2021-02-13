from matplotlib.backends.backend_pdf import PdfPages
import matplotlib.pyplot as plt

# X-data points y- labels for cluster membership of each sample
def data_txt(X,y):

    f=open("data.txt","w")
    n, d = X.shape
    for i in range(n):
        f.write(",".join([str(X[i][j]) for j in range(d)])+","+str(y[i])+"\n")
    f.close()

# normalized_cluster and k_means_cluster hold the indices of the points in each cluster
def cluster_txt(normalized_cluster,k_means_cluster):

    f=open("clusters.txt","w")
    num_of_clusters=len(k_means_cluster)# number of clusters
    f.write(str(num_of_clusters))
    for i in range(num_of_clusters):
        f.write(",".join([str(normalized_cluster[j]) for j in range(num_of_clusters)])+"\n")
    for i in range(num_of_clusters):
        f.write(",".join([str(k_means_cluster[j]) for j in range(num_of_clusters)])+"\n")
    f.close()

# x,y are the parameters returned from make_blobs()
def visualziation_output(x,y):

    with PdfPages('clusters.pdf') as pdf:

        fig, (ax1, ax2) = plt.subplots(1, 2)
        ax1.plot(x, y)
        ax1.set_title('Normalized Spectral Clustering')
        ax2.plot(x, -y)
        ax2.set_title('K-means')
        plt.figtext(0.5, 0.01, "Data was generated from the values:\nn={}, k={}\nThe k that used for both algoritms was {}\nThe jaccard measure for Spectral Clustering: {}\n The jaccard measure for K-means: {}", ha="center", fontsize=10, bbox={"facecolor":"orange", "alpha":0.5, "pad":5})
        pdf.savefig()