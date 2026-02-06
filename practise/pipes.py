import pulp

# Define the problem
problem = pulp.LpProblem("Steel_Pipe_Cutting", pulp.LpMinimize)

# Define the decision variables
# x_i represents the number of pipes cut using pattern i
x1 = pulp.LpVariable('x1', lowBound=0, cat='Integer')
x2 = pulp.LpVariable('x2', lowBound=0, cat='Integer')
x3 = pulp.LpVariable('x3', lowBound=0, cat='Integer')
x4 = pulp.LpVariable('x4', lowBound=0, cat='Integer')
x5 = pulp.LpVariable('x5', lowBound=0, cat='Integer')
x6 = pulp.LpVariable('x6', lowBound=0, cat='Integer')
x7 = pulp.LpVariable('x7', lowBound=0, cat='Integer')

# Define the objective function: minimize the total leftover material
problem += 3 * x1 + 1 * x2 + 2 * x3 + 3 * x4 + 6 * x5 + 1 * x6 + 3 * x7, "Total Leftover Material"

# Define the constraints
# 4m pipe requirement: 4x1 + 3x2 + 3x3 + 2x4 + x5 >= 50
problem += 4 * x1 + 3 * x2 + 3 * x3 + 2 * x4 + x5 >= 50, "4m Pipe Constraint"

# 6m pipe requirement: x2 + 3x6 >= 20
problem += x2 + 3 * x6 >= 20, "6m Pipe Constraint"

# 8m pipe requirement: x3 + 2x7 >= 15
problem += x3 + 2 * x7 >= 15, "8m Pipe Constraint"

# Solve the problem
problem.solve()

# Print the results
print("Status:", pulp.LpStatus[problem.status])
print("Optimal Solution:")
print(f"x1 (Pattern 1): {x1.varValue}")
print(f"x2 (Pattern 2): {x2.varValue}")
print(f"x3 (Pattern 3): {x3.varValue}")
print(f"x4 (Pattern 4): {x4.varValue}")
print(f"x5 (Pattern 5): {x5.varValue}")
print(f"x6 (Pattern 6): {x6.varValue}")
print(f"x7 (Pattern 7): {x7.varValue}")
print(f"Total Leftover Material: {pulp.value(problem.objective)}")