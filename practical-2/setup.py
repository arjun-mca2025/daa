import requests
from pathlib import Path

# ----------------------- Create the required structure ---------------------- #

input_folder = Path("input")
output_folder = Path("output")
build_folder = Path("build")

input_folder.mkdir(parents=True, exist_ok=True)
output_folder.mkdir(parents=True, exist_ok=True)
build_folder.mkdir(parents=True, exist_ok=True)

# ------------------------- Download the dataset file ------------------------ #

url = "https://corgis-edu.github.io/corgis/datasets/csv/weather/weather.csv"
input_path = Path("input/data.csv")

response = requests.get(url)
response.raise_for_status()  # Raises error if download fails

with open(input_path, "wb") as f:
    f.write(response.content)

print("Download complete")
