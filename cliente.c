/**
 * @file main.c
 * @brief Implementação da função principal do programa.
 */

 /**
 * @brief Define para desativar as mensagens de aviso do compilador relacionadas à segurança da função scanf.
 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"



/**
 * @brief Função para criar conta para cliente.
 */
void registerUser() {
    /**
     * @brief Estrutura de dados que representa um novo usuário.
     */
    struct User newUser = { 0 };
    printf("Digite o número de NIF (até 20 caracteres): ");
    scanf("%u", &newUser.nif);

    printf("Digite uma senha (até 20 caracteres): ");
    scanf("\n%s", newUser.password);

    printf("Digite o nome do usuário (até 50 caracteres): ");
    scanf("\n%[^\n]", newUser.name);

    printf("Digite o endereço do usuário (até 100 caracteres): ");
    scanf("\n%[^\n]", newUser.address);

    newUser.balance = 0.0;

    // Abrir o arquivo de usuários no modo de escrita
    FILE* usersFile = fopen("users.txt", "a");

    // Verificar se o arquivo foi aberto corretamente
    if (usersFile == NULL) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return;
    }

    // Escrever as informações do novo usuário no arquivo
    fprintf(usersFile, "%u,%s,%s,%s,%f\n", newUser.nif, newUser.password, newUser.name, newUser.address, newUser.balance);

    // Fechar o arquivo
    fclose(usersFile);

    printf("Usuário cadastrado com sucesso.\n");
}
/**
 * @brief Função para verificar as informações de login do usuário.
 *
 * @return void
 */
void loginUser() {
    unsigned int nif;
    char password[20];
    char line[50];
    printf("Digite o número de NIF (até 20 caracteres): ");
    scanf("%u", &nif);

    printf("Digite uma senha (até 20 caracteres): ");
    scanf("\n%s", password);

    FILE* usersFile = fopen("users.txt", "r");

    if (usersFile != NULL) {
        unsigned int savedNif = 0;
        char savedPassword[20] = { 0 };
        int loginSuccess = 0;

        while (fgets(line, 50, usersFile) != NULL) {
            sscanf(line, "%u,%[^,],%*[^\n]", &savedNif, savedPassword);

            if (savedNif == nif && strcmp(password, savedPassword) == 0) {
                printf("Login bem-sucedido. Bem-vindo, %u!\n", nif);
                loginSuccess = 1;
                fclose(usersFile);
                break;
            }
        }

        if (!loginSuccess) {
            printf("Login sem sucesso...\n");
        }

        fclose(usersFile);
    }
    else {
        printf("Login sem sucesso...\n");
    }
}
/**
 * @brief Função para remover os dados de um usuário.
 *
 */
void removeData() {
    unsigned int nif; /**< Número de identificação fiscal do usuário */
    char password[20]; /**< Senha do usuário */
    char line[50]; /**< Linha atual do arquivo de usuários */
    char newLine[50]; /**< Nova linha a ser escrita no arquivo temporário */

    printf("Digite o número de NIF (até 20 caracteres): ");
    scanf("%u", &nif);

    printf("Digite uma senha (até 20 caracteres): ");
    scanf("\n%s", password);

    // Abrir o arquivo de usuários no modo de leitura
    FILE* usersFile = fopen("users.txt", "r");

    // Verificar se o arquivo foi aberto corretamente
    if (usersFile != NULL) {
        // Criar um arquivo temporário para armazenar as informações sem o usuário removido
        FILE* tempFile = fopen("temp.txt", "w");

        // Verificar se o arquivo temporário foi criado corretamente
        if (tempFile == NULL) {
            printf("Erro ao criar arquivo temporário.\n");
            fclose(usersFile);
            return;
        }

        unsigned int savedNif = 0; /**< Número de identificação fiscal armazenado no arquivo */
        char savedPassword[20] = { 0 }; /**< Senha armazenada no arquivo */
        int removeSuccess = 0; /**< Flag para indicar se a remoção foi bem-sucedida ou não */

        // Ler cada linha do arquivo
        while (fgets(line, 50, usersFile) != NULL) {
            sscanf(line, "%u,%[^\n]\n", &savedNif, savedPassword);

            // Verificar se as informações de login coincidem
            if (savedNif == nif && strcmp(password, savedPassword) == 0) {
                printf("Removendo dados do usuário %u...\n", nif);
                removeSuccess = 1; // Atualiza a flag
            }
            else {
                // Escrever a linha atual no arquivo temporário
                sprintf(newLine, "%u,%s\n", savedNif, savedPassword);
                fputs(newLine, tempFile);
            }
        }

        // Fechar os arquivos
        fclose(usersFile);
        fclose(tempFile);

        // Remover o arquivo original e renomear o arquivo temporário
        if (removeSuccess) {
            if (remove("users.txt") != 0) {
                printf("Erro ao remover arquivo original.\n");
                return;
            }
            if (rename("temp.txt", "users.txt") != 0) {
                printf("Erro ao renomear arquivo temporário.\n");
                return;
            }
            printf("Dados removidos com sucesso.\n");
        }
    }
}
/**
 * @brief Função para alterar os dados de um usuário.
 * @details Esta função lê o número de NIF e a senha do usuário a ser atualizado, verifica se as informações coincidem com um usuário registrado, solicita a nova senha e atualiza o arquivo de usuários com as informações atualizadas.
 *
 * @note O arquivo de usuários deve estar no formato "NIF,SENHA".
 *
 * @note O tamanho máximo para o número de NIF e senha é 20 caracteres.
 *
 * @warning Esta função sobrescreve o arquivo de usuários com as informações atualizadas.
 */
