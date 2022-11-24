#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "entrada_de_datos.h"

static int myGets(char *cadena, int longitud);
static int getInt(int *pResultado);
static float getFloat(float *pResultado);
static int getString(char *cadena);
static int esNumerica(char *cadena);
static int esNumericoDecimal(char *cadena);
static int esTexto(char *cadena);
static int normalizarTexto(char *cadena);

/**
 * \brief Lee de stdin hasta que encuentra un '\n' o hasta que haya copiado en cadena
 * un máximo de ' longitud - 1' caracteres .
 * \ param pResultado Puntero al espacio de memoria donde se copiara la cadena obtenida
 * \ param longitud Define el tamaño de cadena
 * \return Retorna 0 (EXITO) si se obtiene una cadena y -1 (ERROR) si no
 *
 */
static int myGets(char *cadena, int longitud) {
	if (cadena != NULL && longitud > 0 && fgets(cadena, longitud, stdin) == cadena) {
		fflush(stdin);
		if (cadena[strlen(cadena) - 1] == '\n') {
			cadena[strlen(cadena) - 1] = '\0';
		}
		return 0;
	}
	return -1;
}

/**
 * \brief Transforma la cadena validada a un entero
 * \ param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 0 (EXITO) si se obtiene un numero entero y -1 (ERROR) si no
 *
 */
static int getInt(int *pResultado) {
	int noError = -1;
	char buffer[64];
	if (pResultado != NULL) {
		if (myGets(buffer, sizeof(buffer)) == 0 && esNumerica(buffer) == 1) {
			*pResultado = atoi(buffer);
			noError = 0;
		}
	}
	return noError;
}

static float getFloat(float *pResultado) {
	float noError = -1;
	char buffer[64];
	if (pResultado != NULL) {
		if (myGets(buffer, sizeof(buffer)) == 0 && esNumericoDecimal(buffer)) {
			*pResultado = atof(buffer);
			noError = 0;
		}
	}
	return noError;
}

/**
 * \brief Valida que lo que se le ingreso sea una cadena
 * \ param pResultado Puntero al espacio de memoria donde se dejara el resultado de la funcion
 * \return Retorna 0 (EXITO) si no obtiene numeros ni caracteres distintos de letras y -1 (ERROR) si obtiene alguno
 */
static int getString(char *cadena) {
	int noError = -1;
	char buffer[64];
	if (cadena != NULL) {
		if (myGets(buffer, sizeof(buffer)) == 0)
		{
			if (esTexto(buffer) == 1) {
				strcpy(cadena, buffer);
				noError = 0;
			}
		}
	}
	return noError;
}

/**
 * \brief Verifica si la cadena ingresada es numerica
 * \ param cadena Cadena de caracteres a ser analizada
 * \return Retorna 1 ( verdadero ) si la cadena es numerica y -1 ( falso ) si no lo es
 */
static int esNumerica(char *cadena) {
	int i = 0;
	int noError = -1;
	int longitud = strlen(cadena);
	if (cadena != NULL && longitud > 0) {
		while (i < longitud) {

			if ((cadena[i] >= '0' && cadena[i] <= '9')) {
				noError = 1;
			} else {
				noError = -1;
				break;
			}
			i++;
		}
	}
	return noError;
}

/**
 * \brief Verifica si la cadena ingresada es numerica
 * \ param cadena Cadena de caracteres a ser analizada
 * \return Retorna 1 ( verdadero ) si la cadena es numerica y -1 ( falso ) si no lo es
 */
static int esNumericoDecimal(char *cadena) {
	int i = 0;
	int noError = -1;
	int longitud = strlen(cadena);
	if (cadena != NULL && longitud > 0) {
		while (i < longitud) {

			if ((cadena[i] >= '0' && cadena[i] <= '9') || cadena[i] == '.') {
				noError = 1;
			} else {
				noError = -1;
				break;
			}
			i++;
		}
	}
	return noError;
}

/**
 * \brief Verifica si la cadena ingresada es texto, es decir, letras.
 * \ param cadena Cadena de caracteres a ser analizada
 * \return Retorna 1 ( verdadero ) si la cadena es numerica y -1 ( falso ) si no lo es
 */
static int esTexto(char *cadena) {
	int i = 0;
	int noError = -1;
	int longitud = strlen(cadena);
	if (cadena != NULL && longitud > 0) {
		while (i < longitud) {

			if ((cadena[i] >= 'a' && cadena[i] <= 'z') || (cadena[i] >= 'A' && cadena[i] <= 'Z') || cadena[i] == ' ') {
				noError = 1;
			} else {
				noError = -1;
				break;
			}
			i++;
		}
	}
	return noError;
}

static int normalizarTexto(char *cadena) {

	int noError;
	int tam;
	if (cadena != NULL) {
		strlwr(cadena);
		cadena[0] = toupper(cadena[0]);
		tam = strlen(cadena);
		for (int i = 0; i < tam; i++)
		{
			if ((cadena[i] == 32)) {
				cadena[i+1] = toupper(cadena[i+1]);
			}
		}
		noError = 0;
	}
	return noError;
}

int getNumber(int *pReturn, char *message, char *errorMessage, int min, int max, int retries) {
	int bufferInt;
	int noError = -1;
	while (retries > 0) {
		retries--;
		printf("%s", message);
		if (getInt(&bufferInt) == 0) {
			if (bufferInt >= min && bufferInt <= max) {
				*pReturn = bufferInt;
				noError = 0;
				break;
			}
		}
		printf("\n%s\n-> Fallos restantes: %d\n-> Rango aceptado: (%d-%d)\n", errorMessage, retries, min, max);
	}
	return noError;
}

int getFloatNumber(float *pReturn, char *message, char *errorMessage, int min, int max, int retries) {
	float bufferFloat;
	int noError = -1;
	while (retries > 0) {
		retries--;
		printf("%s", message);
		if (getFloat(&bufferFloat) == 0) {
			if (bufferFloat >= min && bufferFloat <= max) {
				*pReturn = bufferFloat;
				noError = 0;
				break;
			}
		}
		printf("\n%s\n-> Fallos restantes: %d\n-> Rango aceptado: (%d-%d)\n", errorMessage, retries, min, max);
	}
	return noError;
}

int getText(char *pReturn, char *message, char *errorMessage, int len, int retries)
{
	char bufferString[64];
	int noError = -1;

	while (retries > 0) {
		retries--;
		printf("%s", message);
		if (getString(bufferString) == 0 && strlen(bufferString) >= 3 && strlen(bufferString) <= len) {
				normalizarTexto(bufferString);
				strcpy(pReturn, bufferString);
				noError = 0;
				break;
		}
		printf("\n%s\n-> Fallos restantes: %d\n-> Rango aceptado: (3-%d)\n", errorMessage, retries, len);
	}
	return noError;
}

int getTarjeta(char *pReturn, char *message, char *errorMessage, int len, int retries) {
	char bufferString[64];
	int noError = -1;

	while (retries > 0) {
		retries--;
		printf("%s", message);
		if (myGets(bufferString, sizeof(bufferString)) == 0 && esNumerica(bufferString) == 1) {

			if (strlen(bufferString) == len) {
				normalizarTexto(bufferString);
				strcpy(pReturn, bufferString);
				noError = 0;
				break;
			}
			printf("\n%s\n-> Fallos restantes: %d\n-> Longitud requerida: %d\n", errorMessage, retries, len);
		}
	}
	return noError;
}

int confirmarAccion(char *message, char *errorMessage)
{
	int retorno;
	getNumber(&retorno, message, errorMessage, 0, 1, 2);
	return retorno;
}
