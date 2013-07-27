#include "avl.c"
#include <stdio.h>
#include <stdlib.h>

TAVL *inicializa() {
	return NULL;
}

int calc_alt(TAVL *t) {
	if (!t)
		return -1;
	return t->alt;
}

int maximo(int a, int b) {
	if (a > b)
		return a;
	return b;
}

int fb(TAVL* t) {
	int left, right;
	if (!t)
		return 0;
	if (!(t->esq))
		left = 0;
	else
		left = 1 + (t->esq->alt);
	if (!(t->dir))
		right = 0;
	else
		right = 1 + (t->dir->alt);
	return (left - right);
}

TAVL* rse(TAVL *t) {
	TAVL *novo = t->dir;
	t->dir = novo->esq;
	novo->esq = t;
	t->alt = 1 + maximo(calc_alt(t->esq), calc_alt(t->dir));
	novo->alt = maximo(calc_alt(novo->dir), t->alt) + 1;
	return novo;
}

TAVL* rsd(TAVL *t) {
	TAVL *novo = t->esq;
	t->esq = novo->dir;
	novo->dir = t;
	t->alt = 1 + maximo(calc_alt(t->esq), calc_alt(t->dir));
	novo->alt = maximo(calc_alt(novo->esq), t->alt) + 1;
	return novo;
}

TAVL* rde(TAVL* t) {
	t->dir = rsd(t->dir);
	t = rse(t);
	return t;
}

TAVL* red(TAVL* t) {
	t->esq = rse(t->esq);
	t = rsd(t);
	return t;
}

TAVL* insere(TAVL *t, int matricula, char nome[], int cargaCursada,
		int semestre) {
	if (!t) {
		t = (TAVL *) malloc(sizeof(TAVL));

		t->matricula = matricula;
		strcpy(t->nome, nome);
		t->cargaCursada = cargaCursada;
		t->semestre = semestre;

		t->alt = 0;
		t->dir = t->esq = NULL;
	} else if (t->matricula > matricula) {
		t->esq = insere(t->esq, matricula, nome, cargaCursada, semestre);
		if (calc_alt(t->esq) - calc_alt(t->dir) == 2) {
			if (matricula < t->esq->matricula)
				t = rsd(t);
			else
				t = red(t);
		}
	} else if (t->matricula < matricula) {
		t->dir = insere(t->dir, matricula, nome, cargaCursada, semestre);
		if (calc_alt(t->dir) - calc_alt(t->esq) == 2) {
			if (matricula > t->dir->matricula)
				t = rse(t);
			else
				t = rde(t);
		}
	}
	t->alt = maximo(calc_alt(t->esq), calc_alt(t->dir) + 1);
	return t;
}

TAVL* retira(TAVL *t, int m) {
	if (!t)
		return t;
	if (m > t->matricula) {
		t->dir = retira(t->dir, m);
		if (fb(t) == 2) {
			if (fb(t->esq) >= 0)
				t = rsd(t);
			else
				t = rse(t);
		}
	} else if (m < t->matricula) {
		t->esq = retira(t->esq, m);
		if (fb(t) == -2) {
			if (fb(t->dir) <= 0)
				t = rse(t);
			else
				t = rde(t);
		}
	} else {
		if (t->dir) {
			TAVL *p = t->dir;
			while (p->esq)
				p = p->esq;
			t->matricula = p->matricula;
			p->matricula = m;
			t->dir = retira(t->dir, m);
			if (fb(t) == 2) {
				if (fb(t->esq) >= 0)
					t = rsd(t);
				else
					t = red(t);
			}
		} else {
			TAVL *q = t;
			t = t->esq;
			free(q);
			return t;
		}
		if (t) {
			int lh, rh;
			if (!t->esq)
				lh = 0;
			else
				lh = 1 + t->esq->alt;
			if (!t->dir)
				rh = 0;
			else
				rh = 1 + t->dir->alt;
			if (lh > rh)
				t->alt = lh;
			else
				t->alt = rh;
		}
	}
	return t;
}

void imprime(TAVL *t) {
	if (t == NULL)
		return;
	else {
		printf("\nMatricula:%d\n", t->matricula);
		printf(" \tNome:%s\n", t->nome);
		printf(" \tSemestre:%d\n", t->semestre);
		printf(" \tCargaHoraria:%d\n\n", t->cargaCursada);

		if (t->esq != NULL)
			imprime(t->esq);
		if (t->dir != NULL)
			imprime(t->dir);
	}
}

TAVL* buscar(TAVL* t, int matricula) {
	TAVL* result;
	if (t == NULL)
		return NULL;
	if (t->matricula == matricula)
		result = t;
	if (t == NULL)
		result = buscar(t->esq, matricula);
	if (result == NULL)
		result = buscar(t->dir, matricula);
	return result;
}

TAVL* limparArvore(TAVL* t) {
	if (t == NULL)
		return t;
	if (t->semestre == 4 && t->cargaCursada < 1762) {
		printf(
				"Aluno Jubilado\n "
						"\tNome %s\n"
						"\tMatricula %d\n"
						"\tCargaHoraria %d\n"
						"\tSemestre %d\n"
						"sera jubilado por nao completar metade da carga horario no seu quarto semestre.\n",
				t->nome, t->matricula, t->cargaCursada, t->semestre);
		t = retira(t, t->matricula);
	} else if (t->semestre == 12 && t->cargaCursada < 3524) {
		printf("Aluno Jubilado\n"
				"\tNome %s\n"
				"\tMatricula %d\n"
				"\tCargaHoraria %d\n"
				"\tSemestre %d\n"
				"sera jubilado por nao completar o curso em 12 semestres.\n",
				t->nome, t->matricula, t->cargaCursada, t->semestre);
		t = retira(t, t->matricula);
	} else if (t->cargaCursada == 3524) {
		printf("Aluno formado\n"
				"\t Nome %s\n"
				"\t Matricula %d\n"
				"\t Semestre %d\n", t->nome, t->matricula, t->semestre);
		t = retira(t, t->matricula);
	}
	if (t) {
		if (t->dir != NULL)
			t->dir = limparArvore(t->dir);
		if (t->esq != NULL)
			t->esq = limparArvore(t->esq);
	}
	return t;
}