void updateData() {
    unsigned int nif; /**< Número de NIF (até 20 caracteres) do usuário. */
    char password[20]; /**< Senha atual (até 20 caracteres) do usuário. */
    char newPassword[20]; /**< Nova senha (até 20 caracteres) do usuário. */
    char line[50]; /**< String que armazena uma linha do arquivo de usuários. */
    char newLine[50]; /**< String que armazena a nova linha atualizada no arquivo. */

    printf("Digite o número de NIF (até 20 caracteres): ");
    scanf("%u", &nif);

    printf("Digite a senha atual (até 20 caracteres): ");
    scanf("\n%s", password);

    // Abrir o arquivo de usuários no modo de leitura
    FILE* usersFile = fopen("users.txt", "r");

    // Verificar se o arquivo foi aberto corretamente
    if (usersFile != NULL) {
        // Criar um arquivo temporário para armazenar as informações com o usuário atualizado
        FILE* tempFile = fopen("temp.txt", "w");

        // Verificar se o arquivo temporário foi criado corretamente
        if (tempFile == NULL) {
            printf("Erro ao criar arquivo temporário.\n");
            fclose(usersFile);
            return;
        }

        unsigned int savedNif = 0; /**< Número de NIF (até 20 caracteres) salvo no arquivo. */
        char savedPassword[20] = { 0 }; /**< Senha salva no arquivo (até 20 caracteres). */
        int updateSuccess = 0; /**< Flag para indicar se a atualização foi bem-sucedida ou não. */

        // Ler cada linha do arquivo
        while (fgets(line, 50, usersFile) != NULL) {
            sscanf(line, "%u,%[^\n]\n", &savedNif, savedPassword);

            // Verificar se as informações de login coincidem
            if (savedNif == nif && strcmp(password, savedPassword) == 0) {
                printf("Senha atual correta. Digite a nova senha (até 20 caracteres): ");
                scanf("\n%s", newPassword);

                // Escrever a linha atualizada no arquivo temporário
                sprintf(newLine, "%u,%s\n", savedNif, newPassword);
                fputs(newLine, tempFile);
            }
        }

        // Fechar os arquivos
        fclose(usersFile);
        fclose(tempFile);

        // Remover o arquivo original e renomear o arquivo temporário
        remove("users.txt");
        rename("temp.txt", "users.txt");

        // Verificar se a atualização foi bem-sucedida
        if (updateSuccess) {
            printf("Senha atualizada com sucesso.\n");
        }
        else {
            printf("Não foi possível atualizar a senha.\n");
        }
    }
    else {
        printf("Não foi possível abrir o arquivo de usuários.\n");
    }
} 
/**
 * @brief Estrutura de dados que representa as informações de saldo de um usuário.
 */
