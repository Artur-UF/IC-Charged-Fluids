#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
#include "func.h"

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


particle check(particle *todas, particle teste, int i, double rs, double ri, double d){
	/*
	Função recursiva que checa a distância entre a partícula gerada e o resto delas
	*/
	double x = teste.p[0], y = teste.p[1], z = teste.p[2];
	double rrs = rs - d/2.;
	
	for (int j = i; j >= 0; --j){
		double dx = x - todas[j].p[0];
		double dy = y - todas[j].p[1];
		double dz = z - todas[j].p[2];
		double dpart = dist(dx, dy, dz);
		if (dpart <= d) {
			//printf("Conflito entre (%d, %d)\n", i+1, j);
			teste.p[0] = uniform(-rrs, rrs);
			teste.p[1] = uniform(-rrs, rrs);
			teste.p[2] = uniform(-rrs, rrs);
			teste = check(todas, teste, i, rs, ri, d);
		}
	}
	return teste;
}


void gerador(particle *todas, int n, double rs, double ri, double d){
	double dc;										// distância entre a partícula e o centro do sistema
	double rrs = rs - d/2., rri = ri + d/2.;		// Raios relativos ao centro das particulas

	particle teste;
	
	// Partícula simulando centro do sistema carregado	
	todas[n].p[0] = 0.;
	todas[n].p[1] = 0.;	
	todas[n].p[2] = 0.;
	
	
	// Primeira partícula gerada
	todas[0].p[0] = uniform(-(rrs + rri)/2., (rrs + rri)/2.);
	todas[0].p[1] = uniform(-(rrs + rri)/2., (rrs + rri)/2.);
	todas[0].p[2] = uniform(-(rrs + rri)/2., (rrs + rri)/2.);	
	
	
	int i = 0;
	
	while(i <= n-2){
		teste.p[0] = uniform(-rrs, rrs);
		teste.p[1] = uniform(-rrs, rrs);
		teste.p[2] = uniform(-rrs, rrs);
		teste = check(todas, teste, i, rs, ri, d);
		dc = dist(teste.p[0], teste.p[1], teste.p[2]);
		if(dc < rrs && dc > rri){
			++i;
			todas[i].p[0] = teste.p[0];
			todas[i].p[1] = teste.p[1];
			todas[i].p[2] = teste.p[2];
			printf("Particula %d criada\n", i);
		}
	}
	
	n = n+1;
	for(int i = 0; i < n; ++i){
		todas[i].v[0] = 0.;
		todas[i].v[1] = 0.;
		todas[i].v[2] = 0.;
		
		todas[i].f[0] = 0.;
		todas[i].f[1] = 0.;
		todas[i].f[2] = 0.;
		if(i < (n + CENT)/2){
			todas[i].carga = NA;
		}
		if(i >= (n + CENT)/2){
			todas[i].carga = CL;
		}
	}
	todas[n-1].carga = CENT;
}


void ciFile(particle *todas, int n, double rs, double tf, double lb){
	// Escrita do arquivo
	char titulo[35];
	sprintf(titulo, "LJ_RS%.1lf_TF%.1lf_LB%.1lf/CI.txt", rs, tf, lb);
	
	FILE *ark = fopen(titulo, "w");
	fprintf (ark, "%i\n\n", n+1);
	
	for (int i = 0; i <= n; ++i) {
		if (i < (n + CENT)/2 && i != n){
			fprintf (ark, "Na ");
		}
		if(i >= (n + CENT)/2 && i != n){
			fprintf (ark, "Cl ");
		}
		if(i == n){
			fprintf (ark, "Cla ");
		}
		fprintf(ark, "%.1f ", todas[i].carga);
		for (int k = 0; k < 3; ++k){
			fprintf (ark, "%lf ", todas[i].p[k]);
		}
		fprintf (ark, "\n");
	}
	fclose(ark);
}

