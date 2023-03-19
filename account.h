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
    unsigned int nif; /**< NIF number of the user (up to 20 characters). */
    char password[20]; /**< Password of the user (up to 20 characters). */
    char name[50]; /**< Name of the user (up to 50 characters). */
    char address[100]; /**< Address of the user (up to 100 characters). */
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