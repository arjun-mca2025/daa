import numpy as np
import matplotlib.pyplot as plt

files = [
    "./output/report.txt",
    "./output/report_age_only.txt",
    "./output/report_name_only.txt",
]

titles = [
    "When sorted on age alone (Radix Sort)",
    "When sorted on name alone (Radix Sort)",
    "When sorted on age followed by name (Radix Sort)",
]

fig_names = ["age_only_radix", "name_only_radix", "both_radix"]

for i, file_path in enumerate(files):
    # Lists to store numeric data
    col1 = []
    col2 = []

    # Read CSV
    with open(file_path, "r", encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            a, b = line.split(",")
            col1.append(float(a))
            col2.append(float(b))

    # Convert to numpy arrays
    y1 = np.array(col1)
    y2 = np.array(col2)
    x = np.arange(1, 1 + len(y1))

    degree = 1

    # Fit polynomials
    poly1 = np.poly1d(np.polyfit(x, y1, degree))
    poly2 = np.poly1d(np.polyfit(x, y2, degree))

    # Evaluate polynomials
    y1_fit = poly1(x)
    y2_fit = poly2(x)

    # Plot
    plt.scatter(x, y1, label="Comparisons", color="blue")
    plt.plot(x, y1_fit, color="blue", linestyle="--")

    plt.scatter(x, y2, label="Assignments", color="green")
    plt.plot(x, y2_fit, color="green", linestyle="--")

    plt.xlabel("n/10")
    plt.ylabel("Absolute number")
    plt.xticks(np.arange(1, 10 + 1, 1))
    plt.yticks(np.arange(1, 7000 + 1, 500))
    plt.title(titles[i])
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig(f"./plots/{fig_names[i]}.png")
    plt.clf()
