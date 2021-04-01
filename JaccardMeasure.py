import numpy as np


def calculate_jaccard(truth, clusters):
    # truth = np.array([0, 0, 1, 1, 1, 2, 1])
    # clusters = np.array([0, 0, 0, 1, 1, 2, 1])
    truth_pairs = np.equal(truth[:, None] - truth[None, :], 0)
    truth_pairs_count = np.sum(truth_pairs) - len(truth)
    clusters_pairs = np.equal(clusters[:, None] - clusters[None, :], 0)
    common_pairs = np.logical_and(truth_pairs, clusters_pairs)
    common_pairs_count = np.sum(common_pairs) - len(truth)
    jaccard = common_pairs_count / truth_pairs_count
    return jaccard
