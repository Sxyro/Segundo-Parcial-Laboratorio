#ifndef SALIDA_DE_DATOS_H_
#define SALIDA_DE_DATOS_H_
#define MSG_INGRESO_MENU "\n-> Ingrese opcion: "
#define MSG_ERROR_MENU "Ha ocurrido un error, reintente.\n"
#define RETRIES 2

/**
 * \brief Solicita al usuario una opcion del menu principal.
 * \return Retorna la opcion ingresada.
 */
int menuPrincipal();

int menuEditarJugador();

int mostrarListados(LinkedList* pArrayListJugador, LinkedList* pArrayListSeleccion);

int systemPause(char* message);

#endif /* SALIDA_DE_DATOS_H_ */
