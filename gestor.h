#ifndef GESTOR_H
#define GESTOR_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * @brief Estrutura de dados que representa um gestor.
 */
struct Gestor {
    unsigned int nif; /**< N?mero de identifica??o fiscal do gestor. */
    char password[20]; /**< Senha do gestor. */
    char name[50]; /**< Nome do gestor. */
    char address[100]; /**< Endere?o do gestor. */
};

/**
 * @brief Fun??o para criar conta para gestor.
 */
void registerGestor();

/**
 * @brief Fun??o para verificar as informa??es de login do gestor.
 *
 * @return void
 */
void loginGestor();

/**
 * @brief Fun??o para mostrar a lista de usu?rios.
 *
 * @return void
 */
void showUsers();

/**
 * @brief Fun??o para remover uma conta de usu?rio.
 *
 * @return void
 */
void removeUser();

#endif //GESTOR_H
