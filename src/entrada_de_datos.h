#ifndef ENTRADA_DE_DATOS_H_
#define ENTRADA_DE_DATOS_H_

/**
 * \brief Solicita un numero al usuario de tipo int, luego de verificarlo devuelve el resultado
 * \ param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \ param mensaje Es el mensaje a ser mostrado
 * \ param mensajeError Es el mensaje de Error a ser mostrado
 * \ param min Es el numero maximo a ser aceptado
 * \ param max Es el minimo minimo a ser aceptado
 * \ param retries Es la cantidad de intentos que tiene para ingresar un numero valido
 * \return Retorna 0 si se obtuvo el numero y -1 si no
 */
int getNumber(int *pReturn, char *message, char *errorMessage, int min, int max, int retries);

/**
 * \brief Solicita un numero al usuario de tipo float, luego de verificarlo devuelve el resultado
 * \ param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \ param mensaje Es el mensaje a ser mostrado
 * \ param mensajeError Es el mensaje de Error a ser mostrado
 * \ param min Es el numero maximo a ser aceptado
 * \ param max Es el minimo minimo a ser aceptado
 * \ param retries Es la cantidad de intentos que tiene para ingresar un numero valido
 * \return Retorna 0 si se obtuvo el numero y -1 si no
 */
int getFloatNumber(float *pReturn, char *message, char *errorMessage, int min, int max, int retries);

/**
 * \brief Solicita una cadena al usuario, luego de validarla la devuelve
 * \ param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \ param mensaje Es el mensaje a ser mostrado
 * \ param mensajeError Es el mensaje de Error a ser mostrado
 * \ param minimo Es la longitud minima del texto
 * \ param maximo Es la longitud maxima del texto
 * \return Retorna 0 si se obtuvo el numero y -1 si no
 */
int getText(char *pReturn, char *message, char *errorMessage, int len, int retries);

int getTarjeta(char *pReturn, char *message, char *errorMessage, int len, int retries);

int confirmarAccion(char *message, char *errorMessage);

#endif /* ENTRADA_DE_DATOS_H_ */
