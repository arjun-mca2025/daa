import os
import shutil
import random

NAMES_FILE = "names.txt"
INPUT_DIR = "./input"

NUM_DIRS = 10
FILES_PER_DIR = 10
RECORDS_PER_FILE = 10


def read_names(path):
    with open(path, "r", encoding="utf-8") as f:
        return [line.strip() for line in f if line.strip()]


def recreate_dir(path):
    if os.path.exists(path):
        shutil.rmtree(path)
    os.makedirs(path)


def generate():
    names = read_names(NAMES_FILE)

    if not names:
        raise RuntimeError("names.txt is empty")

    recreate_dir(INPUT_DIR)

    for dir_index in range(1, NUM_DIRS + 1):
        subdir = os.path.join(INPUT_DIR, f"{dir_index:03}")
        os.makedirs(subdir)

        for file_index in range(1, FILES_PER_DIR + 1):
            filename = f"n{file_index * 10:03}"
            filepath = os.path.join(subdir, filename)

            with open(filepath, "w", encoding="utf-8") as f:
                for _ in range(file_index * RECORDS_PER_FILE):
                    name = random.choice(names)
                    age = random.uniform(20.0, 90.0)
                    f.write(f"{name},{age:.1f}\n")


if __name__ == "__main__":
    generate()
