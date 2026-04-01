"""
Plot the graphs of comparisons and assignments for both quick sort and randomized quick sort
"""

import numpy as np
import matplotlib.pyplot as plt

random_files = [
    "output/report_age_only.txt",
    "output/report_name_only.txt",
    "output/report.txt",
]

quick_files = [
    "../practical-4/output/report_age_only.txt",
    "../practical-4/output/report_name_only.txt",
    "../practical-4/output/report.txt",
]

titles = [
    "When sorted on age alone (compared with Quick Sort)",
    "When sorted on name alone (compared with Quick Sort)",
    "When sorted on age followed by name (compared with Quick Sort)",
]

fig_names = [
    "age_only_comparison",
    "name_only_comparison",
    "both_comparison",
]


# ---------------------------------------------------------------------------- #
#                               Utility functions                              #
# ---------------------------------------------------------------------------- #
def read_csv(file_path, comparisons, assignments):
    """Helper function to read the contents of a CSV of comparisons and assignments and populate the given lists with the data read"""
    with open(file_path, "r", encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            a, b = line.split(",")
            comparisons.append(float(a))
            assignments.append(float(b))


def plot(
    figname,
    title,
    comparisons_quick,
    assignments_quick,
    comparisons_random,
    assignments_random,
):
    """Plot a comparison plot"""

    # Convert to numpy arrays
    y1_quick = np.array(comparisons_quick)
    y2_quick = np.array(assignments_quick)

    y1_random = np.array(comparisons_random)
    y2_random = np.array(assignments_random)

    x_quick = np.arange(len(y1_quick))
    x_random = np.arange(len(y1_random))

    degree_quick = 1
    degree_random = 1

    # Fit polynomials
    poly1_quick = np.poly1d(np.polyfit(x_quick, y1_quick, degree_quick))
    poly2_quick = np.poly1d(np.polyfit(x_quick, y2_quick, degree_quick))
    poly1_random = np.poly1d(np.polyfit(x_random, y1_random, degree_random))
    poly2_random = np.poly1d(np.polyfit(x_random, y2_random, degree_random))

    # Evaluate polynomials
    fit1 = poly1_quick(x_quick)
    fit2 = poly2_quick(x_quick)
    fit3 = poly1_random(x_random)
    fit4 = poly2_random(x_random)

    # Plot
    plt.scatter(x_quick, y1_quick, label="Comparisons (Quick Sort)", color="blue")
    plt.plot(x_quick, fit1, color="blue", linestyle="--")

    plt.scatter(x_quick, y2_quick, label="Assignments (Quick Sort)", color="black")
    plt.plot(x_quick, fit2, color="black", linestyle="--")

    plt.scatter(
        x_random,
        y1_random,
        label="Comparisons (Randomized Quick Sort)",
        color="green",
    )
    plt.plot(x_random, fit3, color="green", linestyle="--")

    plt.scatter(x_random, y2_random, label="Assignments (Randomized Sort)", color="red")
    plt.plot(x_random, fit4, color="red", linestyle="--")

    plt.xlabel("n/10")
    plt.ylabel("Absolute number")
    plt.title(title)
    plt.legend()
    plt.tight_layout()
    plt.savefig(f"plots/{figname}.png")
    plt.grid()
    plt.clf()


if __name__ == "__main__":
    for i in range(0, len(quick_files)):
        random_path = random_files[i]
        quick_path = quick_files[i]

        # Lists to store numeric data
        comparisons_random = []
        assignments_random = []
        comparisons_quick = []
        assignments_quick = []

        # Read CSV
        read_csv(quick_path, comparisons_quick, assignments_quick)
        read_csv(random_path, comparisons_random, assignments_random)

        # Plot
        figname = fig_names[i]
        title = titles[i]
        plot(
            figname,
            title,
            comparisons_quick,
            assignments_quick,
            comparisons_random,
            assignments_random,
        )
