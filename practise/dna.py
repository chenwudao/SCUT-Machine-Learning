import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier

# 示例DNA序列数据（需替换为实际数据）
known_sequences = [
    "tgacctcttgtcctgtatagcaacctatttggtaatgattccagcactcacagaaaagct",
    "tgcacacatacacacacaccccacccctccccactaacaaatgcaagttggtaaacaaat",
    "tccaaaaaggcataacaaaccttatatatatagacaaatatatattaaagttttttagtc",
    "tgtactagaaagagcttcagacagaactgaccaccattccattgctcatcaatttcctgg",
    "gacagcacctgagcgtgcgcttacgcgcgtacacacacatagacacgcactgcgatacaa",
    "gtcctgatttgggagtccgtccttttaaaaacagccacatgctttcacgctctgagaccc",
    "acccgtttctgtgagcagggggagggcaaggaaagccctggcctcagtccagccttttct",
    "ctgcttccacctgctcaggctgtgtgctcttggttctgtcctgcacttgtgtgaattcca",
    "aaactgtttttttaaaaaatggcccgcaccccaaatgtctccctgccccatactttgcaa",
    "caagagaaaactttaggatgcttctcttttgggtggcggaggttgttaacttcaagaatt",
    "tagaagaatcattgctccgacaaatccactgtctcctgagttttctttattcatgttaac",
    "aaggcaagagtcagagaaaagggagacttggtctgcttcccacatgcagctgagcggagg",
    "ggccgtcacagcacagggtcacctgcagagctgaagccgctcctcaggctccccctccaa",
    "gagggctggggcaaggtccctgggctgaggcctcccaggggggcctgggcaaggcttcct",
    "tgggttctggatcccccctgcaatgctgccccatcctgcccccacccccacgtcattaaa",
    "cacgatggagggtttttcggtcggttggttggttggtgttctaaatcaaggaaaatggtc",
    "cgactggaccccttgtctctctctacagactgcttcacggactctttgctgttgacga",
    "tctcctggtagcatgaccttttggcctttgttaagacacacagcctttctgtatcaagcc",
    "ccctgtctaacctacgacccagagtgactgacggctgtgta",
    "ctggctctctccataggcttttctgagaggaggaactatggcttagctgaggttagttct",
]
labels = ['A'] * 10 + ['B'] * 10  # 已知标签

# 待分类序列21-40
unknown_sequences = [
    "cagtatatgagtggccctgaataaagcctttctttccccaaacggctctaatgtcctgct",
    "aatccagaaatcatcagtgcatggttactatgtgaaagcataatagcttgtggcctgcag",
    "agacaagaggaaggttaacaagtaggggtcctttggtttgagatcttggagcaaattaag",
    "gaagagccactaaagttaatggaattacactggatcctgtgacagacacttcatgcttca",
    "tgggtcacatggtctgtttctgctcctctctgccctggttggtgtgggttttggtgttag",
    "aactctccggtgggagatctgggactgggatattgtgttggaggacagatttgcttcaat",
    "atcttttaagtgtaaatcttctcctctttctcccaggacactctggccttcagccaacag",
    "gtaataccttttaatcctctttaggacacagattcagtttctccagtgagaggtgaagcc",
    "agctggacttctgggttgggtggggacttggagaacttttctgtcttacaagaggtttct",
    "aaatgcaccaatgagtgctctgtaaaaacacaccaatgagtgctctgtaaaaattgacac",
    "tctgtggctcgctagatgtttgtaagatggaccaatcagcactctgtaaaatggaccaat",
    "ccacactctgtaaaatggaccaatcagcactctttaaaatggaccaatcagcaggatacg",
    "ggcggagacaaataagggaataaaagctggtcaccctagccagcacctgcaacctgctta",
    "ggtccttttctatgctgtggaaggtctgttctttcactcttcacaataaatcttgtgctc",
    "actctttggggccgtgccacctttaagagctataacactcactgcaagggtctgtggctt",
    "cactcttgaagtcagccagaccctgaacctaccggaaggaacaaactcaggacacactag",
    "aatgatggtagaggtgataaggcatgagacagaaataataggaaagactttggatccaaa",
    "tttctgatcaggcaatttacaccaaaactcctcctctccacttagaaaaggcctgtgctc",
    "tgcaggactattggctctgggagactcaggaacttgtttttcttcttcctgcagtgttct",
    "catctgagtccttcaaagagggggaaagaaacgttagtagacccaggttgaaaacaacac",
]

# 提取碱基频率特征
def extract_features(sequences):
    features = []
    for seq in sequences:
        total = len(seq)
        a = seq.count('a') / total
        t = seq.count('t') / total
        c = seq.count('c') / total
        g = seq.count('g') / total
        features.append([a, t, c, g])
    return np.array(features)

# 提取已知和未知序列特征
X_train = extract_features(known_sequences)
y_train = labels
X_test = extract_features(unknown_sequences)

# 训练KNN分类器
clf = KNeighborsClassifier(n_neighbors=3)
clf.fit(X_train, y_train)

# 预测并输出结果
predictions = clf.predict(X_test)
for i, pred in enumerate(predictions):
    print(f"序列{i+21}的类别为：{pred}")