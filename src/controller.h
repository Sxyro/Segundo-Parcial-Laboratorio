#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include "LinkedList.h"

int controller_cargarUltimoId();

int controller_guardarUltimoId();

int controller_buscarId(LinkedList* pArrayListVenta, int idVenta);

/** \brief Carga los datos de los jugadores desde el archivo jugadores.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListVenta LinkedList*
 * \return int
 *
 */
int controller_cargarVentasDesdeTexto(char* path , LinkedList* pArrayListVenta);

int controller_cargarVentasDesdeBinario(char* path , LinkedList* pArrayListVenta);

int controller_guardarVentasModoTexto(char* path , LinkedList* pArrayListVenta);

int controller_guardarJugadoresModoBinario(char* path , LinkedList* pArrayListVenta);

int controller_agregarVenta(LinkedList* pArrayListVenta);

int controller_editarVenta(LinkedList *pArrayListVenta);

int controller_borrarVenta(LinkedList* pArrayListVenta);

int controller_listarVentas(LinkedList* pArrayListVenta);

/** \brief Guarda los datos de los jugadores en el archivo binario.
 *
 * \param path char*
 * \param pArrayListVenta LinkedList*
 * \return int
 *
 */
int controller_guardarVentasModoBinario(char* path , LinkedList* pArrayListVenta);

int controller_generarInforme(char* path, LinkedList* pArrayListVenta);

#endif /* CONTROLLER_H_ */
