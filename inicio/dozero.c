#include <stdio.h>

/*
Relembrando como se usa os loops em C
*/

int main ()
{
	int x, final;	
	
	
	printf ("Quer o fatorial do que?\n");
	scanf ("%i", &x);
	
	
	for (int cont = x-1; cont >= 1; --cont){
	x *= cont;
	}
	
	printf ("Resultado = %i\n", x);
	
	printf ("Gerando um range até? \n");
	scanf ("%i", &final);
	
	int array[final];
	
	for (int i = 0; i <= final; ++i){
	array[i] = i;
	}
	
	for (int i = final; i >=0; --i){
	printf ("%i\n", array[i]);
	}
		
	return 0;
}

