from pulp import *

# 示例数据
foods = ['F1', 'F2', 'F3']  # 食物名称
costs = {'F1': 10, 'F2': 20, 'F3': 15}  # 各种食物的成本
kcal = {'F1': 500, 'F2': 300, 'F3': 400}  # 各种食物的热量
protein = {'F1': 10, 'F2': 15, 'F3': 20}  # 各种食物的蛋白质
calcium = {'F1': 50, 'F2': 80, 'F3': 60}  # 各种食物的钙含量
max_portion = {'F1': 3, 'F2': 2, 'F3': 4}  # 各种食物的最大份数

# 创建问题实例
prob = LpProblem("Diet Problem", LpMinimize)

# 定义变量
x = LpVariable.dicts("Food", foods, lowBound=0, cat='Integer')  # 整数变量

# 定义目标函数
prob += lpSum([costs[i] * x[i] for i in foods])

# 定义约束条件
prob += lpSum([kcal[i] * x[i] for i in foods]) >= 2000  # 热量约束
prob += lpSum([protein[i] * x[i] for i in foods]) >= 55  # 蛋白质约束
prob += lpSum([calcium[i] * x[i] for i in foods]) >= 800  # 钙约束

# 最大份数约束
for i in foods:
    prob += x[i] <= max_portion[i]

# 求解问题
prob.solve()

# 打印结果
print("最低成本：", value(prob.objective))

# 打印各个食物的份数
for food in foods:
    print(f"{food}: {x[food].varValue}")