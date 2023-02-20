#include <stdio.h>
#include <stdlib.h>

typedef struct {
	// Estrutura com os atributos possíveis de uma partícula
	double p[3];
	double v[3];
	double f[3];
	double carga;
	double gaussian[3]; // Atributo para ajudar na integração
}particle;


int main (){
	
	int n = 100;
	
	particle *todas;
	todas = (particle *) malloc(n * sizeof(particle));

	FILE *ark = fopen("LJ_RS10.0_TF30.0_LB7.0/passos/1.bin", "rb");

	fread(todas, sizeof(particle), n, ark);

	printf("(%.2lf, %.2lf, %.2lf)\n", todas[99].p[0], todas[99].p[1], todas[99].p[2]);

	return 0;
}
