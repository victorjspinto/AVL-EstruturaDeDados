#include <stdio.h>
#include <stdlib.h>
#include "logic/operacoesavl.h"

int lerInteiro() {
	int result = 0;
	scanf("%d", &result);
	return result;
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

	printf("Digite a matricula do aluno\n");
	matricula = lerInteiro();

	printf("Digite o nome do aluno\n");
	scanf("%s", nome);

	t = insere(t, matricula, nome, 0, 0, 1);

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
}

TAVL* alterarAluno(TAVL* t) {
	printf(
			"    ___    ____                          ___    __                \n"
					"   /   |  / / /____  _________ ______   /   |  / /_  ______  ____ \n"
					"  / /| | / / __/ _ \\/ ___/ __ `/ ___/  / /| | / / / / / __ \\/ __ \\\n"
					" / ___ |/ / /_/  __/ /  / /_/ / /     / ___ |/ / /_/ / / / / /_/ /\n"
					"/_/  |_/_/\\__/\\___/_/   \\__,_/_/     /_/  |_/_/\\__,_/_/ /_/\\____/ \n");
	listarAlunos(t);

	int matricula = lerInteiro();

	TAVL* aluno = buscar(t, matricula);

	printf("Digite o novo semestre do aluno:\n");
	aluno->semestre = lerInteiro();
	printf("Digite a nova carga horario concluida do aluno:\n");
	aluno->cargaCursada = lerInteiro();

	return t;
}

TAVL* telaLimparArvore(TAVL* t) {
	t = limparArvore(t);
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
		}
	}

	return 0;
}
