import numpy as np
import matplotlib.pyplot as plt

MarkerSize = 10
FontTitleSize = 20
FLSize = 20
FontTsize = 17

data = np.genfromtxt("analysis.txt", delimiter='\t')

p, t = data[:, 0], data[:, 1]

fig_width = 20 #inch
fig_height = fig_width / 16 * 9 #inch
fig_dpi = 100
fig = plt.figure(figsize = (fig_width, fig_height), dpi = fig_dpi)

ax = fig.add_subplot(221)
ax.plot(p, t, label = 'Time', marker = 'D', linestyle = '', markersize = MarkerSize)
ax.set_title('Time', fontsize = FLSize)
ax.grid()
ax.tick_params(labelsize=FontTsize)
ax.set_xticks(p)


spup = t[0]/t

ax = fig.add_subplot(222)
ax.plot(p, spup, 'rD', label = 'Speed up', markersize = MarkerSize)
ax.set_title('Speed up', fontsize = FLSize)
ax.grid()
ax.tick_params(labelsize=FontTsize)
ax.set_xticks(p)

eff = spup/p;

ax = fig.add_subplot(223)
ax.plot(p, eff, 'bD', label = 'Efficiency', markersize = MarkerSize)
ax.set_title('Efficiency', fontsize = FLSize)
ax.grid()
ax.tick_params(labelsize=FontTsize)
ax.set_xticks(p)

cost = t*p

ax = fig.add_subplot(224)
ax.plot(p, cost, 'gD', label = 'Cost', markersize=MarkerSize)
ax.set_title('Cost', fontsize=FLSize)
ax.grid()
ax.tick_params(labelsize=FontTsize)
ax.set_xticks(p)

fig.suptitle('C++ parallel computing', fontsize = FontTitleSize)
fig.savefig('result.png')



