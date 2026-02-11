"""
Pre-conditions for running this file:
1. Practical 1's insertion sort generate.py has been run
2. Practical 1's insertion sort binary has been run to produce the output in the form of a report of comparisons and assignments

This file is supposed to perform the following things:

1. Ask the user what mode of operation is to be performed: 0 for just copying the generated data from "../practical-1/input" or 1 for generating data randomly from scratch
"""

import os
import shutil
import random
from pathlib import Path

NAMES_FILE = "names.txt"
INPUT_DIR = "./input"

NUM_DIRS = 10
FILES_PER_DIR = 10
RECORDS_PER_FILE = 10

# ---------------------------------------------------------------------------- #
#                               Utility functions                              #
# ---------------------------------------------------------------------------- #

def read_names(path):
    """Read the names list

    Args:
        path (str): Path to the names file

    Returns:
        List[str]: List of names
    """
    with open(path, "r", encoding="utf-8") as f:
        return [line.strip() for line in f if line.strip()]


def recreate_dir(path):
    """Delete the given directory's contents without deleting the directory itself

    Args:
        path (str): Path of the directory
    """
    if os.path.exists(path):
        shutil.rmtree(path)
    os.makedirs(path)
    

# ---------------------------------------------------------------------------- #
#                                Main functions                                #
# ---------------------------------------------------------------------------- #

def copy_previous_input():
    """Copy the Insertion sort input data
    """
    
    recreate_dir(INPUT_DIR) # Clear the input directory
    
    src = Path("../practical-1/input")
    dest = Path("./input")

    shutil.copytree(src, dest, dirs_exist_ok=True)

def generate():
    """Generate random data

    Raises:
        RuntimeError: If the names list supplied is empty
    """
    
    recreate_dir(INPUT_DIR) # Clear the input directory
    
    names = read_names(NAMES_FILE)

    if not names:
        raise RuntimeError("names.txt is empty")


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
        # ----------------------- Create the required structure ---------------------- #

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
    input_paths = [Path(f"input/{n*10:03}") for n in range(1, 10 + 1)]
    output_paths = [Path(f"output/{n*10:03}") for n in range(1, 10 + 1)]

    for input_path in input_paths:
        input_path.mkdir(parents=True, exist_ok=True)

    for output_path in output_paths:
        output_path.mkdir(parents=True, exist_ok=True)
    
    print("Enter 0 for copying previous input data from insertion sort and 1 for generate new data: ")
    choice = int(input())
    
    if choice == 0:
        copy_previous_input()
    elif choice == 1:
        generate()