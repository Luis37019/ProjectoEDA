#define _CRT_SECURE_NO_WARNINGS
#define GESTOR_FILE "gestor.txt"
#define GESTOR 0
/**
 * @file main.c
 * @brief Implementacao da funcao principal do programa.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "gestor.h"



Gestor* gestorHead = NULL;

void addGestor(unsigned int nif, char password[], char name[], char address[], float balance) {
	Gestor* newGestor = (Gestor*)malloc(sizeof(Gestor));
	newGestor->nif = nif;
	strcpy(newGestor->password, password);
	strcpy(newGestor->name, name);
	strcpy(newGestor->address, address);
	newGestor->balance = balance;
	newGestor->type = GESTOR;
	newGestor->next = NULL;

	if (gestorHead == NULL) {
		gestorHead = newGestor;
	}
	else {
		Gestor* current = gestorHead;
		while (current->next != NULL) {
			current = current->next;
		}
		current->next = newGestor;
	}

	FILE* fp;
	fp = fopen(GESTOR_FILE, "a");
	fprintf(fp, "%u,%s,%s,%s,%.2f\n", nif, password, name, address, balance);
	fclose(fp);
}
void loadGestor() {
	FILE* fp;
	fp = fopen(GESTOR_FILE, "r");
	if (fp == NULL) {
		printf("Erro ao abrir o arquivo.\n");
		return;
	}

	Gestor* aux_buf = (Gestor*)malloc(sizeof(Gestor));

	while (fscanf(fp, "%u,%[^,],%[^,],%[^,],%f\n", 
													&aux_buf->nif, 
													aux_buf->password,
													aux_buf->name,
													aux_buf->address,
													&aux_buf->balance) != EOF) {

		Gestor* newGestor = (Gestor*)malloc(sizeof(Gestor));

		if (newGestor != NULL) {
			newGestor->nif = aux_buf->nif;
			strcpy(newGestor->password, aux_buf->password);
			strcpy(newGestor->name, aux_buf->name);
			strcpy(newGestor->address, aux_buf->address);
			newGestor->balance = aux_buf->balance;
			newGestor->next = NULL;

			if (gestorHead == NULL) {
				gestorHead = newGestor;
			}
			else {
				Gestor* current = gestorHead;
				while (current->next != NULL) {
					current = current->next;
				}
				current->next = newGestor;
			}
		}
		
	}
	free(aux_buf);
	fclose(fp);
}
void registerGestor() {
	unsigned int nif;
	char password[20];
	char name[50];
	char address[100];
	float balance = 0.0;


	printf("Digite o seu NIF: ");
	scanf("%u", &nif);

	printf("Digite a sua senha: ");
	scanf("%s", password);

	printf("Digite o seu nome: ");
	scanf("%s", name);

	printf("Digite o seu endere?o: ");
	scanf("%s", address);

	addGestor(nif, password, name, address, balance);

	printf("Conta criada com sucesso.\n");
}
void cpyGestorData(Gestor* gestor1, Gestor* gestor2) {
	gestor1->nif = gestor2->nif;
	strcpy(gestor1->password, gestor2->password);
	strcpy(gestor1->name, gestor2->name);
	strcpy(gestor1->address, gestor2->address);
	gestor1->balance = gestor2->balance;
	gestor1->next = NULL;
}
void loginGestor(Gestor* logged_account) {
	unsigned int nif;
	char password[20];

	printf("Digite o seu NIF: ");
	scanf("%u", &nif);

	printf("Digite a sua senha: ");
	scanf("%s", password);

	Gestor* current = gestorHead;

	while (current != NULL) {
		if (current->nif == nif && strcmp(current->password, password) == 0) {
			printf("Login realizado com sucesso.\n");
			// Aqui voc? pode adicionar a logica para permitir que o usu?rio fa?a o que precisa ap?s o login
			_getch();
			cpyUserData(logged_account, current);
			return;
		}
		current = current->next;
	}

	printf("NIF ou senha incorretos.\n");
	_getch();
}
void showUsers() {
	User* current = userHead;
	printf("Lista de Usu?rios:\n");
	while (current != NULL) {
		printf("NIF: %u\n", current->nif);
		printf("Nome: %s\n", current->name);
		printf("Endereco: %s\n", current->address);
		printf("Saldo: %.2f\n", current->balance);
		printf("\n");
		current = current->next;
	}
}

void removeUsers(unsigned int nif) {
	User* current = userHead;
	User* previous = NULL;

	while (current != NULL) {
		if (current->nif == nif) {
			if (previous == NULL) {
				userHead = current->next;
			}
			else {
				previous->next = current->next;
			}
			free(current);
			printf("Usuario com NIF %u removido.\n", nif);
			return;
		}
		previous = current;
		current = current->next;
	}

	printf("Usuario com NIF %u nao encontrado.\n", nif);
}
void removeGestor(unsigned int nif, char password[]) {
	Gestor* current = gestorHead;
	Gestor* prev = NULL;

	FILE* fp;
	fp = fopen(GESTOR_FILE, "w");

	while (current != NULL) {
		if (current->nif == nif && strcmp(current->password, password) == 0) {
			if (prev == NULL) {
				gestorHead = current->next;
			}
			else {
				prev->next = current->next;
			}
			free(current);
			printf("Gestor removido com sucesso.\n");

			// escreve no arquivo o novo estado da lista encadeada
			current = gestorHead;
			while (current != NULL) {
				fprintf(fp, "%u %s %s %s %.2f\n", current->nif, current->password, current->name, current->address, current->balance);
				current = current->next;
			}

			fclose(fp);
			return;
		}
		prev = current;
		current = current->next;
	}
	printf("Gestor não encontrado ou senha incorreta.\n");

	fclose(fp);
}

void updateGestor(Gestor* logged_account) {
	FILE* fp;
	fp = fopen(GESTOR_FILE, "r");
	if (fp == NULL) {
		printf("Erro ao abrir o arquivo.\n");
		return;
	}

	Gestor* current = gestorHead;

	while (current != NULL) {
		if (current->nif == logged_account->nif) {
			strcpy(current->password, logged_account->password);
			strcpy(current->name, logged_account->name);
			strcpy(current->address, logged_account->address);
			current->balance = logged_account->balance;
			break;
		}
		current = current->next;
	}

	fclose(fp);

	fp = fopen(GESTOR_FILE, "w");
	current = gestorHead;
	while (current != NULL) {
		fprintf(fp, "%u,%s,%s,%s,%.2f\n", current->nif, current->password, current->name, current->address, current->balance);
		current = current->next;
	}
	fclose(fp);

	printf("Dados atualizados com sucesso.\n");
	_getch();
}