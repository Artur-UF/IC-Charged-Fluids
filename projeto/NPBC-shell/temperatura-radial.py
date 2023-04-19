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



def temprad(carga, rs, ri, todas, nbins, conts, binsT=(), binsP=(), switch=0):
	'''
	Assumo que o diametro das partículas é 1
	conts[0]: # de loops
	conts[1]: # de partículas * # de loops
	binsT: bins para a temperatura
	binsP: bins para o numero de partículas em cada bin
	'''
	if switch == 0:
		binsT = np.zeros(nbins)
		binsP = np.zeros(nbins)
		return conts, binsT, binsP
	
	if switch == 1:
		delbin = (rs-ri)/nbins
		conts[0] += 1
		for p in todas:
			conts[1] += 1
			rp = np.sqrt(p.p[0]**2 + p.p[1]**2 + p.p[2]**2) - ri
			v2 = p.v[0]**2 + p.v[1]**2 + p.v[2]**2
			if rp <= rs-(ri+.5) and rp >= .5:
				indice = int(rp/delbin)
				binsT[indice] += v2
				binsP[indice] += 1
			else:
				print(f'Particula [{p.carga}]: ({p.p[0]:.3f}, {p.p[1]:.3f}, {p.p[2]:.3f})\nd = {rp + ri}')
		return conts, binsT, binsP
	
	if switch == 2:
		for i in range(nbins):
			if binsP[i] == 0: 
				binsT[i] = 0
			else:
				binsT[i] /= 3*binsP[i]
		return conts, binsT, binsP
		


#-*-*-*-*-*-*-PARÂMETROS*-*-*-*-*-*-*-*
lb = 1.8
rs = 20
ri = rs/2
tf = 5130
n = 110
ccentral = 50
pos = int((n-ccentral)/2)
neg = int(n-pos)
nbins = 40
#-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

path = f'LJ_RS{rs:.1f}_TF{tf:.1f}_LB{lb:.1f}-FRIC0.05'
nframes = 10000

frames = binstolist(path, n, nframes)

# Calculando
conts1, binsT1, binsP1 = temprad(1, rs, ri, frames[0], nbins, [0, 0])

for fr in range(nframes):
	conts1, binsT1, binsP1 = temprad(1, rs, ri, frames[fr], nbins, conts1, binsT=binsT1, binsP=binsP1, switch=1)

conts1, binsT1, binsP1 = temprad(1, rs, ri, frames[-1], nbins, conts1, binsT=binsT1, binsP=binsP1, switch=2)


r1, delr1 = np.linspace(ri, rs, len(binsT1), retstep=True)

while True:
	if binsT1[0] == 0: 
		binsT1 = binsT1[1:]
		r1 = r1[1:]
	elif binsT1[-1] == 0:
		binsT1 = binsT1[:-1]
		r1 = r1[:-1]
	else: break

plt.plot(r1, binsT1, 'b-+', markersize=4, linewidth=1)
plt.xlabel('r')
plt.ylabel(r'$T(r)$')
plt.title('Temperatura Radial\n'+r'$\lambda_{B}=$'+f'{lb:.1f} | carga central = {ccentral} | snaps = {nframes}')
plt.grid()
plt.savefig(os.path.join(path, 'Temp-rad.png'), dpi=200)
		
