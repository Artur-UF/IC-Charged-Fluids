#include <stdio.h>
#include <math.h>
#include <sys/stat.h>
#include <stdlib.h>

typedef struct particle {
	// Estrutura com os atributos possíveis de uma partícula
	double p[3];
	double v[3];
	double f[3];
	double carga;
	double gaussian[3]; // Atributo para ajudar na integração
}particle;

int main (){
	
	// Criando o arquivo de saída da dinâmica<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<TESTA
	char pasta[] = "pasta_teste";
	if (mkdir(pasta, 0777) == -1){
		printf("Erro na pasta\n");
		return 1;
	}
	
	char archiv[50];
	sprintf(archiv, "%s/arquivo_teste.bin", pasta);
	FILE *ark = fopen(archiv, "wb");
	particle *todas;
	todas = (particle *) malloc(3 * sizeof(particle));
	particle p1 = 
	{
		.p = {1., 2., 3.}, 
		.v = {4., 5., 6.}, 
		.f = {7., 8., 9.}, 
		.carga = 10., 
		.gaussian = {11., 12., 13.}
	};
	particle p2 = 
	{
		.p = {14., 15., 16.}, 
		.v = {17., 18., 19.}, 
		.f = {20., 21., 22.}, 
		.carga = 23., 
		.gaussian = {24., 25., 26.}
	};
	particle p3 = 
	{
		.p = {27., 28., 29.}, 
		.v = {30., 31., 32.}, 
		.f = {33., 34., 35.}, 
		.carga = 36., 
		.gaussian = {37., 38., 39.}
	};
	
	todas[0] = p1;
	todas[1] = p2;
	todas[2] = p3;
	
	printf("Escrita\n");
	
	for (int i = 0; i < 3; ++i){
		printf("p = (%.1f, %.1f, %.1f)\n", todas[i].p[0], todas[i].p[1], todas[i].p[2]);
		printf("v = (%.1f, %.1f, %.1f)\n", todas[i].v[0], todas[i].v[1], todas[i].v[2]);
		printf("f = (%.1f, %.1f, %.1f)\n", todas[i].f[0], todas[i].f[1], todas[i].f[2]);
		printf("carga = %.1f\n", todas[i].carga);
		printf("gaussian = (%.1f, %.1f, %.1f)\n\n", todas[i].gaussian[0], todas[i].gaussian[1], todas[i].gaussian[2]);
	}	
	
	fwrite(todas, sizeof(particle), 3, ark);
	fclose(ark);
	free(todas);
	
	FILE *ark2 = fopen(archiv, "rb");
	particle *todasin;
	todasin = (particle *) malloc(3 * sizeof(particle));
	
	fread(todasin, sizeof(particle), 3, ark2);

	printf("Leitura\n");
	
	for (int i = 0; i < 3; ++i){
		printf("p = (%.1f, %.1f, %.1f)\n", todasin[i].p[0], todasin[i].p[1], todasin[i].p[2]);
		printf("v = (%.1f, %.1f, %.1f)\n", todasin[i].v[0], todasin[i].v[1], todasin[i].v[2]);
		printf("f = (%.1f, %.1f, %.1f)\n", todasin[i].f[0], todasin[i].f[1], todasin[i].f[2]);
		printf("carga = %.1f\n", todasin[i].carga);
		printf("gaussian = (%.1f, %.1f, %.1f)\n\n", todasin[i].gaussian[0], todasin[i].gaussian[1], todasin[i].gaussian[2]);
	}
	
	free(todasin);
	fclose(ark2);
	
	return 0;
}

