import numpy as np
import matplotlib.pyplot as plt

randomized_quick_path = "./output/meta.csv"
quick_path = "../practical-4/output/meta.csv"

title = "When sorted on average temperature"

# Lists to store numeric data
comparisons_quick = []
assignments_quick = []
comparisons_random = []
assignments_random = []

# Read CSV
with open(quick_path, "r", encoding="utf-8") as f:
    for line in f:
        line = line.strip()
        if not line:
            continue
        a, b = line.split(",")
        comparisons_quick.append(float(a))
        assignments_quick.append(float(b))

with open(randomized_quick_path, "r", encoding="utf-8") as f:
    for line in f:
        line = line.strip()
        if not line:
            continue
        a, b = line.split(",")
        comparisons_random.append(float(a))
        assignments_random.append(float(b))

# Convert to numpy arrays
y1 = np.array(comparisons_quick)
y2 = np.array(assignments_quick)

y3 = np.array(comparisons_random)
y4 = np.array(assignments_random)

x_quick = np.arange(len(y1))
x_random = np.arange(len(y3))

degree_quick = 1
degree_random = 2

# Fit polynomials
poly1 = np.poly1d(np.polyfit(x_quick, y1, degree_quick))
poly2 = np.poly1d(np.polyfit(x_quick, y2, degree_quick))
poly3 = np.poly1d(np.polyfit(x_random, y3, degree_random))
poly4 = np.poly1d(np.polyfit(x_random, y4, degree_random))

# Evaluate polynomials
fit1 = poly1(x_quick)
fit2 = poly2(x_quick)
fit3 = poly3(x_random)
fit4 = poly4(x_random)

# Plot
plt.scatter(x_quick, y1, label="Comparisons (Quick Sort)", color="blue")
plt.plot(x_quick, fit1, color="blue", linestyle="--")

plt.scatter(x_random, y3, label="Comparisons (Randomized Quick Sort)", color="red")
plt.plot(x_random, fit3, color="red", linestyle="--")

plt.scatter(x_quick, y2, label="Assignments (Quick Sort)", color="magenta")
plt.plot(x_quick, fit2, color="magenta", linestyle="--")

plt.scatter(x_random, y4, label="Assignments (Randomized Quick Sort)", color="green")
plt.plot(x_random, fit4, color="green", linestyle="--")


plt.xlabel("n/10")
plt.ylabel("Absolute number")
plt.title(title)
plt.legend()
plt.tight_layout()
plt.savefig("plots/comparison_with_quick.png")
