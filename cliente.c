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
 * @brief Função para visualizar o saldo de um usuário.
 *
 * @param nif Número de identificação fiscal do usuário.
 *
 * @return void
 */
void viewBalance(unsigned int nif) {
    char line[100]; /**< Linha atual do arquivo de usuários. */
    char name[50]; /**< Nome do usuário. */
    double balance = 0; /**< Saldo do usuário. */

    // Abrir o arquivo de usuários no modo de leitura
    FILE* usersFile = fopen("users.txt", "r");

    // Verificar se o arquivo foi aberto corretamente
    if (usersFile != NULL) {
        // Ler cada linha do arquivo
        while (fgets(line, 100, usersFile) != NULL) {
            struct User user = { 0 };
            sscanf(line, "%u,%[^,],%[^,],%[^,],%lf", &user.nif, user.password, user.name, user.address, &user.balance);

            // Verificar se o número de identificação fiscal é o mesmo que o passado como argumento
            if (user.nif == nif) {
                // Armazenar o nome e o saldo do usuário
                strcpy(name, user.name);
                balance = user.balance;
                break;
            }
        }

        // Fechar o arquivo
        fclose(usersFile);
    }
    else {
        printf("Erro ao abrir o arquivo de usuários.\n");
        return;
    }

    // Mostrar o nome e o saldo do usuário
    printf("O saldo de %s é R$%.2lf.\n", name, balance);
}

/**
 * @brief Função para adicionar saldo a um usuário.
 *
 */
void addBalance() {
    unsigned int nif; /**< Número de identificação fiscal do usuário */
    char password[20]; /**< Senha do usuário */
    char line[100]; /**< Linha atual do arquivo de usuários */
    char tempLine[100]; /**< Linha temporária a ser escrita no arquivo */
    float balanceToAdd; /**< Valor a ser adicionado ao saldo */
    int userFound = 0; /**< Flag para indicar se o usuário foi encontrado */

    printf("Digite o número de NIF (até 20 caracteres): ");
    scanf("%u", &nif);

    printf("Digite uma senha (até 20 caracteres): ");
    scanf("\n%s", password);

    // Abrir o arquivo de usuários no modo de leitura e escrita
    FILE* usersFile = fopen("users.txt", "r+");

    // Verificar se o arquivo foi aberto corretamente
    if (usersFile != NULL) {
        // Ler cada linha do arquivo
        while (fgets(line, 100, usersFile) != NULL) {
            // Extrair as informações da linha
            unsigned int savedNif = 0;
            char savedPassword[20] = { 0 };
            char name[50] = { 0 };
            char address[100] = { 0 };
            float balance = 0.0;
            sscanf(line, "%u,%[^,],%[^,],%[^,],%f", &savedNif, savedPassword, name, address, &balance);

            // Verificar se as informações de login coincidem
            if (savedNif == nif && strcmp(password, savedPassword) == 0) {
                printf("Login bem-sucedido. Bem-vindo, %s!\n", name);
                userFound = 1; // Atualiza a flag

                // Pedir ao usuário que informe o valor a ser adicionado ao saldo
                printf("Digite o valor a ser adicionado ao saldo: ");
                scanf("%f", &balanceToAdd);

                // Adicionar o valor ao saldo atual
                balance += balanceToAdd;

                // Escrever as informações atualizadas do usuário no arquivo temporário
                sprintf(tempLine, "%u,%s,%s,%s,%f\n", savedNif, savedPassword, name, address, balance);

                // Voltar para o início da linha do usuário no arquivo
                fseek(usersFile, strlen(line), SEEK_CUR);

                // Sobrescrever a linha do usuário com as informações atualizadas
                fputs(tempLine, usersFile);

                // Fechar o arquivo
                fclose(usersFile);

                // Indicar que a operação foi concluída com sucesso
                printf("Saldo atualizado com sucesso!\n");
                return;
            }
        }

        // Fechar o arquivo
        fclose(usersFile);
    }

    // Se o usuário não foi encontrado, exibir uma mensagem de erro
    if (!userFound) {
        printf("Usuário não encontrado ou senha incorreta. Tente novamente.\n");
    }
}
