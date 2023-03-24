/**
 * @file account.h
 * @brief Header file for account management.
 */

#ifndef ACCOUNT_H
#define ACCOUNT_H

 /**
  * @brief Struct representing a user account.
  */
struct User {
    unsigned int nif; /**< N?mero de identifica??o fiscal do usu?rio. */
    char password[20]; /**< Senha do usu?rio. */
    char name[50]; /**< Nome do usu?rio. */
    char address[100]; /**< Endere?o do usu?rio. */
    float balance; /**< Saldo do usu?rio. */
};

/**
 * @brief Register a new user account.
 */
void registerUser();

/**
 * @brief Login to an existing user account.
 */
void loginUser();

/**
 * @brief Remove an existing user account.
 */
void removeData();

/**
 * @brief Update the information of an existing user account.
 */
void updateData();

#endif