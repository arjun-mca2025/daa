# Display the contents of the CSV file using pandas
import pandas as pd

print("Before sorting: ")
df = pd.read_csv("./input/data.csv")
print(df.head(10))

print("After sorting: ")
df2 = pd.read_csv("./output/data.csv")
print(df2.head(10))
