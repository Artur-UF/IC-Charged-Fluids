# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <math.h>
#include "func.h"

# define PI 3.1415926

// Compilar $ gcc partic_gen_pont.c func.c -o partic_gen_pont -lm
// Para abrir o Jmol e verificar $ java -jar Jmol.jar
// O limite é 100 partículas em aresta 12

int main () {
	srand (time(NULL));

	// Aresta da caixa
	double l = 7;
	
	// Número  e raio das partículas
	int n = 10;
	double r = 1;
	
	double volumeparts = ((4 * PI * pow(r, 2))/3) * n;
	double volumecaixa = pow(l, 3);
	
	printf ("Volume de partículas = %f\nVolume da caixa = %f\n", volumeparts, volumecaixa);
	
	
	// Limites da caixa centrada em 0 (para que as partículas inteiras entrem)
	double min = (-l/2) + r;
	double max = (l/2) - r;
	
	// Vetor de partículas
	struct particle todas[n];
	struct particle *ptodas = todas;
	
	todas[0].p[0] = uniform(min, max);
	todas[0].p[1] = uniform(min, max);
	todas[0].p[2] = uniform(min, max);
	
	// Gerando as coordenadas para cada partícula
	for (int i = 1; i < n; ++i){
		++ptodas;
		//printf ("Criando particula %i\n", i);
		todas[i].p[0] = uniform(min, max);
		todas[i].p[1] = uniform(min, max);
		todas[i].p[2] = uniform(min, max);
		todas[i] = check(ptodas, i, r, min, max);
	}
	
	// Escrita do arquivo
	char titulo[25];
	sprintf(titulo, "CI_L%.1f_R%.1f.txt", l, r);
	
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

