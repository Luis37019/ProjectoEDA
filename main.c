/**

* @file main.c
* @brief Função principal do sistema de contas bancárias.
*/
#define _CRT_SECURE_NO_WARNINGS /**< Diretiva para desativar avisos de segurança do compilador. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"

/**

* @brief Função principal que apresenta um menu ao usuário e permite que ele execute várias opções do sistema.

* @return Retorna 0 para indicar que o programa foi executado com sucesso.
*/
int main() {
	int choice;

	do {
		printf("Bem-vindo ao sistema de contas bancárias.\n");
		printf("Digite 1 para cadastrar um novo usuário.\n");
		printf("Digite 2 para fazer login.\n");
		printf("Digite 3 para remover os dados de um usuário.\n");
		printf("Digite 4 para alterar os dados de um usuário.\n");
		printf("Digite 0 para sair.\n");

        scanf("%d", &choice);

        switch (choice) {
        case 1:
            registerUser();
            break;
        case 2:
            loginUser();
            break;
        case 3:
            removeData();
            break;
        case 4:
            updateData();
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida.\n");
            break;
        }
    } while (choice != 0);

    return 0;
}