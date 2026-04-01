"""
Plot the graphs of comparisons and assignments for both quick sort and randomized quick sort
"""

import numpy as np
import matplotlib.pyplot as plt

radix_files = [
    "output/report_age_only.txt",
    "output/report_name_only.txt",
    "output/report.txt",
]

quick_files = [
    "../practical-4/output/report_age_only.txt",
    "../practical-4/output/report_name_only.txt",
    "../practical-4/output/report.txt",
]

merge_files = [
    "../practical-3/output/report_age_only.txt",
    "../practical-3/output/report_name_only.txt",
    "../practical-3/output/report.txt",
]

insertion_files = [
    "../practical-1/output/report_age_only.txt",
    "../practical-1/output/report_name_only.txt",
    "../practical-1/output/report.txt",
]

titles = [
    "When sorted on age alone (comparison)",
    "When sorted on name alone (comparison)",
    "When sorted on age followed by name (comparison)",
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
    comparisons_radix,
    assignments_radix,
    comparisons_quick,
    assignments_quick,
    comparisons_merge,
    assignments_merge,
    comparisons_insertion,
    assignments_insertion,
):
    """Plot a comparison plot"""

    # Convert to numpy arrays
    y1_radix = np.array(comparisons_radix)
    y2_radix = np.array(assignments_radix)

    y1_quick = np.array(comparisons_quick)
    y2_quick = np.array(assignments_quick)

    y1_merge = np.array(comparisons_merge)
    y2_merge = np.array(assignments_merge)

    y1_insertion = np.array(comparisons_insertion)
    y2_insertion = np.array(assignments_insertion)

    x_radix = np.arange(1, 1 + len(y1_quick))
    x_quick = np.arange(1, 1 + len(y1_quick))
    x_merge = np.arange(1, 1 + len(y1_merge))
    x_insertion = np.arange(1, 1 + len(y1_insertion))

    # Plot
    plt.plot(
        x_radix, y1_radix, label="Comparisons (Radix Sort)", color="red", marker="o"
    )
    plt.plot(
        x_radix, y2_radix, label="Assignments (Radix Sort)", color="green", marker="s"
    )
    plt.plot(
        x_quick, y1_quick, label="Comparisons (Quick Sort)", color="blue", marker="o"
    )
    plt.plot(
        x_quick, y2_quick, label="Assignments (Quick Sort)", color="black", marker="s"
    )
    plt.plot(
        x_merge, y1_merge, label="Comparisons (Merge Sort)", color="pink", marker="o"
    )
    plt.plot(
        x_merge, y2_merge, label="Assignments (Merge Sort)", color="gray", marker="s"
    )
    plt.plot(
        x_insertion,
        y1_insertion,
        label="Comparisons (Insertion Sort)",
        color="cyan",
        marker="o",
    )
    plt.plot(
        x_insertion,
        y2_insertion,
        label="Assignments (Insertion Sort)",
        color="magenta",
        marker="s",
    )

    plt.xlabel("n/10")
    plt.ylabel("Absolute number")
    plt.xticks(np.arange(0, 10 + 1, 1))
    plt.yticks(np.arange(0, 7000 + 1, 500))
    plt.title(title)
    plt.legend()
    plt.tight_layout()
    plt.grid(True)
    plt.savefig(f"plots/{figname}.png")
    plt.clf()


if __name__ == "__main__":
    for i in range(0, len(radix_files)):
        radix_path = radix_files[i]
        quick_path = quick_files[i]
        merge_path = merge_files[i]
        insertion_path = insertion_files[i]

        # Lists to store numeric data
        comparisons_radix = []
        assignments_radix = []
        comparisons_quick = []
        assignments_quick = []
        comparisons_merge = []
        assignments_merge = []
        comparisons_insertion = []
        assignments_insertion = []

        # Read CSV
        read_csv(radix_path, comparisons_radix, assignments_radix)
        read_csv(quick_path, comparisons_quick, assignments_quick)
        read_csv(merge_path, comparisons_merge, assignments_merge)
        read_csv(insertion_path, comparisons_insertion, assignments_insertion)

        # Plot
        figname = fig_names[i]
        title = titles[i]
        plot(
            figname,
            title,
            comparisons_radix,
            assignments_radix,
            comparisons_quick,
            assignments_quick,
            comparisons_merge,
            assignments_merge,
            comparisons_insertion,
            assignments_insertion,
        )
