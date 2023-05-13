#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "gestor.h"
#include "cliente.h"
#include "main.h"
#include "transportes.h"

void registerMenu();
void loginMenu();
void userMenu();
void gestorMenu();
void MenuBalance();
void transportesMenu();
void updateMenu(loggedInAccount);

User* loggedInAccount = NULL; // declare and initialize loggedInAccount

int main() {
    char choice = '0';
    loggedInAccount = malloc(sizeof(User));
    memset(loggedInAccount, 0, sizeof(User));

    do {
        system("cls");
        printf("\nMenu:\n");
        printf("1. Registar\n");
        printf("2. Fazer login\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao:\n ");
        choice = _getch();
        switch (choice) {
        case '1':
            registerMenu();
            break;
        case '2':
            loginMenu();
            break;
        case '0':
            exit(0);
            break;
        default:
            printf("Escolha uma opcao valida.\n");
            break;
        }
    } while (choice != '0');
    return 0;
}

void registerMenu() {
    char choice = '0';
    do {
        system("cls");
        printf("\nRegistar:\n");
        printf("1. Registar como cliente\n");
        printf("2. Registar como gestor\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opcao:\n ");
        choice = _getch();
        switch (choice) {
        case '1':
            registerUser();
            break;
        case '2':
            registerGestor();
            break;
        case '0':
            printf("Voltar ao menu principal.\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;
        }
    } while (choice != '0');
}

void loginMenu() {
    char choice = '0';
    do {
        system("cls");
        printf("\nFazer login:\n");
        printf("1. Fazer login como cliente\n");
        printf("2. Fazer login como gestor\n");
        printf("0. Voltar ao menu principal\n");
        printf("Escolha uma opcao:\n ");
        choice = _getch();
        switch (choice) {
        case '1':
            loginUser(loggedInAccount);
            if (loggedInAccount->nif != NULL) { // check if user is logged in
                userMenu();
            }
            break;
        case '2':
            loginGestor(loggedInAccount);
            if (loggedInAccount->nif != NULL) { // check if user is logged in
                gestorMenu();
            }
            break;
        case '0':
            printf("Voltar ao menu principal.\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;
        }
    } while (choice != '0');
}

void userMenu() {
    char choice = '0';

    do {
        system("cls");
        printf("\nMenu:\n");
        printf("1. Atualizar dados da conta\n");
        printf("2. Remover conta\n");
        printf("3. Ver saldo\n");
        printf("4. Transportes disponiveis\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao:\n ");
        choice = _getch();
        switch (choice) {
        case '1':
            updateMenu(loggedInAccount);
            break;
        case '2':
            removeData(loggedInAccount->nif, loggedInAccount->password);
            loggedInAccount = NULL;
            printf("Conta removida com sucesso.\n");
            _getch();
            break;
        case '3':
            MenuBalance();
            break;
        case '4':
            searchByGeocode();
            break;

        case '0':
            loggedInAccount->nif = 0;
            return;
        default:
            printf("Escolha uma opcao valida.\n");
            break;
        }
    } while (choice != '0');
}
void MenuBalance() {
    char choice = '0';
    float balance = 0.0; // Initialize balance to 0.0
    do {
        system("cls");
        printf("\nMenu de Saldo:\n");
        printf("1. Visualizar saldo\n");
        printf("2. Adicionar saldo\n");
        printf("0. Voltar ao menu do usuario\n");
        printf("Escolha uma opcao:\n ");
        choice = _getch();
        switch (choice) {
        case '1':
            viewBalance(loggedInAccount); // pass the logged in user's account
            _getch();
            break;
        case '2':
            //addBalance(loggedInAccount);
            _getch();
            break;
        case '0':
            printf("Voltar ao menu do usuario.\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;
        }
    } while (choice != '0');
}
void gestorMenu() {
    char choice = '0';
    unsigned int nif = 0;

    do {
        system("cls");
        printf("\nMenu do gestor:\n");
        printf("1. Visualizar lista de clientes\n");
        printf("2. Remover conta de usuario\n");
        printf("3. Transportes\n");
        printf("4. Alterar dados da conta\n");
        printf("0. Fazer logout\n");
        printf("Escolha uma opcao:\n ");
        choice = _getch();
        switch (choice) {
        case '1':
            showUsers();
            break;
        case '2':
            printf("Digite o NIF do usuario que deseja remover: ");
            scanf("%u", &nif);
            removeUsers(nif);
            break;
        case '3':
            transportesMenu();
            break;
        case '4':
            updateMenu(loggedInAccount);
            break;
        case '0':
            loggedInAccount->nif = 0;
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;
        }
    } while (choice != '0');
}
void transportesMenu() {
    int id, type, battery, autonomy;
    char geocode[MAX_GEOCODE_SIZE];
    char choice = '0';

    do {
        system("cls");
        printf("\nMenu Transportes:\n");
        printf("1. Adicionar transporte\n");
        printf("2. Editar transporte\n");
        printf("3. Remover transporte\n");
        printf("4. Listar transportes\n");
        printf("0. Voltar ao menu anterior\n");
        printf("Escolha uma opcao: ");
        choice = _getch();
        switch (choice) {
        case '1':
            // Get the transport information from the user
            addTransport();
            break;
        case '2':
            //Change transport data
            updateTransport();
            break;
        case '3':
            //Remove transport data
            removeTransport();
            break;
        case '4':
            //List transport data
            //listTransport();
            break;
        case '0':
            // Exit the loop
            break;

        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (choice != '0');
}
void updateMenu(User* logged_account) {
    int choice;
    if (logged_account->type == CLIENT) {
        do {
            system("cls");
            printf("Selecione a opcao:\n");
            printf("1 - Atualizar senha\n");
            printf("2 - Atualizar nome\n");
            printf("3 - Atualizar endereco\n");
            printf("4 - Atualizar saldo\n");
            printf("0 - Voltar\n");

            scanf("%d", &choice);

            switch (choice) {
            case 1:
                printf("Digite a nova senha: ");
                scanf("%s", logged_account->password);
                updateData(logged_account);
                _getch();
                break;
            case 2:
                printf("Digite o novo nome: ");
                scanf("%s", logged_account->name);
                updateData(logged_account);
                _getch();
                break;
            case 3:
                printf("Digite o novo endereco: ");
                scanf("%s", logged_account->address);
                updateData(logged_account);
                _getch();
                break;
            case 4:
                printf("Digite o novo saldo: ");
                scanf("%f", &logged_account->balance);
                updateData(logged_account);
                _getch();
                break;
            case 0:
                return;
            default:
                printf("Opcao invalida.\n");
                _getch();
                break;
            }
        } while (1);
    }
    else if (logged_account->type == GESTOR) {
        do {
            system("cls");
            printf("Selecione a opcao:\n");
            printf("1 - Atualizar senha\n");
            printf("2 - Atualizar nome\n");
            printf("3 - Atualizar endereco\n");
            printf("4 - Atualizar saldo\n");
            printf("0 - Voltar\n");

            scanf("%d", &choice);

            switch (choice) {
            case 1:
                printf("Digite a nova senha: ");
                scanf("%s", logged_account->password);
                updateGestor(logged_account);
                _getch();
                break;
            case 2:
                printf("Digite o novo nome: ");
                scanf("%s", logged_account->name);
                updateGestor(logged_account);
                _getch();
                break;
            case 3:
                printf("Digite o novo endereco: ");
                scanf("%s", logged_account->address);
                updateGestor(logged_account);
                _getch();
                break;
            case 4:
                printf("Digite o novo saldo: ");
                scanf("%f", &logged_account->balance);
                updateGestor(logged_account);
                _getch();
                break;
            case 0:
                return;
            default:
                printf("Opcao invalida.\n");
                _getch();
                break;
            }
        } while (1);
    }
}
