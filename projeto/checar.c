/*
Compilar: $ gcc checar.c func.c -o checar -lm

Código criado para checar se a dinâmica não está fazendo partículas colidirem
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
		sprintf(titulo, "LJ_L%.1lf_TF%.1lf/%d.bin", L, TF, count);
		FILE *ark = fopen(titulo, "rb");
		
		fread(todas, sizeof(particle), n, ark);
		
		// Checando MAIS UMA VEZ se nenhuma se sobrepôs
		double dx, dy, dz, dtotal;
		for (int i = 0; i < n; ++i) {
			//printf("%d\t%.2lf\t%.2lf\t%.2lf\n", i, todas[i].p[0], todas[i].p[1], todas[i].p[2]);
			for (int j = i+1; j < n; ++j) {
				dx = todas[i].p[0] - todas[j].p[0];
				dy = todas[i].p[1] - todas[j].p[1];
				dz = todas[i].p[2] - todas[j].p[2];
				dtotal = dist(dx, dy, dz);
				if (dtotal <= 2 * R){
					printf("Passo = %-2d\tAproximação (%-2d e %-2d)\tDistancia = %.3lf\n", count, i, j, dtotal);
				}
			}
		}
		printf("-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");		
		fclose(ark);
	}

	free(todas);
	return 0;
}


