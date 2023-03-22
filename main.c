#include <stdio.h>
#include <stdlib.h>
#include "gestor.h"
#include "cliente.h"
#include "main.h"

void registerMenu();
void loginMenu();
void userMenu();
void gestorMenu();

int main() {
    int choice = 0;
    do {
        printf("\nMenu:\n");
        printf("1. Registar\n");
        printf("2. Fazer login\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            registerMenu();
            break;
        case 2:
            loginMenu();
            break;
        case 0:
            printf("Sair.\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;
        }
    } while (choice != 0);
    return 0;
}

void registerMenu() {
    int choice = 0;
    do {
        printf("\nRegistar:\n");
        printf("1. Registar como cliente/usuario\n");
        printf("2. Registar como gestor\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            registerUser();
            break;
        case 2:
            registerGestor();
            break;
        case 0:
            printf("Voltar ao menu principal.\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;
        }
    } while (choice != 0);
}

void loginMenu() {
    int choice = 0;
    do {
        printf("\nFazer login:\n");
        printf("1. Fazer login como cliente/usuario\n");
        printf("2. Fazer login como gestor\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            loginUser();
            userMenu();
            break;
        case 2:
            loginGestor();
            gestorMenu();
            break;
        case 0:
            printf("Voltar ao menu principal.\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;
        }
    } while (choice != 0);
}

void userMenu() {
    int choice = 0;
    do {
        printf("\nMenu do usuario:\n");
        printf("1. Atualizar dados da conta\n");
        printf("2. Remover conta\n");
        printf("0. Fazer logout\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            updateData();
            break;
        case 2:
            removeData();
            break;
        case 0:
            printf("Fazer logout.\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;
        }
    } while (choice != 0);
}
void gestorMenu() {
    int choice = 0;
    do {
        printf("\nMenu do gestor:\n");
        printf("1. Visualizar lista de usuarios\n");
        printf("2. Remover conta de usuario\n");
        printf("0. Fazer logout\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            showUsers();
            break;
        case 2:
            removeUser();
            break;
        case 0:
            printf("Fazer logout.\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;
        }
    } while (choice != 0);
}