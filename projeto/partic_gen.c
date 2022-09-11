# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <math.h>

double uniform (double min, double max) {
	/*
	Função que gera um número aleatório em uma distribuição uniforme
	*/

	double random  = ((double) rand()) / RAND_MAX;
	double range = (max - min) * random;
	double n = range + min;	
	
	return n;
}

double dist (double dx, double dy, double dz){
	return sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));
}


int main () {
	srand (time(NULL));
		
	struct particle {
		double p[3];
	};
	// Aresta da caixa
	double l = 10;
	
	// Número  e raio das partículas
	int n = 10;
	double r = 0.5;
	
	// Limites da caixa centrada em 0 (para que as partículas inteiras entrem)
	double min = (-l/2) + r;
	double max = (l/2) - r;
	
	// Vetor de partículas
	struct particle todas[n];
	
	
	// !!! VERIFICA RECURSIVAMENTE !!!
	for (int i = 0; i < n; ++i){
		todas[i].p[0] = uniform(min, max);
		todas[i].p[1] = uniform(min, max);
		todas[i].p[2] = uniform(min, max);
		if (i >= 1){
			for (int j = i - 1; j > 0; --j){
				double dx = todas[i].p[0] - todas[j].p[0];
				double dy = todas[i].p[1] - todas[j].p[1];
				double dz = todas[i].p[2] - todas[j].p[2];
				if (dist(dx, dy, dz) < r) {
					todas[i].p[0] = uniform(min, max);
					todas[i].p[1] = uniform(min, max);
					todas[i].p[2] = uniform(min, max);
				}
			}
		}
	}
		
	printf ("x    y    z\n");
	for (int i = 0; i < n; ++i) {
		for (int k = 0; k < 3; ++k){
			printf ("%.2f ", todas[i].p[k]);
		}
		printf ("\n");
	}
	
	return 0;
}

