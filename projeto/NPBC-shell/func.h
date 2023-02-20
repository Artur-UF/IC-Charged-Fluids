#define NA 1.	// Carga do sódio
#define CL -1.	// Carga do Cloro
#define CENT 10.
#define CHECKPOINT 10.

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
particle check(particle *todas, particle teste, int i, double rs, double ri, double d);

// Gera as coordenadas aleatórias de todas as partículas
void gerador(particle *todas, int n, double rs, double ri, double d);

// Gera um arquivo com as posições iniciais das partículas
void ciFile(particle *todas, int n, double rs, double tf, double lb);

// Calcula as forças do potencial de Lennard-Jones
void forcas(particle *todas, int n, double d, double lb);

// Checa se alguma partícula está fora da esfera ou se tem alguma se sobrepondo
void checador(particle *todas, int n, double rs, double d);

// Realiza a dinâmica
void dinamica(particle *todas, int n, double rs, double ri, double d, double fric, double lb, double tf, double dt);

// Gerador de numeros aleatórios em uma distribuição Gaussiana
double gausran();
