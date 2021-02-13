from sklearn.datasets import make_blobs

if __name__ == '__main__':

    x, y = make_blobs(n_samples=10, centers=3, n_features=2,random_state=0)