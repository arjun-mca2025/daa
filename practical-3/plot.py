import numpy as np
import matplotlib.pyplot as plt

INSERTION_FILE = "../practical-2/output/meta.csv"
MERGE_FILE = "./output/meta.csv"

import numpy as np
import matplotlib.pyplot as plt

merge_path = "./output/meta.csv"
insertion_path = "../practical-2/output/meta.csv"

title = "When sorted on average temperature"

# Lists to store numeric data
comparisons_merge = []
assignments_merge = []
comparisons_insertion = []
assignments_insertion = []

# Read CSV
with open(merge_path, "r", encoding="utf-8") as f:
    for line in f:
        line = line.strip()
        if not line:
            continue
        a, b = line.split(",")
        comparisons_merge.append(float(a))
        assignments_merge.append(float(b))
        
with open(insertion_path, "r", encoding="utf-8") as f:
    for line in f:
        line = line.strip()
        if not line:
            continue
        a, b = line.split(",")
        comparisons_insertion.append(float(a))
        assignments_insertion.append(float(b))

# Convert to numpy arrays
y1 = np.array(comparisons_merge)
y2 = np.array(assignments_merge)

y3 = np.array(comparisons_insertion)
y4 = np.array(assignments_insertion)

x_merge = np.arange(len(y1))
x_insertion = np.arange(len(y3))

degree_merge = 1
degree_insertion = 2

# Fit polynomials
poly1 = np.poly1d(np.polyfit(x_merge, y1, degree_merge))
poly2 = np.poly1d(np.polyfit(x_merge, y2, degree_merge))
poly3 = np.poly1d(np.polyfit(x_insertion, y3, degree_insertion))
poly4 = np.poly1d(np.polyfit(x_insertion, y4, degree_insertion))

# Evaluate polynomials
fit1 = poly1(x_merge)
fit2 = poly2(x_merge)
fit3 = poly3(x_insertion)
fit4 = poly4(x_insertion)

# Plot
plt.scatter(x_merge, y1, label="Comparisons (Merge Sort)", color="blue")
plt.plot(x_merge, fit1, color="blue", linestyle="--")

plt.scatter(x_merge, y2, label="Assignments (Merge Sort)", color="red")
plt.plot(x_merge, fit2, color="red", linestyle="--")

plt.scatter(x_insertion, y3, label="Comparisons (Insertion Sort)", color="black")
plt.plot(x_insertion, fit3, color="black", linestyle="--")

plt.scatter(x_insertion, y4, label="Assignments (Insertion Sort)", color="green")
plt.plot(x_insertion, fit4, color="green", linestyle="--")


plt.xlabel("n/10")
plt.ylabel("Absolute number")
plt.title(title)
plt.legend()
plt.tight_layout()
plt.savefig("plots/insertion_merge_comparison_on_weather_data.png")