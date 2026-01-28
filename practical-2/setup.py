import requests
from pathlib import Path
import shutil

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
input_paths = [Path(f"input/n{n*10}") for n in range(1, 10 + 1)]
output_paths = [Path(f"output/n{n*10}") for n in range(1, 10 + 1)]

for input_path in input_paths:
    input_path.mkdir(parents=True, exist_ok=True)

for output_path in output_paths:
    output_path.mkdir(parents=True, exist_ok=True)

# ------------------------- Download the dataset file ------------------------ #

url = "https://corgis-edu.github.io/corgis/datasets/csv/weather/weather.csv"
input_path = Path("input/data.csv")

response = requests.get(url)
response.raise_for_status()  # Raises error if download fails

with open(input_path, "wb") as f:
    f.write(response.content)

print("Download complete")
