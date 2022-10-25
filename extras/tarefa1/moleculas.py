from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

x, y, z = np.loadtxt("/home/arturuf/Documentos/GitHub/IC-Charged-Fluids/projeto/particulas_pont.txt", usecols=(1, 2, 3), skiprows=2, unpack=True)

list_center = []
for xi, yi, zi in zip(x, y, z):
    tup = (xi, yi, zi)
    list_center.append(tup)

r = 1
list_radius = np.ones(len(list_center)) * r


def plt_sphere(list_center, list_radius):
    fig, ax = plt.subplots(subplot_kw={"projection": "3d"})
    for c, r in zip(list_center, list_radius):
        #ax = fig.gca(projection='3d')

        # draw sphere
        u, v = np.mgrid[0:2*np.pi:50j, 0:np.pi:50j]
        x = r*np.cos(u)*np.sin(v)
        y = r*np.sin(u)*np.sin(v)
        z = r*np.cos(v)

        ax.plot_surface(x-c[0], y-c[1], z-c[2], color=np.random.choice(['g','b']), alpha=1)


plt_sphere(list_center, list_radius)
plt.savefig('moleculasIC.png', dpi=300)
