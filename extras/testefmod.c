#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main (){
	
	double x1, x2, y1, y2, l;
	double gausran();
	
	for (int i = 0; i < 10; ++i){
		printf("%lf\n", gausran());
	}
	

	return 0;
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


