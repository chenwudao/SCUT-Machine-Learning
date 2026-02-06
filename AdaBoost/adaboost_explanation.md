# AdaBoost 实现说明

本文档说明 `AdaBoost_blank.ipynb` 中实现 AdaBoost 元算法的思路、关键步骤与代码对应关系，便于理解与评估。

## 简明契约
- 输入：特征矩阵 X (N×p)，标签向量 y，标签取值为 {-1, +1}；迭代次数 M（弱分类器个数）。
- 输出：训练好的弱分类器集合 G_1...G_M、对应权重 alpha_1...alpha_M；对新样本给出预测 y_hat ∈ {-1, +1}。
- 失败模式：当某次弱分类器错误率精确为 0 或 1 时会导致 alpha 无穷或 -∞；代码中对 error 做了数值裁剪以避免除零/对数错误。

## 关键思想（对应作业图片）
按《The Elements of Statistical Learning》中第 10.1 节：
1. 初始化观测权重 w_i = 1/N。
2. 对 m = 1..M：
   a. 用当前权重 w_i 训练一个弱分类器 G_m（此处用决策树桩 DecisionTreeClassifier(max_depth=1)）。
   b. 计算加权错误率：
      err_m = \frac{\sum_i w_i I(y_i \ne G_m(x_i))}{\sum_i w_i}。
   c. 计算分类器权重：
      alpha_m = log((1 - err_m) / err_m)。为了数值稳定性在实现中对 err_m 做了裁剪。
   d. 更新观测权重：
      w_i <- w_i * exp(alpha_m * I(y_i \ne G_m(x_i)))，并归一化使和为 1。
3. 最终元分类器： G(x) = sign(\sum_{m=1}^M alpha_m G_m(x))。

## 代码对应位置
- `compute_error(y, y_pred, w_i)`：实现了步骤 2b 的加权错误率计算，返回 error。
  - 代码要点：使用 `np.not_equal` 生成 0/1 掩码，计算加权和并除以权重和。

- `compute_alpha(error)`：实现步骤 2c，返回 alpha。为避免 log(0) 或除以 0，先用 eps(=1e-10) 对 error 做裁剪。

- `update_weights(w_i, alpha, y, y_pred)`：实现步骤 2d，按公式 w_i * exp(alpha * I(misclassified))，随后将权重除以其和以归一化。

- `AdaBoost.fit(self, X, y, M)`：主循环实现
  - m==0 时初始化 w_i = 1/N。
  - 否则在每个迭代开始时使用上一次训练的弱分类器与上一次的 alpha 来更新权重（代码中通过 `self.G_M[-1].predict(X)` 和 `self.alphas[-1]` 获得）。
  - 使用 `DecisionTreeClassifier(max_depth=1)`，并把 `sample_weight=w_i` 传入 `fit`。
  - 使用 `compute_error` 计算当前弱分类器的错误率，使用 `compute_alpha` 得到 alpha，并把它们保存到 `self.training_errors` / `self.alphas`。

- `AdaBoost.predict(self, X)`：
  - 收集每个弱分类器的预测（DataFrame `weak_preds`），然后计算每个样本的加权和：weighted = dot(weak_preds, alphas)。
  - 最终预测为 sign(weighted)，若某个样本加权和为 0，则将其映射为 +1（实现上选择 +1 作为默认值）。

## 实现细节与工程考虑
- 标签约定：代码中把原始数据集中 0/1 的 Spam 列转换成 {-1, +1}（`df['Spam'] = df['Spam'] * 2 - 1`），与 AdaBoost 的符号形式一致。
- 数值稳定性：`compute_alpha` 中对 `error` 做裁剪（eps = 1e-10），避免 log(0) 或除零导致的 NaN/Inf。
- 权重归一化：`update_weights` 在返回之前把权重除以它们的总和，保证下一轮训练时权重和为 1（也使 compute_error 分母稳定）。
- 决策树桩的 `sample_weight` 参数：sklearn 的 `DecisionTreeClassifier.fit` 支持 `sample_weight`，因此可直接传入权重向量来按权训练。

## 可能的边界/改进点
- 若某一弱分类器的 error 非常接近 0，会使 alpha 非常大，从而导致后面迭代权重极端；可以在 alpha 计算上做更强的裁剪或在训练策略上早停。
- 当前实现每次在循环开头使用上一次 G_{m-1} 和 alpha_{m-1} 更新权重（与书中在获得 alpha 后立即更新等价，只是实现位置不同）；两者在逻辑上等价。
- 可扩展为概率输出（例如对加权和做 sigmoid）以便直接计算 AUC 曲线或概率估计。

## 如何运行
在包含 `AdaBoost_blank.ipynb`、`spambase.data` 与 `spambase.names` 的文件夹中打开 Jupyter Notebook（或 VS Code 的 Notebook 界面），运行所有单元。主要单元：
- 数据读取与预处理（已在 notebook 中），将标签转换为 {-1,+1}。
- 创建 `ab = AdaBoost()` 并调用 `ab.fit(X_train, y_train, M=400)`。
- 使用 `y_pred = ab.predict(X_test)`，随后用 `roc_auc_score(y_test, y_pred)` 等指标评估。

## 结语
已在 `AdaBoost_blank.ipynb` 中实现关键函数与类方法，保持了代码结构与原始作业框架的一致性。若需要，我可以：
- 运行 notebook 单元以做语法/运行时验证（需要在当前环境启动 Python 并安装依赖），
- 增加单元测试来覆盖核心函数（happy-path + 边界），
- 将预测输出从 {-1,+1} 转换为概率估计并绘制 ROC 曲线。

---
文件：`adaboost_explanation.md` 已创建于本目录。祝你作业顺利！
