#define _CRT_SECURE_NO_WARNINGS
#define CLIENT_FILE "cliente.txt"
#define CLIENT 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "gestor.h"
#include <conio.h>

User* userHead = NULL;

/**
 * @brief Função para adicionar um novo usuário à lista encadeada e ao arquivo.
 *
 * @param nif Número de identificação fiscal do usuário.
 * @param password Senha do usuário.
 * @param name Nome do usuário.
 * @param address Endereço do usuário.
 * @param balance Saldo do usuário.
 *
 * @return void
 */
void addUser(unsigned int nif, char password[], char name[], char address[], float balance) {
    User* newUser = (User*)malloc(sizeof(User));
    newUser->nif = nif;
    strcpy(newUser->password, password);
    strcpy(newUser->name, name);
    strcpy(newUser->address, address);
    newUser->balance = 0;
    newUser->type = CLIENT;
    newUser->next = NULL;

    if (userHead == NULL) {
        userHead = newUser;
    }
    else {
        User* current = userHead;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newUser;
    }

    addBalance(nif, balance);
}


void loadUsers() {
    FILE* fp = fopen(CLIENT_FILE, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    User* aux_buf = (User*)malloc(sizeof(User));

    while (fscanf(fp, "%u,%[^,],%[^,],%[^,],%f\n", &aux_buf->nif, aux_buf->password, aux_buf->name, aux_buf->address, &aux_buf->balance) != EOF) {
        User* newUser = (User*)malloc(sizeof(User));

        if (newUser != NULL) {
            newUser->nif = aux_buf->nif;
            strcpy(newUser->password, aux_buf->password);
            strcpy(newUser->name, aux_buf->name);
            strcpy(newUser->address, aux_buf->address);
            newUser->balance = aux_buf->balance;
            newUser->next = NULL;

            if (userHead == NULL) {
                userHead = newUser;
            }
            else {
                User* current = userHead;
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = newUser;
            }
        }
        
    }
    free(aux_buf);
    fclose(fp);
}

void registerUser() {
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

    printf("Digite o seu endereço: ");
    scanf("%s", address);

    addUser(nif, password, name, address, balance);

    printf("Conta criada com sucesso.\n");
}

void cpyUserData(User* user1, User* user2) {
    user1->nif = user2->nif;
    strcpy(user1->password, user2->password);
    strcpy(user1->name, user2->name);
    strcpy(user1->address, user2->address);
    user1->balance = user2->balance;
    user1->next = NULL;
}

void loginUser(User* logged_account) {
    unsigned int nif;
    char password[20];

    printf("Digite o seu NIF: ");
    scanf("%u", &nif);

    printf("Digite a sua senha: ");
    scanf("%s", password);

    User* current = userHead;

    while (current != NULL) {
        if (current->nif == nif && strcmp(current->password, password) == 0) {
            printf("Login realizado com sucesso.\n");
            // Aqui você pode adicionar a lógica para permitir que o usuário faça o que precisa após o login
            _getch();
            cpyUserData(logged_account, current);
            return;
        }
        current = current->next;
    }

    printf("NIF ou senha incorretos.\n");
    _getch();
}

/**
 * @brief Função para remover um usuário da lista encadeada.
 *
 * @param nif Número de identificação fiscal do usuário a ser removido.
 * @param password Senha do usuário a ser removido.
 *
 * @return void
 */
void removeData(unsigned int nif, char password[]) {
    User* current = userHead;
    User* prev = NULL;

    FILE* fp;
    fp = fopen(CLIENT_FILE, "w");

    while (current != NULL) {
        if (current->nif == nif && strcmp(current->password, password) == 0) {
            if (prev == NULL) {
                userHead = current->next;
            }
            else {
                prev->next = current->next;
            }
            free(current);
            printf("Usuário removido com sucesso.\n");

            // escreve no arquivo o novo estado da lista encadeada
            current = userHead;
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
    printf("Usuário não encontrado ou senha incorreta.\n");

    fclose(fp);
}

/**
 * @brief Função para atualizar os dados de um usuário, exceto o NIF.
 *
 * @param nif Número de identificação fiscal do usuário a ser atualizado.
 * @param password Senha do usuário a ser atualizado.
 * @param name Novo nome do usuário.
 * @param address Novo endereço do usuário.
 * @param balance Novo saldo do usuário.
 *
 * @return void
 */
void updateData(User* logged_account) {
    FILE* fp;
    fp = fopen(CLIENT_FILE, "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    User* current = userHead;

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

    fp = fopen(CLIENT_FILE, "w");
    current = userHead;
    while (current != NULL) {
        fprintf(fp, "%u,%s,%s,%s,%.2f\n", current->nif, current->password, current->name, current->address, current->balance);
        current = current->next;
    }
    fclose(fp);

    printf("Dados atualizados com sucesso.\n");
    _getch();
}

void viewBalance(User* user) {
    printf("Seu saldo atual é €%.2f\n", user->balance);
}


 // Função para adicionar saldo a um usuário
void addBalance(unsigned int nif, float amount) {
    User* current = userHead;
    while (current != NULL) {
        if (current->nif == nif) {
            current->balance += amount;
            break;
        }
        current = current->next;
    }

    // Salva as alterações no arquivo
    FILE* fp = fopen(CLIENT_FILE, "w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    current = userHead;
    while (current != NULL) {
        fprintf(fp, "%u,%s,%s,%s,%.2f\n", current->nif, current->password, current->name, current->address, current->balance);
        current = current->next;
    }
    fclose(fp);
}