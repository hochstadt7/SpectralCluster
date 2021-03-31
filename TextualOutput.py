from matplotlib.backends.backend_pdf import PdfPages
import matplotlib.pyplot as plt
import numpy as np

def data_txt(data,labels):

    f=open("data.txt","w")
    n, d = data.shape
    for i in range(n):
        f.write(",".join([str(data[i][j]) for j in range(d)])+","+str(labels[i])+"\n")
    f.close()

def cluster_txt(data,labels_nornalized,labels_k_means):

    f=open("clusters.txt","w")
    num_of_clusters=len(data)# number of clusters
    f.write(str(num_of_clusters)+'\n')
    for i in range(num_of_clusters):
        f.write(",".join([str(labels_nornalized[j]) for j in range(num_of_clusters) if labels_nornalized[j]==i])+"\n")
    for i in range(num_of_clusters):
        f.write(",".join([str(labels_k_means[j]) for j in range(num_of_clusters) if labels_k_means[j]==i])+"\n")
    f.close()

# dimension is either 2 or 3
def visualziation_output(data,labels_nornalized,labels_k_means,k,dimension,jaccard):
    colors = ['r', 'g', 'b', 'y', 'c', 'm', 'r', 'g', 'b', 'y', 'c', 'm']
    with PdfPages('clusters.pdf') as pdf:
        fig=plt.figure()
        if dimension==2:
            ax=fig.add_subplot(2,2,1)
            for i in range(k):
                points = np.array([data[j] for j in range(len(data)) if labels_nornalized[j] == i])
                ax.scatter(points[:, 0], points[:, 1], s=7, c=colors[i])
            ax.set_title('Normal Spectral Clustering')
            ax = fig.add_subplot(2, 2, 2)
            for i in range(k):
                points = np.array([data[j] for j in range(len(data)) if labels_k_means[j] == i])
                ax.scatter(points[:, 0], points[:, 1], s=7, c=colors[i])
            ax.set_title('K-means')
        else:
            ax=fig.add_subplot(2,2,1,projection='3d')
            for i in range(k):
                points = np.array([data[j] for j in range(len(data)) if labels_nornalized[j] == i])
                ax.scatter(points[:, 0], points[:, 1], points[:,2], s=7, c=colors[i])
            ax.set_title('Normal Spectral Clustering')
            ax = fig.add_subplot(2, 2, 2,projection='3d')
            for i in range(k):
                points = np.array([data[j] for j in range(len(data)) if labels_k_means[j] == i])
                ax.scatter(points[:, 0], points[:, 1], points[:,2], s=7, c=colors[i])
            ax.set_title('K-means')

        plt.figtext(0.5, 0.01, "Data was generated from the values:\nn="+str(len(data))+", k="+str(k)+"\nThe k that used for both algoritms was "+str(dimension)+"\nThe jaccard measure for Spectral Clustering: "+str(jaccard)+"\n The jaccard measure for K-means: "+str(jaccard), ha="center", fontsize=10, bbox={"facecolor":"orange", "alpha":0.5, "pad":5})
        pdf.savefig()