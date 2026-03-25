"""
Plot the graphs of comparisons and assignments for both quick sort and insertion sort
"""

import numpy as np
import matplotlib.pyplot as plt

quick_path = "./output/meta.csv"
insertion_path = "../practical-2/output/meta.csv"
merge_path = "../practical-3/output/meta.csv"

title = "When sorted on average temperature"
figname = "comparison"


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
    comparisons_insertion,
    assignments_insertion,
    comparisons_merge,
    assignments_merge,
):
    """Plot a comparison plot"""

    # Convert to numpy arrays
    y1_quick = np.array(comparisons_quick)
    y2_quick = np.array(assignments_quick)

    y1_insertion = np.array(comparisons_insertion)
    y2_insertion = np.array(assignments_insertion)

    y1_merge = np.array(comparisons_merge)
    y2_merge = np.array(assignments_merge)

    x_quick = np.arange(len(y1_quick))
    x_insertion = np.arange(len(y1_insertion))
    x_merge = np.arange(len(y1_merge))

    degree_quick = 1
    degree_insertion = 2
    degree_merge = 1

    # Fit polynomials
    poly1_quick = np.poly1d(np.polyfit(x_quick, y1_quick, degree_quick))
    poly2_quick = np.poly1d(np.polyfit(x_quick, y2_quick, degree_quick))
    poly1_insertion = np.poly1d(np.polyfit(x_insertion, y1_insertion, degree_insertion))
    poly2_insertion = np.poly1d(np.polyfit(x_insertion, y2_insertion, degree_insertion))
    poly1_merge = np.poly1d(np.polyfit(x_merge, y1_merge, degree_merge))
    poly2_merge = np.poly1d(np.polyfit(x_merge, y2_merge, degree_merge))

    # Evaluate polynomials
    fit1 = poly1_quick(x_quick)
    fit2 = poly2_quick(x_quick)
    fit3 = poly1_insertion(x_insertion)
    fit4 = poly2_insertion(x_insertion)
    fit5 = poly1_merge(x_merge)
    fit6 = poly2_merge(x_merge)

    # Plot
    plt.scatter(x_quick, y1_quick, label="Comparisons (Quick Sort)", color="blue")
    plt.plot(x_quick, fit1, color="blue", linestyle="--")

    plt.scatter(x_quick, y2_quick, label="Assignments (Quick Sort)", color="black")
    plt.plot(x_quick, fit2, color="black", linestyle="--")

    plt.scatter(
        x_insertion, y1_insertion, label="Comparisons (Insertion Sort)", color="green"
    )
    plt.plot(x_insertion, fit3, color="green", linestyle="--")

    plt.scatter(
        x_insertion, y2_insertion, label="Assignments (Insertion Sort)", color="red"
    )
    plt.plot(x_insertion, fit4, color="red", linestyle="--")

    plt.scatter(x_merge, y1_merge, label="Comparisons (Merge Sort)", color="yellow")
    plt.plot(x_merge, fit5, color="yellow", linestyle="--")
    plt.scatter(x_merge, y2_merge, label="Assignments (Merge Sort)", color="magenta")
    plt.plot(x_merge, fit6, color="magenta", linestyle="--")

    plt.xlabel("n/10")
    plt.ylabel("Absolute number")
    plt.title(title)
    plt.legend()
    plt.tight_layout()
    plt.savefig(f"plots/{figname}.png")
    plt.grid()
    plt.clf()


if __name__ == "__main__":
    # Lists to store numeric data
    comparisons_quick = []
    assignments_quick = []
    comparisons_insertion = []
    assignments_insertion = []
    comparisons_merge = []
    assignments_merge = []

    # Read CSV
    read_csv(quick_path, comparisons_quick, assignments_quick)
    read_csv(insertion_path, comparisons_insertion, assignments_insertion)
    read_csv(merge_path, comparisons_merge, assignments_merge)

    # Plot
    plot(
        figname,
        title,
        comparisons_quick,
        assignments_quick,
        comparisons_insertion,
        assignments_insertion,
        comparisons_merge,
        assignments_merge,
    )
