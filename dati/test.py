import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

df = pd.read_csv('dati.csv', header=None)

dati = df[0].to_numpy(dtype=float)

print(len(dati))
print(dati>0.2)
plt.hist(dati,bins=100)
plt.show()