struct Balance {
    unsigned int nif; /**< Número de identificação fiscal do usuário */
    float amount; /**< Saldo atual do usuário */
};
/**
 * @brief Função para visualizar o saldo do usuário.
 *
 * @param[in] nif Número de identificação fiscal do usuário.
 */
void viewBalance(unsigned int nif) {
    FILE* usersFile = fopen("users.txt", "r");
    unsigned int savedNif = 0;
    char savedPassword[20] = { 0 };
    char savedName[50] = { 0 };
    char savedAddress[100] = { 0 };
    float savedBalance = 0.0;
    int balanceFound = 0;

    if (usersFile != NULL) {
        while (fscanf(usersFile, "%u,%[^,],%[^,],%[^,],%f\n", &savedNif, savedPassword, savedName, savedAddress, &savedBalance) == 5) {
            if (savedNif == nif) {
                printf("O saldo do usuário %u é %.2f.\n", nif, savedBalance);
                balanceFound = 1;
                break;
            }
        }

        if (!balanceFound) {
            printf("Usuário não encontrado.\n");
        }

        fclose(usersFile);
    }
    else {
        printf("Erro ao abrir o arquivo de usuários.\n");
    }
}
/**
 * @brief Função para adicionar saldo à conta do usuário.
 *
 */

void addBalance(float* balance) {
    // function body
    unsigned int nif; /**< Número de identificação fiscal do usuário */
    char password[20]; /**< Senha do usuário */
    char line[100]; /**< Linha atual do arquivo de usuários */
    char newLine[100]; /**< Nova linha a ser escrita no arquivo temporário */
    float balanceToAdd; /**< Valor a ser adicionado ao saldo */
    int loginSuccess = 0; /**< Flag para indicar se o login foi bem-sucedido ou não */

    printf("Digite o número de NIF (até 20 caracteres): ");
    scanf("%u", &nif);

    printf("Digite uma senha (até 20 caracteres): ");
    scanf("\n%s", password);

    // Abrir o arquivo de usuários no modo de leitura
    FILE* usersFile = fopen("users.txt", "r");

    // Verificar se o arquivo foi aberto corretamente
    if (usersFile == NULL) {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return;
    }

    // Criar um arquivo temporário para armazenar as informações atualizadas
    FILE* tempFile = fopen("temp.txt", "w");

    // Verificar se o arquivo temporário foi criado corretamente
    if (tempFile == NULL) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(usersFile);
        return;
    }

    unsigned int savedNif = 0; /**< Número de identificação fiscal armazenado no arquivo */
    char savedPassword[20] = { 0 }; /**< Senha armazenada no arquivo */
    char name[50] = { 0 }; /**< Nome do usuário */
    char address[100] = { 0 }; /**< Endereço do usuário */
    float savedBalance = 0.0; /**< Saldo atual do usuário */

    // Ler cada linha do arquivo
    while (fgets(line, 100, usersFile) != NULL) {
        sscanf(line, "%u,%[^,],%[^,],%[^,],%f\n", &savedNif, savedPassword, name, address, &savedBalance);

        // Verificar se as informações de login coincidem
        if (savedNif == nif && strcmp(password, savedPassword) == 0) {
            printf("Login bem-sucedido. Bem-vindo, %s!\n", name);
            loginSuccess = 1; // Atualiza a flag

            // Pedir ao usuário para informar o valor a ser adicionado ao saldo 
            printf("Digite o valor a ser adicionado ao saldo: ");
            scanf("%f", &balanceToAdd);

            // Atualizar o saldo do usuário
            savedBalance += balanceToAdd;

            // Escrever a nova linha atualizada no arquivo temporário
            sprintf(newLine, "%u,%s,%s,%s,%.2f\n", savedNif, savedPassword, name, address, savedBalance);
            fputs(newLine, tempFile);
        }
        else {
            // Escrever a linha original no arquivo temporário
            fputs(line, tempFile);
        }
    }

    // Fechar os arquivos
    fclose(usersFile);
    fclose(tempFile);

    // Substituir o arquivo original pelo arquivo temporário
    if (rename("temp.txt", "users.txt") != 0) {
        printf("Erro ao atualizar o arquivo de usuários.\n");
        return;
    }

    // Se o login não foi bem-sucedido, exibir uma mensagem de erro
    if (!loginSuccess) {
        printf("NIF ou senha inválidos. Tente novamente.\n");
    }
}