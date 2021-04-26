# generate data.txt
def data_txt(data, labels):
    f = open("data.txt", "w")
    n, d = data.shape
    for i in range(n):
        f.write(",".join([str(data[i][j]) for j in range(d)]) + "," + str(labels[i]) + "\n")
    f.close()


# generate clusters.txt
def cluster_txt(data, labels_normalized, labels_k_means, k):
    f = open("clusters.txt", "w")
    f.write(str(k) + '\n')
    lst = [[] for _ in range(k)]
    for i in range(len(data)):
        lst[labels_normalized[i]].append(i)
    for i in range(k):
        f.write(",".join([str(j) for j in lst[i]]) + "\n")
    lst = []
    for i in range(k):
        lst.append([])
    for i in range(len(data)):
        lst[labels_k_means[i]].append(i)
    for i in range(k):
        f.write(",".join([str(j) for j in lst[i]]) + "\n")
    f.close()
