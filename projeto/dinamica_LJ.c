/*
Compilar $ gcc dinamica_LJ.c func.c -o dinamica_LJ -lm

Esse código é um teste para verificar se o cálculo de forças feito pela função forcas está correto
Ele lê o arquivo .txt criado pelo gerador
Alimente as definições com o tipo de condições iniciais utilizadas no gerador
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "func.h"

#define NA 1.0	// Carga do Sódio
#define CL -1.0	// Carga do Cloro
#define L 7.0	// Aresta da caixa
#define R 1.0	// Raio das partículas


int main (){
	// Lendo o arquivo e atribuindo o número de partículas
	char titulo[25];		// Variável auxiliar para ler o .txt
	int n;					// Número de partículas
	
	sprintf(titulo, "CI_L%.1f_R%.1f.txt", L, R);
	FILE *ark = fopen(titulo, "r");
	fscanf(ark, "%i", &n);
	
	// Criando o vetor de partículas
	particle *todas;
	todas = (particle *) malloc(n * sizeof(particle));
	
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
	
	// Escrevendo o arquivo com as forças iniciais
	forcas(todas, n, L, L, L);
	
	FILE *ark2 = fopen("forcas.txt", "w");
	for (int i = 0; i < n; ++i){
		fprintf(ark2, "%-3d %lf\t%lf\t%lf\n", i+1, todas[i].f[0], todas[i].f[1], todas[i].f[2]);
	}
	
	fclose(ark);
	fclose(ark2);
	free(todas);
	return 0;
}


