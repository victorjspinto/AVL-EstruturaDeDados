#include <stdio.h>
#include <stdlib.h>
#include "logic/operacoesavl.h"

int lerInteiro() {
	int result = 0;
	scanf("%d", &result);
	return result;
}

void enterParaContinuar() {
	printf("\n\nPressione enter para continuar\n");
	char enter = 0;
	getchar();
	while (enter != '\r' && enter != '\n') {
		enter = getchar();
	}
}

void imprimeMenu() {
	printf(
			"    ____               _      __           ___ _    ____       __________ ___\n"
					"   / __ \\_________    (_)__  / /_____     /   | |  / / /      / ____/ __ <  /\n"
					"  / /_/ / ___/ __ \\  / / _ \\/ __/ __ \\   / /| | | / / /      / __/ / / / / / \n"
					" / ____/ /  / /_/ / / /  __/ /_/ /_/ /  / ___ | |/ / /___   / /___/ /_/ / /  \n"
					"/_/   /_/   \\____/_/ /\\___/\\__/\\____/  /_/  |_|___/_____/  /_____/_____/_/   \n"
					"                /___/                                                        \n");
	printf("Digite a odpcao desejada abaixo:\n");
	printf("\t(1) - Inserir Aluno manualmente\n");
	printf("\t(2) - Importar Alunos de arquivo\n");
	printf("\t(3) - ListarAlunos\n");
	printf("\t(4) - Alterar dados de aluno\n");
	printf("\t(5) - Limpar arvore\n");
	printf("\t(0) - Sair\n");
}

TAVL* cadastrarAluno(TAVL* t) {
	printf(
			"   ______          __           __                    __        ___    __                \n"
					"  / ____/___ _____/ /___ ______/ /__________     ____/ /__     /   |  / /_  ______  ____ \n"
					" / /   / __ `/ __  / __ `/ ___/ __/ ___/ __ \\   / __  / _ \\   / /| | / / / / / __ \\/ __ \\\n"
					"/ /___/ /_/ / /_/ / /_/ (__  ) /_/ /  / /_/ /  / /_/ /  __/  / ___ |/ / /_/ / / / / /_/ /\n"
					"\\____/\\__,_/\\__,_/\\__,_/____/\\__/_/   \\____/   \\__,_/\\___/  /_/  |_/_/\\__,_/_/ /_/\\____/ \n");

	int matricula;
	char nome[50];

	printf("Digite a matricula do aluno:\n");
	matricula = lerInteiro();

	printf("Digite o nome do aluno:\n");
	getchar();
	scanf("%30[^\n]", nome);

	t = insere(t, matricula, nome, 0, 1);

	printf("Aluno cadastrado com sucesso!   :-)\n");
	return t;
}

void listarAlunos(TAVL* t) {
	printf(
			"    __    _      __                                    __        ___    __                      \n"
					"   / /   (_)____/ /_____ _____ ____  ____ ___     ____/ /__     /   |  / /_  ______  ____  _____\n"
					"  / /   / / ___/ __/ __ `/ __ `/ _ \\/ __ `__ \\   / __  / _ \\   / /| | / / / / / __ \\/ __ \\/ ___/\n"
					" / /___/ (__  ) /_/ /_/ / /_/ /  __/ / / / / /  / /_/ /  __/  / ___ |/ / /_/ / / / / /_/ (__  ) \n"
					"/_____/_/____/\\__/\\__,_/\\__, /\\___/_/ /_/ /_/   \\__,_/\\___/  /_/  |_/_/\\__,_/_/ /_/\\____/____/  \n"
					"                       /____/                                                                   \n");
	imprime(t);
	enterParaContinuar();
}

TAVL* alterarAluno(TAVL* t) {
	printf(
			"    ___    ____                          ___    __                \n"
					"   /   |  / / /____  _________ ______   /   |  / /_  ______  ____ \n"
					"  / /| | / / __/ _ \\/ ___/ __ `/ ___/  / /| | / / / / / __ \\/ __ \\\n"
					" / ___ |/ / /_/  __/ /  / /_/ / /     / ___ |/ / /_/ / / / / /_/ /\n"
					"/_/  |_/_/\\__/\\___/_/   \\__,_/_/     /_/  |_/_/\\__,_/_/ /_/\\____/ \n");

	imprime(t);

	TAVL* aluno = NULL;
	int semestre, cargaHoraria;
	while(!aluno){
		printf("Digite umas das matriculas acimas para selecionar o aluno:\n");
		int matricula = lerInteiro();
		aluno = buscar(t, matricula);
	}

	printf("Digite o novo semestre do aluno:\n");
	semestre = lerInteiro();
	printf("Digite a nova carga horario concluida do aluno:\n");
	cargaHoraria = lerInteiro();

	aluno->semestre = semestre;
	aluno->cargaCursada = cargaHoraria;

	return t;
}

TAVL* telaLimparArvore(TAVL* t) {
	printf(
			"    __    _                                         __                                        \n"
					"   / /   (_)___ ___  ____  ___  ____  ____ _   ____/ /___ _   ____ _______   ______  ________ \n"
					"  / /   / / __ `__ \\/ __ \\/ _ \\/_  / / __ `/  / __  / __ `/  / __ `/ ___/ | / / __ \\/ ___/ _ \\\n"
					" / /___/ / / / / / / /_/ /  __/ / /_/ /_/ /  / /_/ / /_/ /  / /_/ / /   | |/ / /_/ / /  /  __/\n"
					"/_____/_/_/ /_/ /_/ .___/\\___/ /___/\\__,_/   \\__,_/\\__,_/   \\__,_/_/    |___/\\____/_/   \\___/ \n"
					"                 /_/                                                                          \n\n\n");
	printf("\t Iniciando processo de limpeza da arvore\n");
	t = limparArvore(t);
	printf("\n\n Processo finalizado com sucesso\n");
	enterParaContinuar();
	return t;
}

TAVL* importarAlunos(TAVL* t) {
	FILE *fp;

	int matricula, cargaHoraria, semestre;
	char nome[30];

	printf("Iniciando importacao de alunos \n\n");

	if ((fp = fopen("lista.txt", "r")) != NULL) {
		while (fscanf(fp, "%d %d %d %30[^\n]", &matricula, &cargaHoraria, &semestre, &nome) != EOF) {
			printf("\t%3d %5d %3d %30s\n", matricula, cargaHoraria, semestre, nome);
			t = insere(t, matricula, nome, cargaHoraria, semestre);
		}
	} else{
		printf("O arquivo lista.txt não existe!\n");
		enterParaContinuar();
		return t;
	}

	printf("Alunos importados com sucesso\n");

	enterParaContinuar();

	fclose(fp);

	return t;
}

void limparTela() {
	system("clear");
}

int main() {
	int sair = 0;
	TAVL *t = inicializa();

	while (!sair) {
		int opcaoSelecionada;

		limparTela();
		imprimeMenu();

		opcaoSelecionada = lerInteiro();
		limparTela();

		switch (opcaoSelecionada) {
		case 1:
			t = cadastrarAluno(t);
			break;
		case 2:
			t = importarAlunos(t);
			break;
		case 3:
			listarAlunos(t);
			break;
		case 4:
			t = alterarAluno(t);
			break;
		case 5:
			t = telaLimparArvore(t);
			break;
		case 0:
			sair = 1;
			break;
		default:
			printf("Opcao selecionada invalida!  [%d]\n", opcaoSelecionada);
			enterParaContinuar();
		}
	}

	return 0;
}
