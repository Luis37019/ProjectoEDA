#define _CRT_SECURE_NO_WARNINGS
/**
 * @file main.c
 * @brief Implementa??o da fun??o principal do programa.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "gestor.h"


  /**
   * @brief Fun??o para criar conta para cliente ou gestor.
   */
void registerGestor() {
    /**
     * @brief Estrutura de dados que representa um novo usu?rio.
     */
    struct Gestor newGestor = { 0 };
    printf("Digite o n?mero de NIF (at? 20 caracteres): ");
    scanf("%u", &newGestor.nif);

    printf("Digite uma senha (at? 20 caracteres): ");
    scanf("%s", newGestor.password);

    printf("Digite o nome do usu?rio (at? 50 caracteres): ");
    scanf(" %[^\n]", newGestor.name);

    printf("Digite o endere?o do usu?rio (at? 100 caracteres): ");
    scanf(" %[^\n]", newGestor.address);

    // Abrir o arquivo de usu?rios no modo de escrita
    FILE* gestorFile = fopen("gestor.txt", "a");

    // Verificar se o arquivo foi aberto corretamente
    if (gestorFile == NULL) {
        printf("Erro ao abrir o arquivo de gestores.\n");
        return;
    }

    // Escrever os dados do novo gestor no arquivo
    fprintf(gestorFile, "%u,%s,%s,%s\n", newGestor.nif, newGestor.password, newGestor.name, newGestor.address);

    // Fechar o arquivo
    fclose(gestorFile);
}

/**
 * @brief Fun??o para verificar as informa??es de login do gestor.
 *
 * @return void
 */
void loginGestor() {
    unsigned int nif; /**< N?mero de identifica??o fiscal do gestor. */
    char password[20]; /**< Senha do gestor. */
    char line[100]; /**< Linha atual do arquivo de gestor. */
    printf("Digite o n?mero de NIF (at? 20 caracteres): ");
    scanf("%u", &nif);

    printf("Digite uma senha (at? 20 caracteres): ");
    scanf("%s", password);

    // Abrir o arquivo de gestores no modo de leitura
    FILE* gestorFile = fopen("gestor.txt", "r");

    // Verificar se o arquivo foi aberto corretamente
    if (gestorFile != NULL) {
        unsigned int savedNif = 0;
        char savedPassword[20] = { 0 };
        char savedName[50] = { 0 };
        char savedAddress[100] = { 0 };
        int loginSuccess = 0; /**< Flag para indicar se o login foi bem-sucedido ou n?o. */

        // Ler cada linha do arquivo
        while (fgets(line, 100, gestorFile) != NULL) {
            sscanf(line, "%u,%[^,],%[^,],%[^\n]\n", &savedNif, savedPassword, savedName, savedAddress);

            // Verificar se as informa??es de login coincidem
            if (savedNif == nif && strcmp(password, savedPassword) == 0) {
                printf("Login bem-sucedido. Bem-vindo, %s!\n", savedName);
                loginSuccess = 1; // Atualiza a flag

                // Fechar o arquivo
                fclose(gestorFile);

                break; // Sai do loop pois o login foi bem-sucedido
            }
        }

        // Verificar se o login foi bem-sucedido
        if (!loginSuccess) {
            printf("Login sem sucesso...\n");
        }
    }
    else {
        printf("Login sem sucesso...\n");
    } 
}
void showUsers() {
    // Abrir o arquivo de usu?rios no modo de leitura
    FILE* usersFile = fopen("users.txt", "r");

    // Verificar se o arquivo foi aberto corretamente
    if (usersFile == NULL) {
        printf("Erro ao abrir o arquivo de usu?rios.\n");
        return;
    }

    printf("Lista de usu?rios:\n");

    // Ler cada linha do arquivo e imprimir as informa??es do usu?rio correspondente
    char line[100];
    while (fgets(line, 100, usersFile) != NULL) {
        unsigned int nif;
        char password[20];
        char name[50];
        char address[100];
        sscanf(line, "%u,%[^,],%[^,],%[^\n]", &nif, password, name, address);
        printf("NIF: %u\nSenha: %s\nNome: %s\nEndere?o: %s\n\n", nif, password, name, address);
    }

    // Fechar o arquivo
    fclose(usersFile);

}
/**
 * @brief Fun??o para remover uma conta de cliente.
 *
 * @return void
 */
void removeUser() {
    unsigned int nif; /**< N?mero de identifica??o fiscal do usu?rio. */
    char line[100]; /**< Linha atual do arquivo de usu?rios. */

    printf("Digite o n?mero de NIF do usu?rio que deseja remover: ");
    scanf("%u", &nif);

    // Abrir o arquivo de usu?rios no modo de leitura
    FILE* usersFile = fopen("users.txt", "r");

    // Verificar se o arquivo foi aberto corretamente
    if (usersFile != NULL) {
        // Abrir um novo arquivo para escrever os usu?rios que n?o ser?o removidos
        FILE* newFile = fopen("new_users.txt", "w");

        // Verificar se o novo arquivo foi aberto corretamente
        if (newFile == NULL) {
            printf("Erro ao criar o novo arquivo de usu?rios.\n");
            fclose(usersFile);
            return;
        }

        int userRemoved = 0; /**< Flag para indicar se o usu?rio foi removido ou n?o. */

        // Ler cada linha do arquivo de usu?rios
        while (fgets(line, 100, usersFile) != NULL) {
            unsigned int savedNif;
            char savedPassword[20] = { 0 };
            char savedName[50] = { 0 };
            char savedAddress[100] = { 0 };
            sscanf(line, "%u,%[^,],%[^,],%[^\n]", &savedNif, savedPassword, savedName, savedAddress);

            // Verificar se o NIF corresponde ao usu?rio a ser removido
            if (savedNif == nif) {
                userRemoved = 1;
            }
            else {
                // Escrever a linha no novo arquivo
                fprintf(newFile, "%u,%s,%s,%s\n", savedNif, savedPassword, savedName, savedAddress);
            }
        }

        // Fechar os arquivos
        fclose(usersFile);
        fclose(newFile);

        if (userRemoved) {
            // Renomear o arquivo de usu?rios
            if (remove("users.txt") == 0) {
                if (rename("new_users.txt", "users.txt") != 0) {
                    printf("Erro ao renomear o arquivo de usu?rios.\n");
                }
                else {
                    printf("Usu?rio removido com sucesso.\n");
                }
            }
            else {
                printf("Erro ao remover o usu?rio.\n");
            }
        }
        else {
            // Remover o novo arquivo de usu?rios, j? que nenhum usu?rio foi removido
            remove("new_users.txt");
            printf("Usu?rio n?o encontrado.\n");
        }
    }
    else {
        printf("N?o foi poss?vel abrir o arquivo de usu?rios.\n");
        exit(1);
    }
}