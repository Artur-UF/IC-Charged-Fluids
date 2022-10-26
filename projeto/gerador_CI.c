/*
Compilar $ gcc gerador_CI.c func.c -o gerador_CI -lm
Para abrir o Jmol e verificar $ java -jar Jmol.jar
O limite é 100 partículas em aresta 12

Esse cógido gera as as partículas em suas posições iniciais e cria um .txt com a quantidade, tipo e suas posições
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "func.h"

#define PI 3.1415926
#define N 10	// Número de partículas
#define R 1.0	// Raio das partículas
#define LX 7.0 	//
#define LY 7.0	// Arestas da caixa
#define LZ 7.0	//

int main () {
	srand (time(NULL));

	// Aresta da caixa (aqui estão todas iguais !!!!)
	double lx = LX;
	double ly = LX;
	double lz = LX;
	
	// Número  e raio das partículas
	int n = N;
	double r = R;
	
	double volumeparts = ((4 * PI * pow(r, 2))/3) * n;
	double volumecaixa = lx*ly*lz;
	
	printf ("Volume de partículas = %f\nVolume da caixa = %f\n", volumeparts, volumecaixa);
	
	
	// Limites da caixa centrada em 0 (para que as partículas inteiras entrem)
	double lx_min = (-lx/2) + r;
	double lx_max = (lx/2) - r;
	double ly_min = (-ly/2) + r;
	double ly_max = (ly/2) - r;
	double lz_min = (-lz/2) + r;
	double lz_max = (lz/2) - r;
	
	// Vetor de partículas
	particle todas[n];
	particle *ptodas = todas;
	
	todas[0].p[0] = uniform(lx_min, lx_max);
	todas[0].p[1] = uniform(ly_min, ly_max);
	todas[0].p[2] = uniform(lz_min, lz_max);
	
	// Gerando as coordenadas para cada partícula
	for (int i = 1; i < n; ++i){
		++ptodas;
		//printf ("Criando particula %i\n", i);
		todas[i].p[0] = uniform(lx_min, lx_max);
		todas[i].p[1] = uniform(ly_min, ly_max);
		todas[i].p[2] = uniform(lz_min, lz_max);
		todas[i] = check(ptodas, i, r, lx, ly, lz);
	}
	
	// Escrita do arquivo
	char titulo[25];
	sprintf(titulo, "CI_L%.1f_R%.1f.txt", lx, r);
	
	FILE *ark = fopen(titulo, "w");
	fprintf (ark, "%i\n\n", n);
	
	for (int i = 0; i < n; ++i) {
		if (i < n/2){
			fprintf (ark, "Na ");
		}else{
			fprintf (ark, "Cl ");
		}
		for (int k = 0; k < 3; ++k){
			fprintf (ark, "%lf ", todas[i].p[k]);
		}
		fprintf (ark, "\n");
	}
	fclose(ark);
	
	
	// Checando MAIS UMA VEZ se nenhuma se sobrepôs
	for (int i = 0; i < n; ++i) {
		for (int j = i+1; j < n; ++j) {
			double dx = todas[i].p[0] - todas[j].p[0];
			double dy = todas[i].p[1] - todas[j].p[1];
			double dz = todas[i].p[2] - todas[j].p[2];
			if (dist(dx, dy, dz) <= 2 * r){
				printf("Conflito com %i e %i\n", i, j);
			}
		}
	}
	
	return 0;
}

