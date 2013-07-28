#ifndef OPERACOESAVL_H_INCLUDED
#define OPERACOESAVL_H_INCLUDED
#include "avl.c"

TAVL *inicializa();

TAVL *insere(TAVL *t, int matricula, char nome[], int cargaCursada,
		int semestre);

TAVL* buscar(TAVL* t, int matricula);

void imprime(TAVL *t);

TAVL* limparArvore(TAVL* t);

#endif // OPERACOESAVL_H_INCLUDED
