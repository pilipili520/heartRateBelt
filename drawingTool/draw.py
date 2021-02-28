import matplotlib.pyplot as plt
import numpy as np

data = np.loadtxt('tmp.txt')
x = range(0,len(data))
plt.plot(x,data)
plt.show()
