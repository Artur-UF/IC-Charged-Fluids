#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct particle {
	// Estrutura com os atributos possíveis de uma partícula
	double p[3];
	double v[3];
	double f[3];
	double carga;
	double gaussian[3]; // Atributo para ajudar na integração
}particle;

//*-*-*-*-*-*-*-*-*FUNÇÕES PARA O GERADOR DE CONCIÇÕES INICIAIS*-*-*-*-*-*-*-*-*-
double uniform(double min, double max) {
	/*
	Função que gera um número aleatório em uma distribuição uniforme
	*/
	double random  = ((double) rand()) / RAND_MAX;
	double range = (max - min) * random;
	double n = range + min;	
	
	return n;
}


double dist(double dx, double dy, double dz){
	/*
	Calcula a distância entre duas partículas em 3D
	*/
	return sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));
}


particle check(particle *ptodas, int ind, double r, double lx, double ly, double lz){
	/*
	Função recursiva que checa a distância entre a partícula gerada e o resto delas
	*/
	double lx_min = (-lx/2) + r;
	double lx_max = (lx/2) - r;
	double ly_min = (-ly/2) + r;
	double ly_max = (ly/2) - r;
	double lz_min = (-lz/2) + r;
	double lz_max = (lz/2) - r;
	
	particle *final = ptodas;
	
	for (int j = ind - 1; j >= 0; --j){
		--ptodas;
		//printf ("Checando a particula %i com %i\n", ind, j);
		double dx = final->p[0] - ptodas->p[0];
		double dy = final->p[1] - ptodas->p[1];
		double dz = final->p[2] - ptodas->p[2];
		if (dist(dx, dy, dz) <= 2*r) {
			//printf ("recriando a particula %i\n", ind);
			final->p[0] = uniform(lx_min, lx_max);
			final->p[1] = uniform(ly_min, ly_max);
			final->p[2] = uniform(lz_min, lz_max);
			*final = check(final, ind, r, lx, ly, lz);
		}
	}
	return *final;
}


//-*-*-*-*-*-*-*-*-*-*-FUNÇÕES PARA A DINÂMICA*-*-*-*-*-*-*-*-*-*-*-*-*-
double imin(double p1, double p2, double l){
    // Imagem mínima
    double dp;
    
    dp = p2 - p1;
    dp = dp - round(dp/l)*l;
    
    return dp;
}


void forcas(particle *todas, int n, double lx, double ly, double lz){
	// Libera a memória depois
	double imin(double p1, double p2, double l);
	double cut, c5, dx, dy, dz, dist, fx, fy, fz;
	cut = pow(2., 1./6.); // ESSE CORTE ESTÁ MUITO PEQUENO, POR ISSO NÃO GERA FORÇA
	
	// Zerando as forças antes de recalcular
	for (int i = 0; i < n; ++i){
		todas[i].f[0] = 0.0;
		todas[i].f[1] = 0.0;
		todas[i].f[2] = 0.0;
	}
	
	// ACHO QUE O ERRO ESTÁ AQUI
	for (int i = 0; i < n; ++i){
		for (int j = i + 1; j < n; ++j){
				dx = imin(todas[i].p[0], todas[j].p[0], lx);
				dy = imin(todas[i].p[1], todas[j].p[1], ly);
				dz = imin(todas[i].p[2], todas[j].p[2], lz);
				dist = sqrt(dx*dx + dy*dy + dz*dz);
				
				//printf("%-3d e %-3d\tDistancia; %.3lf\tcut; %.3lf\n", i+1, j+1, dist, cut);
				// Lennard-Jones
				c5 = 0.0; 
				if (dist<cut){
					c5 = 5.*( - 6./pow(dist,7) + 12./pow(dist,13));
					if (dist <= 0.8){
						c5 = 5.*( - 6./pow(0.8,7) + 12./pow(0.8,13));
					}
				}

				// Atribuindo as componentes das forças
				fx = c5*dx/dist;
				fy = c5*dy/dist;
				fz = c5*dz/dist;
				todas[i].f[0] += fx;
				todas[j].f[0] += -fx;
				todas[i].f[1] += fy;
				todas[j].f[1] += -fy;
				todas[i].f[2] += fz;
				todas[j].f[2] += -fz;
		}
	}
}

double gausran(){
    // generate gaussianrandom_numbers                                                                   
    int g;
    double ran1,ran2,PI,R1,R2,res;
    ran1 = (double)rand()/RAND_MAX;
    ran2 = (double)rand()/RAND_MAX;
    PI   = 4.0*atan(1.0);
    R1   = -log(1.0-ran1);
    R2   = 2.0*PI*ran2;
    R1   = sqrt(2.0*R1);
    res  = R1*cos(R2);
    return res;
}

/* TENTATIVA DE COPIAR A FUNÇÃO EM PYTHON
double aij(double r, double eps, double sig){
	return 48 * (eps / (sig*sig)) * (pow((sig / r), 14) - (0.5 * pow((sig / r), 8)));
}

void forcas(particle *todas, int n, double lx, double ly, double lz){
	// Libera a memória depois
	double imin(double p1, double p2, double l);
	double cut, dx, dy, dz, dist, fx, fy, fz, eps, sig, c5, r;
	cut = 2.5;
	eps = 1;
	sig = 1;
	r = 1;
	
	// Zerando as forças antes de recalcular
	for (int i = 0; i < n; ++i){
		todas[i].f[0] = 0.0;
		todas[i].f[1] = 0.0;
		todas[i].f[2] = 0.0;
	}
	
	// ACHO QUE O ERRO ESTÁ AQUI
	for (int i = 0; i < n; ++i){
		for (int j = i + 1; j < n; ++j){
				dx = imin(todas[i].p[0], todas[j].p[0], lx);
				dy = imin(todas[i].p[1], todas[j].p[1], ly);
				dz = imin(todas[i].p[2], todas[j].p[2], lz);
				dist = sqrt(dx*dx + dy*dy + dz*dz);
				
				//printf("%-3d e %-3d\tDistancia; %.3lf\tcut; %.3lf\n", i+1, j+1, dist, cut);
				// Lennard-Jones
				c5 = 0.0; 
				if (dist<cut){
					c5 = aij(dist, eps, sig);
					if (dist <= 0.8){
						c5 = aij(0.8, eps, sig);
					}
				}

				// Atribuindo as componentes das forças
				fx = c5*dx;
				fy = c5*dy;
				fz = c5*dz;
				todas[i].f[0] += fx;
				todas[j].f[0] += -fx;
				todas[i].f[1] += fy;
				todas[j].f[1] += -fy;
				todas[i].f[2] += fz;
				todas[j].f[2] += -fz;
		}
	}
}
*/
