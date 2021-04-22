import numpy as np

# jaccard measure
def calculate_jaccard(truth, clusters):
    # truth = np.array([0, 0, 1, 1, 1, 2, 1])
    # clusters = np.array([0, 0, 0, 1, 1, 2, 1])
    truth_pairs = np.equal(truth[:, None] - truth[None, :], 0)
    clusters_pairs = np.equal(clusters[:, None] - clusters[None, :], 0)
    common_pairs = np.logical_and(truth_pairs, clusters_pairs)
    common_pairs_count = np.sum(common_pairs) - len(truth)
    any_pairs = np.logical_or(truth_pairs, clusters_pairs)
    any_pairs_count = np.sum(any_pairs) - len(truth)
    jaccard = common_pairs_count / any_pairs_count
    return jaccard
