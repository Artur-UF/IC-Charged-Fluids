#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/stat.h>
#include "func.h"

//*-*-*-*-*-*-*PARÂMETROS*-*-*-*-*-*-
#define NA 1.0		// Carga do Sódio
#define CL -1.0		// Carga do Cloro
#define L 15.0		// Aresta da caixa
#define R 1.0		// Raio das partículas
#define DT 0.005	// Delta de tempo
#define FRIC 0.1	// Coeficiente de Fricção
#define TF 1		// Tempo final
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

// Compilar: $ gcc dinamica_LJ.c func.c -o dinamica_LJ -lm

int main (){
	// configuração específica da caixa
	double lx, ly, lz;
	lx = L;
	ly = L;
	lz = L;

	// Lendo o arquivo e atribuindo o número de partículas
	char titulo[25];		// Variável auxiliar para ler o .txt
	int n;					// Número de partículas
	
	sprintf(titulo, "CI_L%.1f_R%.1f.txt", L, R);
	FILE *ark = fopen(titulo, "r");
	fscanf(ark, "%i", &n);
	
	// Criando o vetor de partículas
	particle *todas;
	todas = (particle *) malloc(n * sizeof(particle));
	
	// Leitura e atribuição de valores iniciais
	char elemento[5];
	fgets(elemento, 2, ark);
	fgets(elemento, 2, ark);
	for (int i = 0; i < n; ++i){
		fgets(elemento, 3, ark);
		if (elemento == "Na"){
			todas[i].carga = NA;
		}else{
			todas[i].carga = CL;
		}
		fscanf(ark, "%lf %lf %lf", &todas[i].p[0], &todas[i].p[1], &todas[i].p[2]);
		todas[i].v[0], todas[i].v[1], todas[i].v[2] = .0, .0, .0;
		todas[i].f[0], todas[i].f[1], todas[i].f[2] = .0, .0, .0;
		fgets(elemento, 2, ark);
		fgets(elemento, 2, ark);
	}
	
	// Criando o arquivo de saída da dinâmica<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<TESTA
	char pasta[50];
	spprintf(pasta, "LJ_L%.1lf_TF%.1lf", L, TF);
	if (mkdir(pasta, 0777) == -1){
		printf("Erro na pasta\n");
		return 1;
	}
	
	//Loop Temporal
	double con, c0, c1, c2, desv_r, desv_v, cvv, cvv2, xold, yold, zold;
	con = FRIC*DT;
	c0 = exp(-con);
	c1 = (1-c0)/con;
	c2 = (1-c1)/con;
	desv_r = DT*sqrt((1/con) * (2 - ((1/con) * (3 - (4*c0) + (c0*c0)))));
	desv_v = sqrt(1-(c0*c0));
	cvv = (DT/con/desv_v/desv_r) * (1-co)*(1-c0);
	cvv2 = sqrt(1 - (cvv*cvv));
	dt2 = DT*DT
	
	int counter = 0;
	for (double t = 0; t < TF; t += DT){
		// Cálculo inicial das forças
		forcas(todas, n, lx, ly, lz);
		
		// Loop do espaço sobre todas as partículas
		for (int j = 0; j < n; ++j){
			xold = todas[j].p[0];
			yold = todas[j].p[1];
			zold = todas[j].p[2];
			todas[j].gaussian[0] = gausran();
			todas[j].gaussian[1] = gausran();
			todas[j].gaussian[2] = gausran();
			
			// Passo no espaço
			todas[j].p[0] += c1 * DT * todas[j].v[0] + c2 * dt2 * todas[j].f[0] + todas[j].gaussian[0] * desv_r;
			todas[j].p[1] += c1 * DT * todas[j].v[1] + c2 * dt2 * todas[j].f[1] + todas[j].gaussian[1] * desv_r;
			todas[j].p[2] += c1 * DT * todas[j].v[2] + c2 * dt2 * todas[j].f[2] + todas[j].gaussian[2] * desv_r;
			
			// PBC
			if (fabs(todas[j].p[0]) > lx/2.){
				todas[j].p[0] = lx * (fabs(todas[j].p[0])/todas[j].p[0]);
			}
			if (fabs(todas[j].p[1]) > ly/2.){
				todas[j].p[1] = ly * (fabs(todas[j].p[1])/todas[j].p[1]);
			}
			if (fabs(todas[j].p[2]) > lz/2.){
				todas[j].p[2] = lz * (fabs(todas[j].p[2])/todas[j].p[2]);
			}
		}
		// Cálculo final das forças
		forcas(todas, n, lx, ly, lz);
		
		// Loop da velocidade sobre todas partículas
		for (int j = 0; j < n; ++j){
			// vx
			todas[j].v[0] = c0 * todas[j].v[0] + (c1 - c2) * DT * todas[j].f[0] + 
			c2 * DT * todas[j].f[[0] + desv_v * (cvv * todas[j].gaussian[0] + cvv2 * gausran());
			// vy
			todas[j].v[1] = c0 * todas[j].v[1] + (c1 - c2) * DT * todas[j].f[1] + 
			c2 * DT * todas[j].f[[1] + desv_v * (cvv * todas[j].gaussian[1] + cvv2 * gausran());
			// vz
			todas[j].v[2] = c0 * todas[j].v[2] + (c1 - c2) * DT * todas[j].f[2] + 
			c2 * DT * todas[j].f[[2] + desv_v * (cvv * todas[j].gaussian[2] + cvv2 * gausran());
		}
		
		// Escrevendo arquivo do passo <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<TESTA SALVANDO UM VETOR E AS PARTICULAS
		if (fmod(counter, 10) == 0){
			char passo = sprintf("%s/1", pasta);
			FILE *in = fopen(passo, "wb");
			
		}
		
		++counter
	}
	
	fclose(ark);
	free(todas);
	return 0;
}

