typedef struct particle{
	// Estrutura com os atributos possíveis de uma partícula
	double p[3];
	double v[3];
	double f[3];
	double carga;
	double gaussian[[3]; // Atributo para ajudar na integração
}particle;

// Gerador
double uniform(double min, double max);	
double dist(double dx, double dy, double dz);
particle check(particle *ptodas, int ind, double r, double lx, double ly, double lz);	
// Dinâmica
double imin(double p1, double p2, double l);
void forcas(particle *todas, int n, double l);
double gausran();
