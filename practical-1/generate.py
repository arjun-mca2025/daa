import os
import shutil
import random
from pathlib import Path

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

    input_folder = Path("input")
    output_folder = Path("output")
    build_folder = Path("build")

    # Delete these folder if they already exist
    shutil.rmtree(input_folder, ignore_errors=True)
    shutil.rmtree(output_folder, ignore_errors=True)
    shutil.rmtree(build_folder, ignore_errors=True)

    input_folder.mkdir(parents=True, exist_ok=True)
    output_folder.mkdir(parents=True, exist_ok=True)
    build_folder.mkdir(parents=True, exist_ok=True)

    # Make sure that input and output sample folders exist
    input_paths = [Path(f"input/{n:03}") for n in range(1, 10 + 1)]
    output_paths = [Path(f"output/{n:03}") for n in range(1, 10 + 1)]

    for input_path in input_paths:
        input_path.mkdir(parents=True, exist_ok=True)

    for output_path in output_paths:
        output_path.mkdir(parents=True, exist_ok=True)

    open(
        "./output/time.txt", "a"
    ).close()  # create the time file if it does not exist already

    for dir_index in range(1, NUM_DIRS + 1):
        subdir = os.path.join(INPUT_DIR, f"{dir_index:03}")
        os.makedirs(subdir, exist_ok=True)

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
