import matplotlib.pyplot as plt
import pandas as pd
from matplotlib.pyplot import figure

figure(figsize=(12, 8), dpi=80, edgecolor='k')

data = pd.read_csv("Results/hash_tables/hash_1.csv")

plt.xlim([-10, max(data['index']) + 100])
plt.ylim([0, max(data['size']) + 100])

plt.xticks(range(0, max(data['index']) + 10, 100))
plt.yticks(range(0, max(data['size']) + 10, 500))

plt.bar(data['index'], data['size'], color='red')

plt.xlabel("index")
plt.ylabel("size")
plt.title("return 0", size=30)

plt.savefig("Images/charts/hash_func_1.png")