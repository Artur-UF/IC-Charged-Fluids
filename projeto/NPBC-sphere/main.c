/*
$ gcc main.c func.c -lm
Para abrir o Jmol e verificar $ java -jar Jmol.jar

Programa que cria uma esfera com partículas em posições aleatórias e realiza uma dinâmica de Lennard-Jones
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
#include "func.h"

//*-*-*-*-*-*-*-*-*-*-*PARÂMETROS*-*-*-*-*-*-*-*-*-
#define R 1.		// Raio das particulas
#define RS (8.*R)	// Raio da esfera	
#define N 100		// Número de partículas
#define FRIC 0.1	// Coeficiente de fricção
#define LB (2.*R)	// Lambda B
#define DT 0.005	// Delta de tempo
#define TF 30.		// Tempo final
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

int main (){
	clock_t tic = clock();
	int seed = time(NULL); 
	srand(seed);

	// Criação do vetor de partículas
	particle *todas;
	todas = (particle *) malloc(N * sizeof(particle));
	
	// É firula, fiz pra comparar o volume da esfera com o volume das partículas
	double volT, volP, pi = acos(-1);
	volT = (3./4.)*(RS*RS*RS)*pi;
	volP = N * (3./4.)*(R*R*R)*pi;
	printf("Volume da esfera: %lf\nVolume das partículas: %lf\n", volT, volP);

	// Criando o arquivo de saída da dinâmica
	char pasta[35], lixo[35], arkinfo[35];
	int test = 0;
	sprintf(pasta, "LJ_RS%.1lf_TF%.1lf_LB%.1lf", RS, TF, LB);
	if (mkdir(pasta, 0777) == -1){
		printf("Limpando a pasta\n");
		sprintf(lixo, "LJ_RS%.1lf_TF%.1lf_LB%.1lf/animLJ.txt", RS, TF, LB);
		sprintf(arkinfo, "LJ_RS%.1lf_TF%.1lf_LB%.1lf/info.txt", RS, TF, LB);
		remove(arkinfo);
		remove(lixo);
	}
	
	// Gerando as partículas
	gerador(todas, N, RS, R);
	
	// Escrita do arquivo de posições iniciais
	ciFile(todas, N, RS, TF, LB);
	
	// Dinâmica<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<TÁ DANDO CERTO? TESTA MAIS!!!!!!!!!!!!!
	dinamica(todas, N, RS, R, FRIC, LB, TF, DT);
	
	clock_t toc = clock();
	double time = (double)(toc - tic)/CLOCKS_PER_SEC;
	
	checador(todas, N, RS, R);
	
	// Escrevendo o arquivo com informações<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<NÃO SERIA LEGAL UMA FUNÇÃO RA ISSO?
	sprintf(arkinfo, "LJ_RS%.1lf_TF%.1lf_LB%.1lf/info.txt", RS, TF, LB);
	FILE *infos = fopen(arkinfo, "w");
	fprintf(infos, "#define R %.1lf		// Raio das particulas\n", R);
	fprintf(infos, "#define RS %.1lf	// Raio da esfera\n", RS);
	fprintf(infos, "#define N %d		// Número de partículas\n", N);
	fprintf(infos, "#define FRIC %.1lf	// Coeficiente de fricção\n", FRIC);
	fprintf(infos, "#define LB %.1lf	// Lambda B\n", LB);
	fprintf(infos, "#define DT %.4lf	// Delta de tempo\n", DT);
	fprintf(infos, "#define TF %.2lf	// Tempo final\n", TF);
	fprintf(infos, "Número de passos = %.0lf\n", TF/DT);
	fprintf(infos, "Tempo de execução: %lfs\n", time);
	fprintf(infos, "Seed aleatória: %d\n", seed);
	
	fclose(infos);
	return 0;
}
