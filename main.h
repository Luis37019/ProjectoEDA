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

* @brief Fun??o que permite o registro de um novo usu?rio no sistema.
*
*/
void registerUser();

/**

* @brief Fun??o que permite o login de um usu?rio j? cadastrado no sistema.
*
*/
void loginUser();

/**

* @brief Fun??o que permite a remo??o dos dados de um usu?rio do sistema.
*
*/
void removeData();

/**

* @brief Fun??o que permite a atualiza??o dos dados de um usu?rio do sistema.
*
*/
void updateData();

/**
 * @brief Fun??o para registrar um novo gestor no sistema.
 *
 * @return void
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

/**
 * @brief Fun??o para ver o saldo do usu?rio.
 *
 * @return void
 */
void viewBalance();

/**
 * @brief Fun??o para adicionar dinheiro ao saldo na conta do usu?rio.
 *
 * @return void
 */
void addBalance();
/**
 * @brief Fun??o para visualizar lista de clientes.
 *
 * @return void
 */
void showUsers();
/**
 * @brief Fun??o para remover a conta do cliente.
 *
 * @return void
 */
void removeUser();
/**
 * @brief Fun??o para adicionar transporte ? base de dados.
 *
 * @param transport o transporte a ser adicionado
 * @return void
 */
void add_transport(transports_data transport);

/**
 * @brief Fun??o para remover transporte da base de dados.
 *
 * @param id o id do transporte a ser removido
 * @return void
 */
void remove_transport(int id);

/**
 * @brief Fun??o para editar transporte na base de dados.
 *
 * @param id o id do transporte a ser editado
 * @param new_transport o novo transporte
 * @return void
 */
void edit_transport(int id, transports_data new_transport);

#endif //MAIN_H