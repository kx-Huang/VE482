import matplotlib.pyplot as plt
from matplotlib.ticker import MaxNLocator

n = [i for i in range(12)]
u25 = [1 - 0.25**i for i in n]
u60 = [1 - 0.60**i for i in n]
u90 = [1 - 0.90**i for i in n]

ax = plt.figure().gca()
ax.xaxis.set_major_locator(MaxNLocator(integer=True))

plt.plot(n, u25, '-o')
plt.plot(n, u60, '-o')
plt.plot(n, u90, '-o')

plt.legend(['p = 25%', 'p = 60%', 'p = 90%'])
plt.xlabel("Number of Process")
plt.ylabel("CPU Utilisation")
plt.title("CPU Utilisation vs. Number of Process")

plt.show()