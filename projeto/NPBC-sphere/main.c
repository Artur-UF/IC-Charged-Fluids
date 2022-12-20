/*
$ gcc main.c func.c -lm
Para abrir o Jmol e verificar $ java -jar Jmol.jar

Programa que cria uma esfera com partículas em posições aleatórias e realiza uma dinâmica de Lennard-Jones
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "func.h"

#define R 1.		// Raio das particulas
#define RS (10.*R)	// Raio da esfera	
#define N 100		// Número de partículas


int main (){
	srand(time(NULL));

	// Criação do vetor de partículas
	particle *todas;
	todas = (particle *) malloc(N * sizeof(particle));
	
	// É firula, fiz pra comparar o volume da esfera com o volume das partículas
	double volT, volP, pi = acos(-1);
	volT = (3./4.)*(RS*RS*RS)*pi;
	volP = N * (3./4.)*(R*R*R)*pi;
	printf("Volume da esfera: %lf\nVolume das partículas: %lf\n", volT, volP);
	
	// Gerando as partículas
	gerador(todas, N, RS, R);
	printf("Deu certo!\n");
	
	// Escrita do arquivo de posições iniciais
	ciFile(todas, N, RS, R);
	
	forcas(todas, N);
	
	return 0;
}
