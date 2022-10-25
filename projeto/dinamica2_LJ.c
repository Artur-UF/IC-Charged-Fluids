#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "func.h"

//*-*-*-*-*-*-*CONSTANTES*-*-*-*-*-*-
#define NA 1.0		// Carga do Sódio
#define CL -1.0		// Carga do Cloro
#define L 15.0		// Aresta da caixa
#define R 1.0		// Raio das partículas
#define DT 0.005	// Delta de tempo
#define FRIC 0.1	// Coeficiente de Fricção
#define TF 1		// Tempo final
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

// Compilar: $ gcc dinamica_LJ.c func.c -o dinamica_LJ -lm

int main (){
	// Lendo o arquivo e atribuindo o número de partículas
	char titulo[25];
	int n;
	sprintf(titulo, "CI_L%.1f_R%.1f.txt", L, R);
	FILE *ark = fopen(titulo, "r");
	fscanf(ark, "%i", &n);
	
	// Criando o vetor de partículas
	struct particle *todas;
	todas = (struct particle *) malloc(n * sizeof(struct particle));
	
	// Leitura e atribuição de valores iniciais
	char elemento[5];
	fgets(elemento, 2, ark);
	fgets(elemento, 2, ark);
	for (int i = 0; i < n; ++i){
		fgets(elemento, 3, ark);
		if (elemento == "Na"){
			todas[i].carga = NA;
		}else{
			todas[i].carga = CL;
		}
		fscanf(ark, "%lf %lf %lf", &todas[i].p[0], &todas[i].p[1], &todas[i].p[2]);
		todas[i].v[0], todas[i].v[1], todas[i].v[2] = .0, .0, .0;
		todas[i].f[0], todas[i].f[1], todas[i].f[2] = .0, .0, .0;
		fgets(elemento, 2, ark);
		fgets(elemento, 2, ark);
	}
	
	//Loop Temporal
	double con, c0, c1, c2, desv_r, desv_v, cvv, cvv2, xold, yold, zold, ;
	con = FRIC*DT;
	c0 = exp(-con);
	c1 = (1-c0)/con;
	c2 = (1-c1)/con;
	desv_r = DT*sqrt((1/con) * (2 - ((1/con) * (3 - (4*c0) + (c0*c0)))));
	desv_v = sqrt(1-(c0*c0));
	cvv = (DT/con/desv_v/desv_r) * (1-co)*(1-c0);
	
	// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< VOCÊ COMEÇOU A FAZER ISSO !!!!!!!
	for (int t = 0; t < TF; t += DT){
		
	}
	
	fclose(ark);
	free(todas);
	return 0;
}

