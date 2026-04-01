import numpy as np
import matplotlib.pyplot as plt

radix_path = "./output/time.txt"
quick_path = "../practical-4/output/time.txt"
merge_path = "../practical-3/output/time.txt"
insertion_path = "../practical-1/output/time.txt"

title = "Running Time Comparison (in ms)"
figname = "time_comparison"


# ---------------------------------------------------------------------------- #
#                               Utility functions                              #
# ---------------------------------------------------------------------------- #
def read_csv(file_path, times):
    with open(file_path, "r", encoding="utf-8") as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            times.append(float(line))


def plot(
    figname,
    title,
    times_radix,
    times_quick,
    times_merge,
    times_insertion,
):
    # Convert to numpy arrays
    y_radix = np.array(times_radix)
    y_quick = np.array(times_quick)
    y_merge = np.array(times_merge)
    y_insertion = np.array(times_insertion)

    x_radix = np.arange(1, 1 + len(y_radix))
    x_quick = np.arange(1, 1 + len(y_quick))
    x_merge = np.arange(1, 1 + len(y_merge))
    x_insertion = np.arange(1, 1 + len(y_insertion))

    # Plot
    plt.plot(x_radix, y_radix, label="Radix Sort", color="red", marker="o")
    plt.plot(x_quick, y_quick, label="Quick Sort", color="blue", marker="o")
    plt.plot(x_merge, y_merge, label="Merge Sort", color="pink", marker="o")
    plt.plot(
        x_insertion,
        y_insertion,
        label="Insertion Sort",
        color="cyan",
        marker="o",
    )

    plt.xlabel("n/10")
    plt.ylabel("Time (ms)")
    plt.xticks(np.arange(0, 10 + 1, 1))
    plt.title(title)
    plt.legend()
    plt.tight_layout()
    plt.grid(True)
    plt.savefig(f"plots/{figname}.png")
    plt.clf()


if __name__ == "__main__":
    # Lists to store numeric data
    times_radix = []
    times_quick = []
    times_merge = []
    times_insertion = []

    # Read CSV
    read_csv(radix_path, times_radix)
    read_csv(quick_path, times_quick)
    read_csv(merge_path, times_merge)
    read_csv(insertion_path, times_insertion)

    # Plot
    plot(
        figname,
        title,
        times_radix,
        times_quick,
        times_merge,
        times_insertion,
    )
