#define NA 1.
#define CL -1.

typedef struct {
	// Estrutura com os atributos possíveis de uma partícula
	double p[3];
	double v[3];
	double f[3];
	double carga;
	double gaussian[3]; // Atributo para ajudar na integração
}particle;

// Gerador de números aleatórios em uma distriibuição uniforme
double uniform(double min, double max);

// Calcula a distância tridimencional baseado em deltas
double dist(double dx, double dy, double dz);

// Função recursiva que checa se a artícula atual está sobreondo alguma e se está contida na esfera
particle check(particle *todas, particle teste, int i, double rs, double r);

// Gera as coordenadas aleatórias de todas as partículas
void gerador(particle *todas, int n, double rs, double r);

// Gera um arquivo com as posições iniciais das partículas
void ciFile(particle *todas, int n, double rs, double r);

// Calcula as forças do potencial de Lennard-Jones
void forcas(particle *todas, int n);

// Realiza a dinâmica
void dinamica(particle *todas, int n, double rs, double r, double fric, double tf, double dt);

double gausran();