void forcas(particle *todas, int n, double d, double lb){
	// Constantes para o Lennard-Jones
	double cut, c5, dx, dy, dz, dist, fx = 0, fy = 0, fz = 0;
	cut = pow(2., 1./6.); // Esse corte é pequeno por isso não gera força imadiatamente
	
	// Constantes para a Força eletrostática
	double pfel, cadm = lb/d;	// Constante adimensionalizadora
	
	// Zerando as forças antes de recalcular
	for (int i = 0; i < n; ++i){
		todas[i].f[0] = 0.0;
		todas[i].f[1] = 0.0;
		todas[i].f[2] = 0.0;
	}
	
	// Loop entre pares de partículas
	for (int i = 0; i <= n; ++i){
		for (int j = i + 1; j <= n; ++j){
				
				if(j == 100){
					//printf("força entre [%d(%.1f), %d(%.1f)]\n", i, todas[i].carga, j, todas[j].carga);
				}
				dx = todas[i].p[0] - todas[j].p[0];
				dy = todas[i].p[1] - todas[j].p[1];
				dz = todas[i].p[2] - todas[j].p[2];
				dist = sqrt(dx*dx + dy*dy + dz*dz);
				
				// Lennard-Jones
				c5 = 0.0; 
				if (dist<cut){
					c5 = 5.*( - 6./pow(dist,7) + 12./pow(dist,13));
					if (dist <= 0.8){
						c5 = 5.*( - 6./pow(0.8,7) + 12./pow(0.8,13));
					}
				}

				// Atribuindo as componentes das forças
				pfel = cadm*(todas[i].carga*todas[j].carga)/(pow(dist, 3)); // parametro da força eletrostática
								
				// Somando as forças de Lennard-Jones
				fx += c5*dx/dist;
				fy += c5*dy/dist;
				fz += c5*dz/dist;
				// Somando as forças Eletrostáticas
				fx += pfel*dx;
				fy += pfel*dy;
				fz += pfel*dz;
				
				// Particula i:
				todas[i].f[0] += fx;
				todas[i].f[1] += fy;
				todas[i].f[2] += fz;
				// Partícula j:				
				todas[j].f[0] += -fx;
				todas[j].f[1] += -fy;
				todas[j].f[2] += -fz;
				
				fx = 0;
				fy = 0;
				fz = 0;
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


void checador(particle *todas, int n, double rs, double d){
	double rrs = rs - d/2.;		// Raio relativo ao centro das particulas
	// Checando se está fora da esfera
	for(int j = 0; j < n; ++j){
		double distancia = dist(todas[j].p[0], todas[j].p[1], todas[j].p[2]);
		if(distancia >= rrs){
			printf("d(%d) = %.3lf\n", j, distancia);		
		}
	}
	
	// Checando se está sobrepondo alguma partícula
	for(int i = 0; i < n; ++i){
		for (int j = i + 1; j < n; ++j){
			double dx = todas[i].p[0] - todas[j].p[0];
			double dy = todas[i].p[1] - todas[j].p[1];
			double dz = todas[i].p[2] - todas[j].p[2];
			double dpart = dist(dx, dy, dz);
			if (dpart <= d) {
				printf("Conflito entre (%d, %d): d = %.3lf\n", i, j, dpart);
			}
		}
	}
}


void dinamica(particle *todas, int n, double rs, double ri, double d, double fric, double lb, double tf, double dt){
	double rrs = rs - d/2., rri = ri + d/2.;		// Raios relativos ao centro das particulas
	
	//Loop Temporal
	double con, c0, c1, c2, desv_r, desv_v, cvv, cvv2, dt2, ds;
	con = fric*dt;
	c0 = exp(-con);
	c1 = (1-c0)/con;
	c2 = (1-c1)/con;
	desv_r = dt*sqrt((1/con) * (2 - ((1/con) * (3 - (4*c0) + (c0*c0)))));
	desv_v = sqrt(1-(c0*c0));
	cvv = (dt/con/desv_v/desv_r) * (1-c0)*(1-c0);
	cvv2 = sqrt(1 - (cvv*cvv));
	dt2 = dt*dt;
	
	// Aqui cria o arquivo que será usado para a animação
	char passo[35];
	sprintf(passo, "LJ_RS%.1lf_TF%.1lf_LB%.1lf/animLJ.txt", rs, tf, lb);
	
	FILE *in = fopen(passo, "w");
	
	
	// Contadores auxiliares para o loop
	int counter = 0;								// Conta o número e passos
	
	int contanim = 0;								// Conta o número de frames a serem salvos em .txt
	int framesanim = 700;							// O número de frames a serem salvos em .txt
	double limiteanim = tf/dt - (framesanim + 1);	// Número do passo a começar a salvar a animação
	
	
	int contbin = 0;								// Conta o número de frames a serem salvos em .bin
	int framesbin = 1500;							// O número de frames a serem salvos para a animação
	double limitebin = tf/dt - (framesbin + 1);		// Número do passo a começar a salvar para arquivo .bin
	
	
	// Cria a pasta para os passos
	char passos[35], npasso[35];
	
	sprintf(passos, "LJ_RS%.1lf_TF%.1lf_LB%.1lf/passos", rs, tf, lb);
	if (mkdir(passos, 0777) == -1){
		printf("Limpando a passos\n");
		for(int i = 1; i <= framesbin; ++i){
			sprintf(npasso, "LJ_RS%.1lf_TF%.1lf_LB%.1lf/passos/%d.bin", rs, tf, lb, i);
			remove(npasso);
		}
	}
	
	
	for (double t = 0; t <= tf; t += dt){
		// Cálculo inicial das forças
		forcas(todas, n, d, lb);
		
		// Loop do espaço sobre todas as partículas
		for (int j = 0; j < n; ++j){
			todas[j].gaussian[0] = gausran();
			todas[j].gaussian[1] = gausran();
			todas[j].gaussian[2] = gausran();

			// Passo no espaço
			todas[j].p[0] += c1 * dt * todas[j].v[0] + c2 * dt2 * todas[j].f[0] + todas[j].gaussian[0] * desv_r;
			todas[j].p[1] += c1 * dt * todas[j].v[1] + c2 * dt2 * todas[j].f[1] + todas[j].gaussian[1] * desv_r;
			todas[j].p[2] += c1 * dt * todas[j].v[2] + c2 * dt2 * todas[j].f[2] + todas[j].gaussian[2] * desv_r;
			
			if(todas[j].carga == 10.) printf("Mexi na última (passo espaço)\n"); // Pra ver se ele ta mexendo na partícula central
			
			// NPBC
			ds = dist(todas[j].p[0], todas[j].p[1], todas[j].p[2]);
			if(ds >= rrs || ds <= rri){
				todas[j].v[0] *= -1.;
				todas[j].v[1] *= -1.;
				todas[j].v[2] *= -1.;
			}
		}
		// Cálculo final das forças
		forcas(todas, n, d, lb);
		
		// Loop da velocidade sobre todas partículas
		for (int j = 0; j < n; ++j){
			if(todas[j].carga == 10.) printf("Mexi na última (passo vel)\n"); // Pra ver se ele ta mexendo na partícula central
			// Vx
			todas[j].v[0] = c0 * todas[j].v[0] + (c1 - c2) * dt * todas[j].f[0] + 
			c2 * dt * todas[j].f[0] + desv_v * (cvv * todas[j].gaussian[0] + cvv2 * gausran());
			// Vy
			todas[j].v[1] = c0 * todas[j].v[1] + (c1 - c2) * dt * todas[j].f[1] + 
			c2 * dt * todas[j].f[1] + desv_v * (cvv * todas[j].gaussian[1] + cvv2 * gausran());
			// Vz
			todas[j].v[2] = c0 * todas[j].v[2] + (c1 - c2) * dt * todas[j].f[2] + 
			c2 * dt * todas[j].f[2] + desv_v * (cvv * todas[j].gaussian[2] + cvv2 * gausran());
		}
		
		// Esse salva em .txt pra fazer a animação
		if (counter >= limiteanim && counter < limiteanim + framesanim){
			fprintf(in, "%d\n\n", n+1);
			for (int i = 0; i <= n; ++i){
				if (i < (n + CENT)/2 && i != n){
					fprintf (in, "Na ");
				}
				if(i >= (n + CENT)/2 && i != n){
					fprintf (in, "Cl ");
				}
				if(i  == n){
					fprintf(in, "Cla ");
				}
				fprintf(in, "%lf %lf %lf\n", todas[i].p[0], todas[i].p[1], todas[i].p[2]);
			}
			fprintf(in, "\n");
			++contanim;
		}
		
		// Esse salva em binário
		// Escrevendo arquivo do passo
		if (counter >= limitebin && counter < limitebin + framesbin){
			++contbin;
			char passo[35];
			sprintf(passo, "LJ_RS%.1lf_TF%.1lf_LB%.1lf/passos/%d.bin", rs, tf, lb, contbin);
			
			FILE *inbin = fopen(passo, "wb");
			
			fwrite(todas, sizeof(particle), n, inbin);
			fclose(inbin);
		}

		++counter;
	}
	fclose(in); // isso eu  só uso quando to salvando em .txt

}
