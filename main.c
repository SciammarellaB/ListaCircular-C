#include <stdio.h>
#include <stdlib.h>

/*
	Definicao do struct com conteudo e ponteiro para o proximo
*/
typedef struct pessoa {
	//ponteiro do proximo
	struct pessoa *prox;
	//conteudo util
	int idade;
	char nome[126];
}Pessoa;

/* 
	Inicializar como null para n ter lixo
*/
Pessoa* inicializa() {
	return NULL;
}

/*
	Incluir sera colocado ao inicio da lista
*/
Pessoa* incluir_inicio(Pessoa* pessoas, int idade, char nome[126]) {
	//alocar espaco para 
	Pessoa* item = (Pessoa*)malloc(sizeof(Pessoa));
	//caso n consiga alocar
	if (!item)
		exit(1);

	//colocar valores
	item->idade = idade;
	strcpy(item->nome, nome);

	//quando nao tem nenhum item na lista o prox aponta para o proprio item
	if (!pessoas) {
		item->prox = item;
		return item;
	}
	//quando possui item, precisa percorrer a lista a incluir no fim
	else {
		Pessoa* pessoa_aux = pessoas->prox;
		while (pessoa_aux->prox != pessoas) {
			pessoa_aux = pessoa_aux->prox;
		}
		item->prox = pessoas;
		pessoa_aux->prox = item;
		return item;
	}
}

/* 
	Incluir sera colocado ao fim da lista
*/
Pessoa* incluir_fim(Pessoa* pessoas, int idade, char nome[126]) {
	//alocar espaco para 
	Pessoa* item = (Pessoa*) malloc(sizeof(Pessoa));
	//caso n consiga alocar
	if (!item)
		exit(1);

	//colocar valores
	item->idade = idade;
	strcpy(item->nome, nome);

	//quando nao tem nenhum item na lista o prox aponta para o proprio item
	if (!pessoas) {
		item->prox = item;
		return item;
	}
	//quando possui item, precisa percorrer a lista a incluir no fim
	else {
		Pessoa* pessoa_aux = pessoas->prox;
		while (pessoa_aux->prox != pessoas) {
			pessoa_aux = pessoa_aux->prox;
		}
		item->prox = pessoas;
		pessoa_aux->prox = item;
		return pessoas;
	}
}

/*
	Realiza a limpeza de todos os itens do ponteiro passado
*/
Pessoa* limpar(Pessoa* pessoas) {
	if (pessoas) {
		Pessoa* item = pessoas->prox, * aux;
		while (item != pessoas) {
			aux = item;
			item = item->prox;
			free(aux);
		}
		free(pessoas);
		return NULL;
	}
}

/*
	Mostra na tela apenas o ponteiro passado.
*/
void imprimir(Pessoa* pessoa) {
	//imprimir um elemento
	printf("\nNome: %s", pessoa->nome);
	printf("\nIdade: %d", pessoa->idade);
	printf("\n");
}

/*
	Lista todos os itens e mostra eles na tela.
*/
void listar(Pessoa* pessoas) {
	
	//caso esteja nulo a lista esta vazia. mesmo tendo apenas um item o prox aponta para ele mesmo.
	if (!pessoas) {
		printf("\nNENHUM ITEM ENCONTRADO!!!\n");
		return;
	}

	//auxiliar inicializado a partir do segundo item da lista;
	Pessoa* pessoa_aux = pessoas->prox;
		
	//imprimir o primeiro
	printf("\nNome: %s", pessoas->nome);
	printf("\nIdade: %d", pessoas->idade);

	while (pessoa_aux != pessoas) {
		printf("\nNome: %s", pessoa_aux->nome);
		printf("\nIdade: %d", pessoa_aux->idade);
		//para percorrer os itens
		pessoa_aux = pessoa_aux->prox;
	}
	printf("\n");
}

/*
	Realiza a busca de um ou mais itens que contenham o nome igual ao passado.
	Cria uma lista contendo esses conteudos encontrados e mostra na tela.
	Após a conclusão, limpa a lista criada.
*/
void buscar_nome(Pessoa* pessoas, char nome[126]) {
	//auxiliar inicializado a partir do segundo item da lista;
	Pessoa* pessoa_aux = pessoas->prox;

	//caso esteja nulo a lista esta vazia. mesmo tendo apenas um item o prox aponta para ele mesmo.
	if (!pessoa_aux) printf("\nLISTA VAZIA!!!");

	Pessoa* aux = NULL;
	while (pessoa_aux != pessoas) {
		if (strcmp(pessoa_aux->nome, nome) == 0) {
			aux = incluir_fim(aux, pessoa_aux->idade, pessoa_aux->nome);
		}
		pessoa_aux = pessoa_aux->prox;
	}
	listar(aux);
	aux = limpar(aux);
}

int main() {

	Pessoa* pessoas = inicializa();

	printf("\nINICIALIZANDO\n");

	//INCLUSAO DE VALORES UTILIZANDO OS METODOS DE INCLUSAO CRIADOS
	pessoas = incluir_inicio(pessoas, 10, "Pessoa 1");
	pessoas = incluir_inicio(pessoas, 15, "Pessoa 2");
	pessoas = incluir_fim(pessoas, 22, "Pessoa 3");
	pessoas = incluir_inicio(pessoas, 5, "Pessoa 4");
	pessoas = incluir_fim(pessoas, 17, "Pessoa 5");
	pessoas = incluir_fim(pessoas, 20, "Pessoa 6");
	pessoas = incluir_inicio(pessoas, 56, "Pessoa 7");

	printf("\nLISTANDO\n");

	listar(pessoas);

	printf("\nBUSCANDO\n");

	buscar_nome(pessoas, "Pessoa 1");

	printf("\nLIMPANDO\n");

	pessoas = limpar(pessoas);

	printf("\nLISTANDO\n");

	listar(pessoas);

	return 0;
}