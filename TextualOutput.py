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

# x,y are the parameters returned from make_blobs(), dimension is either 2 or 3
def visualziation_output(X,y,dimension,jaccard):

    with PdfPages('clusters.pdf') as pdf:
        fig=plt.figure()
        if dimension==2:
            ax=fig.add_subplot(2,2,1)
            ax.scatter(X[:,0],X[:,1],c=y)
            ax.set_title('Normal Spectral Clustering')
            ax = fig.add_subplot(2, 2, 2)
            ax.scatter(X[:,0],X[:,1],c=y)
            ax.set_title('K-means')
        else:
            ax=fig.add_subplot(2,2,1,projection='3d')
            ax.scatter(X[:,0],X[:,1],X[:,2],c=y)
            ax.set_title('Normal Spectral Clustering')
            ax = fig.add_subplot(2, 2, 2,projection='3d')
            ax.scatter(X[:,0],X[:,1],X[:,2],c=y)
            ax.set_title('K-means')
        plt.figtext(0.5, 0.01, "Data was generated from the values:\nn="+str(len(X))+", k="+str(dimension)+"\nThe k that used for both algoritms was "+str(dimension)+"\nThe jaccard measure for Spectral Clustering: "+str(jaccard)+"\n The jaccard measure for K-means: "+str(jaccard), ha="center", fontsize=10, bbox={"facecolor":"orange", "alpha":0.5, "pad":5})
        pdf.savefig()