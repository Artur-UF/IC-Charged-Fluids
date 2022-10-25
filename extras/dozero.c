#include <stdio.h>

/*
Relembrando como se usa os loops em C

Compilação: $ gcc <nome do arquivo.c> -o <nome da saída>
	    $ ./<saída>
*/

int fatorial (int n) 
{
	for (int cont = n-1; cont >= 1; --cont)
	{
		n *= cont;
	}
	return n;
}


int fatorial2 (int x)
	{
	int resultado;
	
	if (x == 0){
		resultado = 1;
	}else{
		resultado = x * fatorial2(x-1);
	}
	return resultado;
	
	}


int main ()
{
	int x, final;	
	int fatorial(int);
	double y = 34.25634;
	
	printf ("Quer o fatorial do que?\n");
	scanf ("%i", &x);
	
	x = fatorial2(x);
		
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
		
	printf ("Imprimindo doubles: %.2f\n", y);
	
	return 0;
}

