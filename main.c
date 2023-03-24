#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "gestor.h"
#include "cliente.h"
#include "main.h"

void registerMenu();
void loginMenu();
void userMenu();
void gestorMenu();
void MenuBalance();

int main() {
    char choice = '0';
    do {
        system("cls");
        printf("\nMenu:\n");
        printf("1. Registar\n");
        printf("2. Fazer login\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        choice = _getch(); 
        switch (choice) {
        case '1':
            registerMenu();
            break;
        case '2':
            loginMenu();
            break;
        case '0':
            printf("Sair.\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
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
        printf("Escolha uma opcao: ");
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
        printf("Escolha uma opcao: ");
        choice = _getch();
        switch (choice) {
        case '1':
            loginUser();
            userMenu();
            break;
        case '2':
            loginGestor();
            gestorMenu();
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
        printf("\nMenu do usuario:\n");
        printf("1. Atualizar dados da conta\n");
        printf("2. Remover conta\n");
        printf("3. Saldo\n"); 
        printf("0. Fazer logout\n");
        printf("Escolha uma opcao: ");
        choice = _getch();
        switch (choice) {
        case '1':
            updateData();
            break;
        case '2':
            removeData();
            break;
        case '3':
            MenuBalance(); // Chama função MenuBalance
            break;
        case '0':
            printf("Fazer logout.\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;
        }
    } while (choice != '0');
}
void MenuBalance() {
    char choice = '0';
    float balance = 0;
    do {
        system("cls");
        printf("\nMenu de Saldo:\n");
        printf("1. Visualizar saldo\n");
        printf("2. Adicionar saldo\n");
        printf("0. Voltar ao menu do usuario\n");
        printf("Escolha uma opcao: ");
        choice = _getch();
        switch (choice) {
        case '1':
            printf("\nSaldo atual: %.2f\n", balance);
            break;
        case '2':
            printf("\nDigite o valor a ser adicionado: ");
            float value;
            scanf("%f", &value);
            balance += value;
            printf("Saldo atualizado com sucesso!\n");
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
    do {
        system("cls");
        printf("\nMenu do gestor:\n");
        printf("1. Visualizar lista de clientes\n");
        printf("2. Remover conta de usuario\n");
        printf("0. Fazer logout\n");
        printf("Escolha uma opcao: ");
        choice = _getch();
        switch (choice) {
        case '1':
            showUsers();
            break;
        case '2':
            removeUser();
            break;
        case '0':
            printf("Fazer logout.\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;
        }
    } while (choice != '0');
}