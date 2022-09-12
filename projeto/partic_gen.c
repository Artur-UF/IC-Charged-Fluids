# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <math.h>

// Para compilar com a lib math tenho que usar $ gcc <nome.c> -o <nome> -lm


struct particle {
		double p[3];
	};

int main () {
	srand (time(NULL));
	
	double uniform (double min, double max);	
	double dist (double dx, double dy, double dz);
	struct particle check (struct particle todas[], int ind, double r, double min, double max);	
	
	// Aresta da caixa
	double l = 200;
	
	// Número  e raio das partículas
	int n = 100;
	double r = 0.5;
	
	// Limites da caixa centrada em 0 (para que as partículas inteiras entrem)
	double min = (-l/2) + r;
	double max = (l/2) - r;
	
	// Vetor de partículas
	struct particle todas[n];
	
	// Gerando as coordenadas para cada partícula
	for (int i = 0; i < n; ++i){
		todas[i].p[0] = uniform(min, max);
		todas[i].p[1] = uniform(min, max);
		todas[i].p[2] = uniform(min, max);
		if (i >= 1){
			todas[i] = check(todas, i, r, min, max);
		}
	}
	
	// Escrita do arquivo
	FILE *ark = fopen("particulas.txt", "w");
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
			if (dist(dx, dy, dz) < r){
				printf("Se fudeu");
			}
		}
	}
	
	return 0;
}


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
	/*
	Calcula a distância entre duas partículas em 3D
	*/
	return sqrt(pow(dx, 2) + pow(dy, 2) + pow(dz, 2));
}


struct particle check (struct particle todas[], int ind, double r, double min, double max) {
	/*
	Função recursiva que checa a distância entre a partícula gerada e o resto delas
	*/
	for (int j = ind - 1; j >= 0; --j){
		double dx = todas[ind].p[0] - todas[j].p[0];
		double dy = todas[ind].p[1] - todas[j].p[1];
		double dz = todas[ind].p[2] - todas[j].p[2];
		if (dist(dx, dy, dz) > r) {
			return todas[ind];
		} else {
			todas[ind].p[0] = uniform(min, max);
			todas[ind].p[1] = uniform(min, max);
			todas[ind].p[2] = uniform(min, max);
			check(todas, ind, r, min, max);
		}
	}


}


