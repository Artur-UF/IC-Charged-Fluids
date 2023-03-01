import numpy as np
import matplotlib.pyplot as plt
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



def rdf(carga, rs, ri, pos, neg, todas, size=10, g=(), ngr=0, switch=0):
	nbins = int(rs-ri) * size				# Número de bins em função do tamanho do sistema
	delg = (rs-ri)/(nbins)					# Tamanho dos bins
	rhopos = pos/((4/3)*np.pi*(rs**3 - ri**3))
	rhoneg = neg/((4/3)*np.pi*(rs**3 - ri**3))
	
	
	if switch == 0:
		g = np.zeros(nbins)
		return ngr, g
	
	if switch == 1:
		ngr += 1
		for p in todas:
			if p.carga == carga:
				rp = np.sqrt(p.p[0]**2 + p.p[1]**2 + p.p[2]**2) - ri
				ig = int(rp/delg)
				if ig < nbins:
					g[ig] += 1
				else: print('Deu merda nessa')
		return ngr, g
	
	if switch == 2:
		if carga == 1:
			for i in range(nbins):
				vb = ((i+1)**3 - i**3)*delg**3
				nid = (4/3)*np.pi*vb*rhopos
				g[i] /= (ngr*pos*nid)
		if carga == -1:				
			for i in range(nbins):
				vb = ((i+1)**3 - i**3)*delg**3
				nid = (4/3)*np.pi*vb*rhoneg
				g[i] /= (ngr*neg*nid)
		return ngr, g
			
	
#-*-*-*-*-*-*-PARÂMETROS*-*-*-*-*-*-*-*
lb = 1.8
rs = 10
ri = rs/2
tf = 555
n = 90
ccentral = 30
pos = int((n-ccentral)/2)
neg = int(n-pos)
size = 10
#-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

path = f'LJ_RS{rs:.1f}_TF{tf:.1f}_LB{lb:.1f}'
nframes = 1000

frames = binstolist(path, n, nframes)

# Função para as partículas positivas
ngr1, g1 = rdf(1, rs, ri, pos, neg, frames[0], size=size)

for fr in range(nframes):
	ngr1, g1 = rdf(1, rs, ri, pos, neg, frames[fr], size=size, g=g1, ngr=ngr1, switch=1)

ngr1, g1 = rdf(1, rs, ri, pos, neg, frames[-1], size=size, g=g1, ngr=ngr1, switch=2)



# Função para as partículas negativas
ngr2, g2 = rdf(2, rs, ri, pos, neg, frames[0], size=size)

for fr in range(nframes):
	ngr2, g2 = rdf(-1, rs, ri, pos, neg, frames[fr], size=size, g=g2, ngr=ngr2, switch=1)

ngr2, g2 = rdf(-1, rs, ri, pos, neg, frames[-1], size=size, g=g2, ngr=ngr2, switch=2)


r = np.linspace(ri, rs, len(g1))

plt.plot(r, g1, label=f'{pos:.0f}*'+r'$Na^{+}$')
plt.plot(r, g2, label=f'{neg:.0f}*'+r'$Cl^{-}$')
plt.xlabel('r')
plt.ylabel('g(r)')
plt.title('Densidade Radial: g(r)\n'+r'$\lambda_{B}=$'+f'{lb:.1f} | carga central = {ccentral} | snaps = {nframes}')
plt.grid()
plt.legend()
plt.savefig(os.path.join(path, 'rdf.png'), dpi=200)

