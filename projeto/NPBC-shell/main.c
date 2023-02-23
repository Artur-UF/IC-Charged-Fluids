/*
$ gcc main.c func.c -lm
Para abrir o Jmol e verificar $ java -jar Jmol.jar

Programa que cria duas cascas esféricas com partículas em posições aleatórias  entre elas e realiza uma 
dinâmica de Lennard-Jones com forças eletrostáticas entre partículas.

Esse programa utiliza os parâmetros para realizar a dinâmica e ao final cria uma pasta cujo título
identifica qual o raio da esfera, tempo total da simulação e Lambda B utilizados como parâmetros.
Dentro dessa pasta são criados o arquivo de condições iniciais, com as posições iniciais das partículas, 
um arquivo para a animação no Jmol com diversos frames e um arquivo com informações gerais sobre a simulação
rodada.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
#include "func.h"

//*-*-*-*-*-*-*-*-*-*-*PARÂMETROS*-*-*-*-*-*-*-*-*-
#define D 4.		// Diametro das particulas
#define RS (20.)	// Raio da esfera externa
#define RI (RS/2.)	// Raio da esfera interna
#define N 90		// Número de partículas
#define FRIC 0.1	// Coeficiente de fricção
#define LB (7.20)	// Lambda B
#define DT 0.005	// Delta de tempo
#define TF 5.	// Tempo final
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	
int main (){
	clock_t tic = clock();
	int seed = time(NULL); 
	srand(seed);

	// Criação do vetor de partículas
	particle *todas;
	todas = (particle *) malloc((N + 1) * sizeof(particle));
	
	// É firula, fiz pra comparar o volume da esfera com o volume das partículas
	double volT, volP, pi = acos(-1);
	volT = (3./4.)*((RS*RS*RS) - (RI*RI*RI))*pi;
	volP = N * (3./4.)*(D*D*D*(1/8.))*pi;
	printf("Volume da esfera: %lf\nVolume das partículas: %lf\n", volT, volP);

	// Criando o arquivo de saída da dinâmica
	char pasta[35], lixo[35], arkinfo[35], cilixo[35];

	sprintf(pasta, "LJ_RS%.1lf_TF%.1lf_LB%.1lf", RS, TF, LB);
	if (mkdir(pasta, 0777) == -1){
		printf("Limpando a pasta\n");
		sprintf(lixo, "LJ_RS%.1lf_TF%.1lf_LB%.1lf/animLJ.txt", RS, TF, LB);
		sprintf(arkinfo, "LJ_RS%.1lf_TF%.1lf_LB%.1lf/info.txt", RS, TF, LB);
		sprintf(cilixo, "LJ_RS%.1lf_TF%.1lf_LB%.1lf/CI.txt", RS, TF, LB);		
		remove(cilixo);
		remove(arkinfo);
		remove(lixo);
	}
	
	// Gerando as partículas
	gerador(todas, N, RS, RI, D);
	
	// Escrita do arquivo de posições iniciais
	ciFile(todas, N, RS, TF, LB);
	
	// Dinâmica
	dinamica(todas, N, RS, RI, D, FRIC, LB, TF, DT);
	
	clock_t toc = clock();
	double time = (double)(toc - tic)/CLOCKS_PER_SEC;
	
	checador(todas, N, RS, D);
	
	// Escrevendo o arquivo com informações<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<NÃO SERIA LEGAL UMA FUNÇÃO PRA ISSO?
	sprintf(arkinfo, "LJ_RS%.1lf_TF%.1lf_LB%.1lf/info.txt", RS, TF, LB);
	FILE *infos = fopen(arkinfo, "w");
	fprintf(infos, "#define D %.1lf		// Diametro das particulas\n", D);
	fprintf(infos, "#define RS %.1lf	// Raio da externo da esfera\n", RS);
	fprintf(infos, "#define RI %.1lf	// Raio da interno da esfera\n", RI);	
	fprintf(infos, "#define N %d		// Número de partículas\n", N);
	fprintf(infos, "#define FRIC %.1lf	// Coeficiente de fricção\n", FRIC);
	fprintf(infos, "#define LB %.1lf	// Lambda B\n", LB);
	fprintf(infos, "#define DT %.4lf	// Delta de tempo\n", DT);
	fprintf(infos, "#define TF %.2lf	// Tempo final\n", TF);
	fprintf(infos, "Número de passos = %.0lf\n", TF/DT);
	fprintf(infos, "Tempo de execução: %.3lfs\n", time);
	fprintf(infos, "Seed aleatória: %d\n", seed);
	
	fclose(infos);
	return 0;
}
