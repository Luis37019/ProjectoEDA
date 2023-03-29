#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "gestor.h"
#include "cliente.h"
#include "main.h"
#include "transportes.h"

void registerMenu();
void loginMenu();
void MenuBalance();
void userMenu();
void transportesMenu();
void gestorMenu();

int main() {
    
    char choice = '0';
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
        printf("Escolha uma opcao:\n ");
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
            printf("\nSaldo atual: %.2f\n", balance);
            printf("\nPress any key to continue\n");
            _getch();
            break;
        case '2':
            addBalance(&balance);
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
    do {
        system("cls");
        printf("\nMenu do gestor:\n");
        printf("1. Visualizar lista de clientes\n");
        printf("2. Remover conta de usuario\n");
        printf("3. Transportes\n");
        printf("0. Fazer logout\n");
        printf("Escolha uma opcao:\n ");
        choice = _getch();
        switch (choice) {
        case '1':
            showUsers();
            break;
        case '2':
            removeUser();
            break;
        case '3':
            transportesMenu();
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
void transportesMenu() {
    int id, type, battery, autonomy;
    char geocode[MAX_GEOCODE_SIZE];
    char choice = '0';

    do {
        system("cls");
        printf("\nMenu Transportes:\n");
        printf("1. Adicionar transporte\n");
        printf("2. Remover transporte\n");
        printf("3. Editar transporte\n");
        printf("0. Voltar ao menu anterior\n");
        printf("Escolha uma opcao:\n ");
        choice = _getch();
        switch (choice) {
        case '1':
            // Get the transport information from the user
            printf("Id: ");
            scanf("%d", &id);
            printf("Tipo (1 para Carro, 2 para Autocarro, 3 para Camioneta): ");
            scanf("%d", &type);
            printf("Bateria (em percentagem): ");
            scanf("%d", &battery);
            printf("Autonomia (em km): ");
            scanf("%d", &autonomy);
            printf("Geocode: ");
            scanf("%s", geocode);

            // Create the transport variable with the user input
            transports_data transport = { id, type, battery, autonomy, geocode };

            // Call the add_transport function with the transport variable
            add_transport(transport);
            printf("Transporte adicionado com sucesso!\n");
            break;
        case '2':
            printf("Id do transporte a remover: ");
            scanf("%d", &id);
            remove_transport(id);
            printf("Transporte removido com sucesso!\n");
            break;
        case '3':
            // Get the new transport information from the user
            printf("Id do transporte a editar: ");
            scanf("%d", &id);
            printf("Novo tipo (1 para Carro, 2 para Autocarro, 3 para Camioneta): ");
            scanf("%d", &type);
            printf("Nova bateria (em percentagem): ");
            scanf("%d", &battery);
            printf("Nova autonomia (em km): ");
            scanf("%d", &autonomy);
            printf("Nova geocode: ");
            scanf("%s", geocode);

            // Create the new_transport variable with the user input
            transports_data new_transport = { id, type, battery, autonomy, geocode };

            // Call the edit_transport function with the id and new_transport variables
            edit_transport(id, new_transport);
            printf("Transporte editado com sucesso!\n");
            break;
        case '0':
            printf("Voltar.\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;
        }
        printf("Pressione qualquer tecla para continuar...");
        _getch();
    } while (choice != '0');
}