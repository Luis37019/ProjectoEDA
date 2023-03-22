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
