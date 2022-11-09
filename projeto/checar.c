/*
Compilar: $ gcc checar.c func.c -o checar -lm

Código que verifica se as partículas colidem ou saem da caixa.
Ele abre a pasta gerada pelo dinamica_LJ.c referente aos parâmetros definidos em #define
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
#include "func.h"

//*-*-*-*-*-*-*PARÂMETROS*-*-*-*-*-*-*-*-*-*-*-*-*-*
#define NA 1.			// Carga do Sódio
#define CL -1.			// Carga do Cloro
#define L 15.			// Aresta da caixa
#define R 1.			// Raio das partículas
#define DT 0.005		// Delta de tempo
#define FRIC 0.1		// Coeficiente de Fricção
#define TF 10.			// Tempo final
#define CHECKPOINT 10.	// Número de passos pulados
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

int main(){
	int n = 100;

	particle *todas;
	todas = (particle *) malloc(n * sizeof(particle));
	
	char titulo[30];
	
	for (int count = 0; count < TF/DT; count += CHECKPOINT){ 
		// Abre o arquivo de cada passo temporal
		sprintf(titulo, "LJ_L%.1lf_TF%.1lf/%d.bin", L, TF, count);
		FILE *ark = fopen(titulo, "rb");
		
		fread(todas, sizeof(particle), n, ark);
		printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-Passo = %-2d\n", count);	
		
		double dx, dy, dz, dtotal, x, y, z;
		for (int i = 0; i < n; ++i) {
			// Verifica se alguma sai da caixa			
			x = todas[i].p[0];
			y = todas[i].p[1];
			z = todas[i].p[2];
			
			if (fabs(x) >= L/2.){
				printf("Partícula %-2d está em x = %.3lf\n", i, x);
			}
			if (fabs(y) >= L/2.){
				printf("Partícula %-2d está em y = %.3lf\n", i, y);
			}
			if (fabs(z) >= L/2.){
				printf("Partícula %-2d está em z = %.3lf\n", i, z);
			}

			// Verifica alguma aproximação
			for (int j = i+1; j < n; ++j) {
				dx = todas[i].p[0] - todas[j].p[0];
				dy = todas[i].p[1] - todas[j].p[1];
				dz = todas[i].p[2] - todas[j].p[2];
				dtotal = dist(dx, dy, dz);
				if (dtotal <= R){ // Distancia que eu quero verificar
					printf("Aproximação (%-2d e %-2d)\tDistancia = %.3lf\n", i, j, dtotal);
				}
			}
		}
			
		fclose(ark);
	}

	free(todas);
	return 0;
}


