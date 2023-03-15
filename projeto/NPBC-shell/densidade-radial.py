import matplotlib.pyplot as plt
import numpy as np
import os
import struct


# Definindo a estrutura
class Particle:
	def __init__(self, list):
		self.p = list[0:3]
		self.v = list[3:6]
		self.f = list[6:9]
		self.carga = list[9]
		self.gaussian = list[10:-1]


def binstolist(path, n, passos):
	struct_fmt = '=3d3d3dd3d'
	struct_len = struct.calcsize(struct_fmt)
	struct_unpack = struct.Struct(struct_fmt).unpack_from


	# Lendo e atribuindo os binarios dentro de objetos e listas
	frames = list([] for i in range(passos))

	for frame in range(passos):
		with open(os.path.join(path, f'passos/{frame+1}.bin'), "rb") as f:
			for i in range(n):
				data = f.read(struct_len)
				s = struct_unpack(data)
				frames[frame].append(Particle(s))
	return frames


def dprad(carga, rs, ri, todas, nbins, conts, bins=(), switch=0):
	if switch == 0:
		bins = np.zeros(nbins)	
		return conts, bins
	
	if switch == 1:
		delbin = (rs-ri)/nbins
		conts[0] += 1
		for p in todas:
			if p.carga == carga:
				conts[1] += 1
				rp = np.sqrt(p.p[0]**2 + p.p[1]**2 + p.p[2]**2) - ri
				bins[int(rp/delbin)] += 1				
		return conts, bins
	
	if switch == 2:
		ticks, delbin = np.linspace(ri, rs, nbins+1, retstep=True)	
		v1 = (4/3)*np.pi
		for i in range(nbins):
			bins[i] /= conts[0]*v1*(ticks[i+1]**3 - ticks[i]**3)
		return conts, bins


#-*-*-*-*-*-*-PARÂMETROS*-*-*-*-*-*-*-*
lb = 1.8
rs = 20
ri = rs/2
tf = 5130
n = 90
ccentral = 30
pos = int((n-ccentral)/2)
neg = int(n-pos)
nbins = 100
#-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

path = f'LJ_RS{rs:.1f}_TF{tf:.1f}_LB{lb:.1f}'
nframes = 10000

frames = binstolist(path, n, nframes)

# Linha para cargas POSITIVAS
conts1, bins1 = dprad(1, rs, ri, frames[0], nbins, [0, 0])

for fr in range(nframes):
	conts1, bins1 = dprad(1, rs, ri, frames[fr], nbins, conts1, bins=bins1, switch=1)

conts1, bins1 = dprad(1, rs, ri, frames[-1], nbins, conts1, bins=bins1, switch=2)

# Linha para cargas NEGATIVAS
conts2, bins2 = dprad(-1, rs, ri, frames[0], nbins, [0, 0])

for fr in range(nframes):
	conts2, bins2 = dprad(-1, rs, ri, frames[fr], nbins, conts2, bins=bins2, switch=1)

conts2, bins2 = dprad(-1, rs, ri, frames[-1], nbins, conts2, bins=bins2, switch=2)

r, delr = np.linspace(ri, rs, len(bins1), retstep=True)

# Comparação
x1, y1, y2 = np.loadtxt('dens.dat', unpack=True)

xr, delxr = np.linspace(x1[0], x1[-1], len(x1), retstep=True)

plt.plot(x1, y1, 'k')
plt.plot(x1, y2, 'r')

p_pos_t = 0
for ri, rho in zip(x1, y1):
	p_pos_t += rho*(ri**2)*delxr
p_pos_t *= 4*np.pi

p_neg_t = 0
for ri, rho in zip(x1, y2):
	p_neg_t += rho*(ri**2)*delxr
p_neg_t *= 4*np.pi


#*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-

p_pos = 0
for ri, rho in zip(r, bins1):
	p_pos += rho*(ri**2)*delr
p_pos *= 4*np.pi

p_neg = 0
for ri, rho in zip(r, bins2):
	p_neg += rho*(ri**2)*delr
p_neg *= 4*np.pi

plt.plot(r, bins1, 'b-*', markersize=5, linewidth=1, label=f'{pos:.0f}*'+r'$Na^{+}$')
plt.plot(r, bins2, 'g-*', markersize=5, linewidth=1, label=f'{neg:.0f}*'+r'$Cl^{-}$')
plt.xlabel('r')
plt.ylabel(r'$\rho(r)$')
plt.title('Densidade Radial\n'+r'$\lambda_{B}=$'+f'{lb:.1f} | carga central = {ccentral} | snaps = {nframes}')
plt.grid()
plt.legend()
plt.savefig(os.path.join(path, 'drad-comp.png'), dpi=200)
print(f'Número de partículas:\n\tMinhas\tTeoria\nCla+ = {p_pos:.3f}\t{p_pos_t:.3f}\nCl- = {p_neg:.3f}\t{p_neg_t:.3f}')





