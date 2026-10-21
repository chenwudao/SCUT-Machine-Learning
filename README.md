# 机器学习课程资料

本仓库分享机器学习课程中的算法练习与配套材料。每个顶层目录对应一种算法或模型，内含 Jupyter Notebook，以及该练习使用的数据、参考 PDF、示意图或文字说明。

## 材料一览

下表按目录名列出仓库中已有的材料。

| 目录 | 说明 |
| --- | --- |
| [`AdaBoost`](AdaBoost) | AdaBoost 练习。弱分类器为决策树桩，数据为 Spambase（`spambase.data`、`spambase.names`）。目录中另有 `Boosting.pdf`、`AdaBoost.html`，以及中文说明 `adaboost_explanation.md` 与 `adaboost_detailed.md`。 |
| [`Decision_Tree`](Decision_Tree) | 决策树练习。数据为周志华西瓜数据集 `Watermelon.txt`，按特征判断是否为好瓜。Notebook 中包含香农熵、信息增益与手写 ID3 的实现。 |
| [`Expectation_Maximization`](Expectation_Maximization) | EM 算法练习。Notebook 中的示例数据服从两种不同的多元正态分布，并附有 `Expectation_Maximization_blank.pdf`、`info2.pdf` 与示意图。 |
| [`Kmeans`](Kmeans) | K-means 聚类。读取 `dataset.mat` 中的二维数据，Notebook 中包含聚类中心初始化等实现。 |
| [`LogisticRegression`](LogisticRegression) | 逻辑回归实验。以 `data.csv` 中的两门学科成绩（`grade1`、`grade2`）做二分类，实现模型，并观察不同初始参数、学习率与迭代次数下的代价曲线和准确率。目录中另有公式配图与 `LogisticRegression_Exp.html`。 |
| [`Navie_Bayes`](Navie_Bayes) | 朴素贝叶斯垃圾邮件分类。邮件样本位于 `email/ham` 与 `email/spam`，并附有示意图与 `Naive_Bayes_blank.html`。目录名沿用仓库中的原有拼写 `Navie_Bayes`。 |
| [`PCA`](PCA) | 主成分分析（PCA）练习，附有 `PCA.pdf` 与示意图。 |
| [`SVM`](SVM) | 支持向量机练习。Notebook 使用合页损失（hinge loss），并以随机梯度下降（SGD）更新参数，另附 `svm_info.pdf`。 |

## 使用方式

1. 从上表进入对应目录，用 Jupyter 打开其中的 `.ipynb`。请在该目录下启动，以便 Notebook 能通过相对路径找到数据、图片和 PDF。
2. 部分练习在 `start` / `end` 标记之间留空，标记写法因文件而异，例如 `###### start ######` 或 `######## start ########`。请先通读整份 Notebook，只在标记区域内填写代码。
3. 若目录中有 PDF、图片或 Markdown 说明，可与代码对照阅读。`AdaBoost`、`LogisticRegression` 与 `Navie_Bayes` 中的 HTML 可在浏览器中直接打开。

## 运行环境

请使用 Python 3。各 Notebook 会按需导入 NumPy、Pandas、Matplotlib、SciPy、scikit-learn 或 Seaborn，具体以该文件开头的 import 为准。
