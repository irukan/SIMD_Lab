import sys
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd
from scipy.stats import norm

input = sys.argv[1]
binN = float(sys.argv[2])
min = float(sys.argv[3])
max = float(sys.argv[4])

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

# Plot Histgram
ax_hist = fig.add_subplot(1,1,1)
ax_hist.set_xlabel(reso.values[0])

for l in lblData:
    # Histgram
    getTime = time[(label == l) & (time > min) & (time < max)].values
    #getTime = time[(label == l)].values
    (mu, sigma) = norm.fit(getTime)
    mid = np.median(getTime)

    info = l + " " + r'$\mathrm{}\ \mu=%.2f\ \sigma=%.2f$' %(mu, sigma)
    ax_hist.hist(getTime, bins = binN, histtype='step',linewidth=1.5, label = info)

plt.legend()
plt.show()







