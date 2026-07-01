import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('hello.txt', sep='\s+', skiprows=1, names=['t', 'V'])
df.plot(x='t', y='V')
plt.savefig('output.png')
