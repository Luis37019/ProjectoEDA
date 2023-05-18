#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "gestor.h"
#include "cliente.h"
#include <ctype.h>
#include "transportes.h"

/**
* @file main.h
* @brief Arquivo de cabe?alho contendo a defini??o das fun??es do programa.
*
*/

#ifndef MAIN_H
#define MAIN_H

/**
* @brief Funcao que permite o registro de um novo usu?rio no sistema.
*
*/
void registerUser();

/**
* @brief Funcao que permite o login de um usu?rio j? cadastrado no sistema.
*
*/
void loginUser(User* logged_account);

/**
* @brief Funcao que permite a remo??o dos dados de um usu?rio do sistema.
*
*/
void removeData(unsigned int nif, char password[]);

/**
* @brief Funcao que permite a atualiza??o dos dados de um usu?rio do sistema.
*
*/
void updateData(loggedInAccount);

/**
 * @brief Funcao para registrar um novo gestor no sistema.
 *
 * @return void
 */
void registerGestor();

/**
 * @brief Funcao para verificar as informa??es de login do gestor.
 *
 * @return void
 */
void loginGestor(Gestor* logged_account);

/**
 * @brief Funcao para mostrar a lista de usu?rios.
 *
 * @return void
 */
void showUsers();

/**
 * @brief Funcao para remover uma conta de usu?rio.
 *
 * @return void
 */
void removeUsers(unsigned int nif);

/**
 * @brief Funcao para ver o saldo do usu?rio.
 *
 * @return void
 */
void viewBalance(loggedInAccount);

/**
 * @brief Funcao para adicionar dinheiro ao saldo na conta do usu?rio.
 *
 * @return void
 */
void addBalance(loggedInAccount);
/**
 * @brief Funcao para visualizar lista de clientes.
 *
 * @return void
 */
void showUsers();
/**
 * @brief Funcao para remover a conta do cliente.
 *
 * @return void
 */
void removeUser();
/**
 * @brief Funcao para adicionar transporte ? base de dados.
 *
 * @param transport o transporte a ser adicionado
 * @return void
 */
void addTransport(unsigned int id, int type, int battery, int autonomy, const char* geocode);


/**
 * @brief Fun??o para remover transporte da base de dados.
 *
 * @param id o id do transporte a ser removido
 * @return void
 */
void removeTransport();

/**
 * @brief Fun??o para editar transporte na base de dados.
 *
 * @param id o id do transporte a ser editado
 * @param new_transport o novo transporte
 * @return void
 */
void updateTransport();
void updateGestor(Gestor* logged_account);
void loadTransport();
void displayTransportByGeocode(const char* geocode);
void registerTransport();

#endif //MAIN_H