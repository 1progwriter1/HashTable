import pandas as pd
import numpy as np

for i in range(1, 8):
    data = pd.read_csv(f'../Results/hash_{i}.csv')
    print(np.var(data['size'].values) / pow(10, 2))

