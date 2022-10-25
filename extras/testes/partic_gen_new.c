# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <math.h>

# define PI 3.1415926
# define N 10			// Número de partículas
# define L 12			// Aresta
# define R 1			// Raio
# define MIN ((-L/2)+R) // Limite inferior da caixa
# define MAX ((L/2)+R)	// Limite superior da caixa


// Para compilar com a lib math tenho que usar $ gcc partic_gen_pont.c -o partic_gen_pont -lm
// Para abrir o Jmol e verificar $ java -jar Jmol.jar
// O limite é 100 partículas em aresta 12

struct particle {
		double p[3];
	};

int main () {
	srand (time(NULL));
	
	// Declaração de funções
	double uniform (double min, double max);	
	double dist (double dx, double dy, double dz);
	struct particle check (struct particle *ptodas, int ind, double r, double min, double max);	
	
	// Verificando o volume
	double volumeparts = ((4 * PI * pow(R, 2))/3) * N;
	double volumecaixa = pow(L, 3);
	
	printf ("Volume de partículas = %f\nVolume da caixa = %f\n", volumeparts, volumecaixa);
	
	// Vetor de partículas
	struct particle *todas;
	todas = (struct particle *) malloc(N * sizeof(struct particle));

	printf ("oi 1\n");

	//struct particle *ptodas = todas;
	
	todas[0].p[0] = uniform(MIN, MAX);
	todas[0].p[1] = uniform(MIN, MAX);
	todas[0].p[2] = uniform(MAX, MAX);
	printf ("oi 1,5\n");
	
	// Gerando as coordenadas para cada partícula
	for (int i = 1; i < N; ++i){
		//++ptodas;
		//printf ("Criando particula %i\n", i);
		todas[i].p[0] = uniform(MIN, MAX);
		todas[i].p[1] = uniform(MIN, MAX);
		todas[i].p[2] = uniform(MIN, MAX);
		todas[i] = check(todas, i, R, MIN, MAX);
	}
	printf ("oi 2\n");
	// Escrita do arquivo
	FILE *ark = fopen("particulas_pont.txt", "w");
	fprintf (ark, "%i\n\n", N);
	
	for (int i = 0; i < N; ++i) {
		if (i < N/2){
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
	printf ("oi 3\n");
	
	// Checando MAIS UMA VEZ se nenhuma se sobrepôs
	for (int i = 0; i < N; ++i) {
		for (int j = i+1; j < N; ++j) {
			double dx = todas[i].p[0] - todas[j].p[0];
			double dy = todas[i].p[1] - todas[j].p[1];
			double dz = todas[i].p[2] - todas[j].p[2];
			if (dist(dx, dy, dz) <= 2 * R){
				printf("Conflito com %i e %i\n", i, j);
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


struct particle check (struct particle *todas, int ind, double r, double min, double max) {
	/*
	Função recursiva que checa a distância entre a partícula gerada e o resto delas
	*/
	
	struct particle *final = todas;
	
	
	for (int j = ind - 1; j >= 0; --j){
		//--ptodas;
		printf ("Checando a particula %i com %i\n", ind, j);
		double dx = final->p[0] - todas[j].p[0];
		double dy = final->p[1] - todas[j].p[1];
		double dz = final->p[2] - todas[j].p[2];
		if (dist(dx, dy, dz) <= 2*r) {
			printf ("recriando a particula %i\n", ind);
			final->p[0] = uniform(min, max);
			final->p[1] = uniform(min, max);
			final->p[2] = uniform(min, max);
			*final = check(final, ind, r, min, max);
		}
	}
	
	return *final;


}


