struct particle {
	// Estrutura com os atributos possíveis de uma partícula
	double p[3];
	double v[3];
	double f[3];
	double carga;
};
// Gerador
double uniform (double min, double max);	
double dist (double dx, double dy, double dz);
struct particle check (struct particle *ptodas, int ind, double r, double min, double max);	
// Dinâmica
double imin(double p1, double p2, double l);
void forcas(struct particle *todas, int n, double l);
double gausran();
