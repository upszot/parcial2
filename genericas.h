#ifndef GENERICAS_H_INCLUDED
#define GENERICAS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#endif // GENERICAS_H_INCLUDED
//#------------- Genericas -------------#

/** \brief Imprime menu en pantalla
 *
 * \param opciones char*
 * \return void
 *
 */
void menu(char *opciones);

/** \brief Imprime mensaje de Error con sus respectivos codigos y la opcion de menu donde ocurrio para facilitar el debuger
 *
 * \param mensaje int
 * \param Error int
 * \return void
 *
 */
void sms_error(int mensaje,int Error);

/** \brief devuelve un punteero a una cadena de caracteres
 *
 * \param sms char*
 * \param LongitudCadena int
 * \return char*
 *
 */
char *get_char(char *sms,int LongitudCadena);

/** \brief Devuelve un Nro Entero valuado entre un rango dado.
 *
 * \param sms char*
 * \param desde int
 * \param hasta int
 * \return int
 *
 */
int get_int_Rango(char *sms,int desde,int hasta);


