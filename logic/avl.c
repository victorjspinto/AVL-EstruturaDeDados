typedef struct ArvoreAVL {

	int alt;

	int matricula;
	char nome[50];
	int cargaCursada;
	int semestre;

	struct ArvoreAVL *esq, *dir;

} TAVL;
