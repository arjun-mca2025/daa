"""
Plot the graphs of comparisons and assignments for both merge sort and insertion sort
"""

import numpy as np
import matplotlib.pyplot as plt

merge_files = [
    "output/report_age_only.txt",
    "output/report_name_only.txt",
    "output/report.txt",
]

insertion_files = [
    "../practical-1/output/report_age_only.txt",
    "../practical-1/output/report_name_only.txt",
    "../practical-1/output/report.txt",
]

titles = [
    "When sorted on age alone (compared with Insertion Sort)",
    "When sorted on name alone (compared with Insertion Sort)",
    "When sorted on age followed by name (compared with Insertion Sort)",
]

fig_names = [
    "age_only_comparison_with_insertion",
    "name_only_comparison_with_insertion",
    "both_comparison_with_insertion"
]

# ---------------------------------------------------------------------------- #
#                               Utility functions                              #
# ---------------------------------------------------------------------------- #
def read_csv(file_path, comparisons, assignments):
    """Helper function to read the contents of a CSV of comparisons and assignments and populate the given lists with the data read

    Args:
        file_path (str): File path
        comparisons (List[float]): Comparisons
        assignments (List[float]): Assignments
    """
    with open(file_path, "r", encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            a, b = line.split(",")
            comparisons.append(float(a))
            assignments.append(float(b))
            
def plot(figname, title, comparisons_merge, assignments_merge, comparisons_insertion, assignments_insertion):
    """Plot a comparison plot
    """
    
    # Convert to numpy arrays
    y1_merge = np.array(comparisons_merge)
    y2_merge = np.array(assignments_merge)
    y1_insertion = np.array(comparisons_insertion)
    y2_insertion = np.array(assignments_insertion)
    
    x_merge = np.arange(len(y1_merge))
    x_insertion = np.arange(len(y1_insertion))

    degree_merge = 1
    degree_insertion = 2

    # Fit polynomials
    poly1_merge = np.poly1d(np.polyfit(x_merge, y1_merge, degree_merge))
    poly2_merge = np.poly1d(np.polyfit(x_merge, y2_merge, degree_merge))
    poly1_insertion = np.poly1d(np.polyfit(x_insertion, y1_insertion, degree_insertion))
    poly2_insertion = np.poly1d(np.polyfit(x_insertion, y2_insertion, degree_insertion))

    # Evaluate polynomials
    fit1 = poly1_merge(x_merge)
    fit2 = poly2_merge(x_merge)
    fit3 = poly1_insertion(x_insertion)
    fit4 = poly2_insertion(x_insertion)

    # Plot
    plt.scatter(x_merge, y1_merge, label="Comparisons (Merge Sort)", color="blue")
    plt.plot(x_merge, fit1, color="blue", linestyle="--")

    plt.scatter(x_merge, y2_merge, label="Assignments (Merge Sort)", color="black")
    plt.plot(x_merge, fit2, color="black", linestyle="--")
    
    plt.scatter(x_insertion, y1_insertion, label="Comparisons (Insertion Sort)", color="green")
    plt.plot(x_insertion, fit3, color="green", linestyle="--")
    
    plt.scatter(x_insertion, y1_insertion, label="Assignments (Insertion Sort)", color="red")
    plt.plot(x_insertion, fit4, color="red", linestyle="--")

    plt.xlabel("n/10")
    plt.ylabel("Absolute number")
    plt.title(title)
    plt.legend()
    plt.tight_layout()
    plt.savefig(f"plots/{figname}.png")
    plt.grid()
    plt.clf()

if __name__ == "__main__":
    for i in range(0, len(merge_files)):
        merge_path = merge_files[i]
        insertion_path = insertion_files[i]

        # Lists to store numeric data
        comparisons_merge = []
        assignments_merge = []
        comparisons_insertion = []
        assignments_insertion = []

        # Read CSV
        read_csv(merge_path, comparisons_merge, assignments_merge)
        read_csv(insertion_path, comparisons_insertion, assignments_insertion)
        
        # Plot
        figname = fig_names[i]
        title = titles[i]
        plot(figname, title, comparisons_merge, assignments_merge, comparisons_insertion, assignments_insertion)

        
