#include <stdio.h>
#include <math.h>

int main (){
	
	int x1, x2;
	
	int res;
	
	printf("x1 = ");
	scanf("%d", &x1);

	printf("x2 = ");
	scanf("%d", &x2);
	
	res = fmod(x1, x2);

	printf("Resto da divisão x1/x2 = %d\n", res);
	
	return 0;
}

