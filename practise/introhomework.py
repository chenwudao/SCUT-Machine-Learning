import numpy as np
import matplotlib.pyplot as plt
from scipy import stats
plt.rcParams["font.family"] = "SimHei"  

# 实验数据
t = np.array([23.3, 32.0, 41.0, 53.0, 62.0, 71.0, 87.0, 99.0])  # 温度 (°C)
l = np.array([71.0, 73.0, 75.0, 78.0, 80.0, 82.0, 86.0, 89.1])  # 长度 (cm)

# 线性回归计算斜率和截距
slope, intercept, r_value, _, _ = stats.linregress(t, l)

# 计算结果
l0 = intercept
alpha = slope / intercept

# 输出结果
print(f"斜率 k = {slope:.4f} cm/°C")
print(f"截距 l₀ = {l0:.2f} cm")
print(f"线胀系数 α = {alpha:.6f} °C⁻¹")
print(f"相关系数 r = {r_value:.4f}")

# 绘制图形
plt.figure(figsize=(8, 5))
plt.scatter(t, l, label='实验数据', color='blue', marker='o')
plt.plot(t, slope * t + intercept, color='red', label=f'拟合直线: $l = {slope:.3f}t + {intercept:.2f}$')
plt.xlabel('温度 $t$ (°C)', fontsize=12)
plt.ylabel('长度 $l$ (cm)', fontsize=12)
plt.title('金属丝长度随温度变化关系', fontsize=14)
plt.legend()
plt.grid(True, linestyle='--', alpha=0.6)
plt.show()