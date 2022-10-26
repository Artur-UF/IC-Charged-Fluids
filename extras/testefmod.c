#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main (){
	
	double x1, x2, y1, y2, l, dx1, dx2;
	double gausran();
	double imin1(double p1, double p2, double l);
	double imin2(double p1, double p2, double l);
	
	
	printf("x1 = ");
	scanf("%lf", &x1);
	printf("x2 = ");
	scanf("%lf", &x2);
	
	l = 10.0;
	dx1 = imin1(x1, x2, l);
	dx2 = imin2(x1, x2, l);
	printf("Distancia prof = %.2f\n", dx1);
	printf("Distancia minha = %.2f\n", dx2);

	return 0;
}

double imin1(double p1, double p2, double l){
    // Imagem mínima
    double dp;
    
    dp = p2 - p1;
    //dp = l/2.0 - abs(fmod(dp, l/2.0));
    dp = dp - round(dp/l)*l;
    
    return dp;
}

double imin2(double p1, double p2, double l){
    // Imagem mínima
    double dp;
    
    dp = p2 - p1;
    dp = l/2.0 - abs(fmod(dp, l/2.0));
    //dp = dp - round(dp/l)*l;
    
    return dp;
}

double gausran(){
    // generate gaussianrandom_numbers                                                                   
    int g;
    double ran1,ran2,PI,R1,R2,res;
    ran1 = (double)rand()/RAND_MAX;
    ran2 = (double)rand()/RAND_MAX;
    PI   = 4.0*atan(1.0);
    R1   = -log(1.0-ran1);
    R2   = 2.0*PI*ran2;
    R1   = sqrt(2.0*R1);
    res  = R1*cos(R2);
    return res;
}


