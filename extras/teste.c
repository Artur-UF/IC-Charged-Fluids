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

double imin(double p1, double p2, double l){
    // Imagem mínima
    double dp;
    
    dp = p2 - p1;
    dp = dp - round(dp/l)*l;
    
    return dp;
}

int main (){
	
	double x1, x2;
	
	printf("x1 = ");
	scanf("%lf", &x1);	
	
	printf("x2 = ");
	scanf("%lf", &x2);
	
	printf("imin(%.1lf, %.1lf) = %.1lf\n", x1, x2, imin(x1, x2, 10.));
	printf("imin(%.1lf, %.1lf) = %.1lf\n", x2, x1, imin(x2, x1, 10.));
		
	return 0;
}

