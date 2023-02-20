import os
import struct
import numpy as np
import matplotlib.pyplot as plt


# Definindo a estrutura
class Particle:
	def __init__(self, list):
		self.p = list[0:3]
		self.v = list[3:6]
		self.f = list[6:9]
		self.carga = list[9]
		self.gaussian = list[10:-1]


def binstolist(path, passos):
	struct_fmt = '=3d3d3dd3d'
	struct_len = struct.calcsize(struct_fmt)
	struct_unpack = struct.Struct(struct_fmt).unpack_from


	# Lendo e atribuindo os binarios dentro de objetos e listas
	frames = list([] for i in range(passos))

	for frame in range(passos):
		with open(os.path.join(path, f'passos/{frame+1}.bin'), "rb") as f:
			for i in range(100):
				data = f.read(struct_len)
				s = struct_unpack(data)
				frames[frame].append(Particle(s))
	return frames



def rdf(carga, rs, ri, todas, size=10, g=(), ngr=0, switch=0):
	n = len(todas)
	nbins = (rs-ri) * size	# Número de bins em função do tamanho do sistema
	delg = (rs-ri)/(nbins)	# Tamanho dos bins SE DER ERRADO BOTA O 2
	rho = n/((4/3)*np.pi*(rs**3 - ri**3))
	
	if switch == 0:
		g = np.zeros(nbins)
		return ngr, g
	
	if switch == 1:
		ngr += 1
		for p in todas:
			if p.carga == carga:
				rp = np.sqrt(p.p[0]**2 + p.p[1]**2 + p.p[2]**2) - ri
				ig = int(rp/delg)
				g[ig] += 1
		return ngr, g
	
	if switch == 2:
		for i in range(nbins):
			vb = ((i+1)**3 - i**3)*delg**3
			nid = (4/3)*np.pi*vb*rho
			g[i] /= (ngr*n*nid)	
		return ngr, g
			
	
path = "LJ_RS10.0_TF30.0_LB7.0"
nframes = 500

frames = binstolist(path, nframes)

rs = 10 
ri = 5
size = 10


# Função para as partículas positivas
ngr1, g1 = rdf(1, rs, ri, frames[0], size=size)

for fr in range(nframes):
	ngr1, g1 = rdf(1, rs, ri, frames[fr], size=size, g=g1, ngr=ngr1, switch=1)

ngr1, g1 = rdf(1, rs, ri, frames[-1], size=size, g=g1, ngr=ngr1, switch=2)



# Função para as partículas negativas
ngr2, g2 = rdf(2, rs, ri, frames[0], size=size)

for fr in range(nframes):
	ngr2, g2 = rdf(-1, rs, ri, frames[fr], size=size, g=g2, ngr=ngr2, switch=1)

ngr2, g2 = rdf(-1, rs, ri, frames[-1], size=size, g=g2, ngr=ngr2, switch=2)


r = np.linspace(5, 10, len(g1))

plt.plot(r, g1, label='Na')
plt.plot(r, g2, label='Cl')
plt.xlabel('r')
plt.ylabel('g(r)')
plt.title('Função de Distribuição Radial: g(r)')
plt.grid()
plt.legend()
plt.savefig(os.path.join(path, 'rdf.png'), dpi=200)























