import sys
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
from scipy.stats import norm

input = sys.argv[1]
database = pd.read_csv(input, names=("label", "time", "reso"))
label = database["label"]
time = database["time"]
reso = database["reso"]

#Labels without Juhuku
lblData = []
for l in label.values:
    if l not in lblData:
        lblData.append(l)


fig = plt.figure()

# Plot Plot
ax_plot = fig.add_subplot(1,1,1)
ax_plot.set_ylabel(reso.values[0])

for l in lblData:
    # Histgram
    getTime = time[(label == l)].values
    
    info = "" + l
    ax_plot.plot(getTime, '.', label = info)

plt.legend()
plt.show()
