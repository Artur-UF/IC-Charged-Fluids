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


def dprad(carga, rs, ri, todas, nbins, bins=(), conts=[0, 0], switch=0):
	ticks, delbin = np.linspace(ri, rs, nbins+1, retstep=True)
	
	if switch == 0:
		bins = np.zeros(nbins)	
		return conts, bins
	
	if switch == 1:
		conts[0] += 1
		for p in todas:
			if p.carga == carga:
				conts[1] += 1
				rp = np.sqrt(p.p[0]**2 + p.p[1]**2 + p.p[2]**2) - ri
				bins[int(rp/delbin)] += 1				
		return conts, bins
	
	if switch == 2:
		bins /= conts[1]
		return conts, bins


#-*-*-*-*-*-*-PARÂMETROS*-*-*-*-*-*-*-*
lb = 1.8
rs = 10
ri = rs/2
tf = 555
n = 90
ccentral = 30
pos = int((n-ccentral)/2)
neg = int(n-pos)
nbins = 50
#-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

path = f'LJ_RS{rs:.1f}_TF{tf:.1f}_LB{lb:.1f}'
nframes = 1000

frames = binstolist(path, n, nframes)

# Linha para cargas POSITIVAS
conts1, bins1 = dprad(1, rs, ri, frames[0], nbins)

for fr in range(nframes):
	conts1, bins1 = dprad(1, rs, ri, frames[fr], nbins, bins=bins1, conts=conts1, switch=1)

conts1, bins1 = dprad(1, rs, ri, frames[-1], nbins, bins=bins1, conts=conts1, switch=2)


# Linha para cargas NEGATIVAS
conts2, bins2 = dprad(-1, rs, ri, frames[0], nbins)

for fr in range(nframes):
	conts2, bins2 = dprad(-1, rs, ri, frames[fr], nbins, bins=bins2, conts=conts2, switch=1)

conts2, bins2 = dprad(-1, rs, ri, frames[-1], nbins, bins=bins2, conts=conts2, switch=2)


r = np.linspace(ri, rs, len(bins1))

plt.plot(r, bins1, label=f'{pos:.0f}*'+r'$Na^{+}$')
plt.plot(r, bins2, label=f'{neg:.0f}*'+r'$Cl^{-}$')
plt.xlabel('r')
plt.ylabel('g(r)')
plt.title('Densidade Radial: g(r)\n'+r'$\lambda_{B}=$'+f'{lb:.1f} | carga central = {ccentral} | snaps = {nframes}')
plt.grid()
plt.legend()
plt.savefig(os.path.join(path, 'rdf.png'), dpi=200)







