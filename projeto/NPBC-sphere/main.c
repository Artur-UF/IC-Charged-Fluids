/*
$ gcc main.c func.c -lm

Programa que cria uma esfera com partículas em posições aleatórias e realiza uma dinâmica de Lennard-Jones
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "func.h"

#define R 1.		// Raio das particulas
#define RS (20.*R)	// Raio da esfera	
#define N 50		// Número de partículas

int main (){

	// Criação do vetor de partículas
	particle *todas;
	todas = (particle *) malloc(N * sizeof(particle));
	
	double volT, volP, pi = acos(-1);
	volT = (3./4.)*(RS*RS*RS)*pi;
	volP = N * (3./4.)*(R*R*R)*pi;
	printf("Volume da esfera: %lf\nVolume das partículas: %lf\n", volT, volP);
	
	gerador(todas, N, RS, R);
	/*
	for (int i = 0; i < N; ++i){
		printf("x:%-5.2lf\ty:%5.2lf\tz:%5.2lf", todas[i].p[0], todas[i].p[1], todas[i].p[2]);
	}
	*/
	return 0;
}
