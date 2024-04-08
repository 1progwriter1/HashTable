import matplotlib.pyplot as plt
import pandas as pd
from matplotlib.pyplot import figure

figure(figsize=(12, 8), dpi=80, edgecolor='k')

data = pd.read_csv("../Results/hash_1.csv")

plt.xlim([-10, max(data['index']) + 10])
plt.ylim([0, max(data['size']) + 10])

plt.xticks(range(0, max(data['index']) + 10, 100))
plt.yticks(range(0, max(data['size']) + 100, 500))

plt.bar(data['index'], data['size'], color='red')

plt.xlabel("index")
plt.ylabel("size")
plt.title("elements distribution")

plt.show()