#include <stdio.h>
#include <stdlib.h>
#include "ventas.h"
#include "controller.h"
#include "LinkedList.h"
#include "parser.h"
#include "entrada_de_datos.h"
#include "salida_de_datos.h"

int ultimoId = 100;
/** \brief Retorna el id incrementado
 * \return Retorna el id incrementado
 */
static int idIncremental(){
	ultimoId++;
	return ultimoId;
}

/** \brief Carga el ultimo ID almacenado del archivo de texto
 * \return Retorna 0 si no hubo error y -1 si algo fallo.
 */
int controller_cargarUltimoId(){

	int noError = -1;
	FILE* pArchivo;
	char id[20];

	pArchivo = fopen("last_id.csv", "r");

	if(pArchivo != NULL && fscanf(pArchivo, "%s", id) == 1 ){
		ultimoId = atoi(id);
		fclose(pArchivo);
		noError = 0;
	}
	return noError;
}

int controller_guardarUltimoId(){

	int noError = -1;
	FILE* pArchivo;

	pArchivo = fopen("last_id.csv", "w");

	if(pArchivo != NULL){
		fprintf(pArchivo, "%d", ultimoId);
		fclose(pArchivo);
		noError = 0;
	}
	return noError;
}

int controller_buscarId(LinkedList* pArrayListVenta, int idVenta) {

	int retorno = -1;
    eVenta* pVenta = NULL;
    int tam, bufferId;

	if(pArrayListVenta != NULL && idVenta > 0){

		tam = ll_len(pArrayListVenta);

		for(int i = 0; i < tam; i++){
			pVenta = (eVenta*)ll_get(pArrayListVenta, i);
			if(pVenta != NULL && !getIdVenta(pVenta, &bufferId) && idVenta == bufferId){
				retorno = i;
				break;
			}
		}
	} else {
		printf("Ha ocurrido un error.");
	}
	return retorno;
}

/** \brief Carga los datos de los jugadores desde el archivo jugadores.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListVenta LinkedList*
 * \return int
 */
int controller_cargarVentasDesdeTexto(char* path , LinkedList* pArrayListVenta)
{
    int noError = -1;
    FILE* pArchivo;
    if(path != NULL && pArrayListVenta != NULL)
    {
        pArchivo = fopen(path,"r");
        if(pArchivo != NULL)
        {
            if(parser_VentaFromText(pArchivo, pArrayListVenta) == 0){

            	controller_cargarUltimoId();
                printf("Se cargo correctamente el archivo de ventas.\n");

            }else{
                 printf("Ha ocurrido un error\n");
            }
        }
        fclose(pArchivo);
        noError = 0;
    }
    return noError;
}

/** \brief Carga los datos de los jugadores desde el archivo generado en modo binario.
 *
 * \param path char*
 * \param pArrayListVenta LinkedList*
 * \return int
 *
 */
int controller_cargarVentasDesdeBinario(char* path , LinkedList* pArrayListVenta)
{
    int noError = -1;
    FILE* pArchivo;

    if(path != NULL && pArrayListVenta != NULL)
    {
        pArchivo = fopen(path,"rb");

        if(pArchivo!=NULL)
        {
            if(parser_VentaFromBinary(pArchivo, pArrayListVenta)){

                printf("Se leyo el archivo correctamente\n");

            }else{

                 printf("ERROR al leer el archivo\n");
            }

        }
        fclose(pArchivo);
        noError = 0;
    }
    return noError;
}

int controller_guardarVentasModoTexto(char* path , LinkedList* pArrayListVenta)
{
    int retorno = 0;
    FILE* pArchivo;
    int longitud;
    eVenta *auxVenta;
    int auxIdVenta, auxDiaVenta, auxMesVenta, auxAnioVenta, auxCantidadVenta;
    char auxModelo[100], auxTarjetaVenta[100];
    float auxPrecioVenta;

    if(path != NULL && pArrayListVenta != NULL)
    {
        pArchivo = fopen(path,"w");

        if(pArchivo != NULL)
        {
            longitud = ll_len(pArrayListVenta);
            for(int i = 0; i < longitud ; i++){

                auxVenta = ll_get(pArrayListVenta, i);

                if(getIdVenta(auxVenta, &auxIdVenta) == 0
                	&& getDiaVenta(auxVenta, &auxDiaVenta) == 0
					&& getMesVenta(auxVenta, &auxMesVenta) == 0
					&& getAnioVenta(auxVenta, &auxAnioVenta) == 0
                	&& getModeloVenta(auxVenta, auxModelo) == 0
					&& getCantidadVenta(auxVenta, &auxCantidadVenta) == 0
					&& getPrecioVenta(auxVenta, &auxPrecioVenta) == 0
					&& getTarjetaVenta(auxVenta, auxTarjetaVenta) == 0){

                	fprintf(pArchivo, "%d,%d/%d/%d,%s,%d,%f,%s\n",auxIdVenta, auxDiaVenta, auxMesVenta, auxAnioVenta, auxModelo, auxCantidadVenta, auxPrecioVenta, auxTarjetaVenta);
                	controller_guardarUltimoId();
                }
            }
        }
        fclose(pArchivo);
        retorno = 1;
    }
    return retorno;
}

/** \brief Guarda los datos de los jugadores en el archivo binario.
 *
 * \param path char*
 * \param pArrayListVenta LinkedList*
 * \return int
 *
 */
int controller_guardarJugadoresModoBinario(char* path , LinkedList* pArrayListVenta)
{
    int retorno = 0;
    FILE* pArchivo;
    int longitud;
    eVenta* auxJugador = NULL;

    if(path != NULL && pArrayListVenta != NULL)
    {
        pArchivo = fopen(path,"wb");

        if(pArchivo != NULL)
        {
            longitud = ll_len(pArrayListVenta);

            for(int i = 0; i < longitud ; i++){

            	auxJugador = ll_get(pArrayListVenta, i);

                if(auxJugador != NULL){

                    fwrite(auxJugador, sizeof(eVenta), 1, pArchivo);
                }
            }
        }
        fclose(pArchivo);
        retorno = 1;
    }
    return retorno;
}

/** \brief Alta de jugadores
 *
 * \param path char*
 * \param pArrayListVenta LinkedList*
 * \return int
 *
 */
int controller_agregarVenta(LinkedList* pArrayListVenta) {

	    int noError = -1;
		eVenta auxVenta;
		eVenta* pVenta = NULL;

		if(pArrayListVenta != NULL) {
			pVenta = nuevaVenta();
			if (pVenta != NULL && cargarDatosVenta(&auxVenta) == 0){
				auxVenta.idVenta = idIncremental();
				if(auxVenta.idVenta > 0 &&
					(setIdVenta(pVenta, auxVenta.idVenta) == 0) &&
					(setDiaVenta(pVenta, auxVenta.fecha.dia) == 0) &&
					(setMesVenta(pVenta, auxVenta.fecha.mes) == 0) &&
					(setAnioVenta(pVenta, auxVenta.fecha.anio) == 0) &&
					(setModeloVenta(pVenta, auxVenta.modeloDeAuto) == 0)  &&
					(setCantidadVenta(pVenta, auxVenta.cantidad) == 0) &&
					(setPrecioVenta(pVenta, auxVenta.precioUnitario) == 0) &&
					(setTarjetaVenta(pVenta, auxVenta.tarjetaDeCredito) == 0) &&
					(ll_add(pArrayListVenta, pVenta) == 0)){
					printf("Se cargó correctamente al jugador.\n");
					noError = 0;
				}
			} else {
				printf("\nAl menos un dato ingresado es invalido, no se ingreso ningun jugador.\n");
			}
		}
	    return noError;
}

/** \brief Modificar datos del jugador
 *
 * \param path char*
 * \param pArrayListVenta LinkedList*
 * \return int
 *
 */
int controller_editarVenta(LinkedList *pArrayListVenta) {

	int noError = -1;
	int opcion = 0;
	int confirmar, indice;
	eVenta auxVenta;
	eVenta *pVenta;

	if (pArrayListVenta != NULL) {

		if (controller_listarVentas(pArrayListVenta) == 0
				&& (getNumber(&auxVenta.idVenta,
				"\nIngresa el ID de la venta a modificar: ",
				"\nNo existe venta con ese ID\n", 1, ultimoId, RETRIES) == 0)) {

			indice = controller_buscarId(pArrayListVenta, auxVenta.idVenta);

			if (indice != -1) {

				pVenta = (eVenta*) ll_get(pArrayListVenta, indice);

				if (pVenta != NULL
						&& (getIdVenta(pVenta, &auxVenta.idVenta) == 0)
						&& (getDiaVenta(pVenta, &auxVenta.fecha.dia) == 0)
						&& (getMesVenta(pVenta, &auxVenta.fecha.mes) == 0)
						&& (getAnioVenta(pVenta, &auxVenta.fecha.anio) == 0)
						&& (getModeloVenta(pVenta, auxVenta.modeloDeAuto) == 0)
						&& (getCantidadVenta(pVenta, &auxVenta.cantidad) == 0)
						&& (getPrecioVenta(pVenta, &auxVenta.precioUnitario) == 0)
						&& (getTarjetaVenta(pVenta, auxVenta.tarjetaDeCredito) == 0)) {
					do {
						opcion = menuEditarJugador();
						switch (opcion) {
							case 1:
								if (getNumber(&auxVenta.fecha.dia,"\nIngrese el dia de la nueva fecha: ", ERROR_MSG,
										MIN_DIA_O_MES, MAX_DIA, RETRIES) == 0 &&
									getNumber(&auxVenta.fecha.mes,"\nIngrese el mes de la nueva fecha: ", ERROR_MSG,
											MIN_DIA_O_MES, MAX_MES, RETRIES) == 0 &&
									getNumber(&auxVenta.fecha.anio,"\nIngrese el anio de la nueva fecha: ", ERROR_MSG,
											MIN_ANIO, MAX_ANIO, RETRIES) == 0) {
									confirmar = confirmarAccion(CONFIRM_MSG,CONFIRM_MSG_ERROR);
									if (confirmar == 0) {
										if (setDiaVenta(pVenta, auxVenta.fecha.dia) == 0 &&
											setMesVenta(pVenta, auxVenta.fecha.mes) == 0 &&
											setAnioVenta(pVenta, auxVenta.fecha.anio) == 0) {
											printf("Fecha ingresada correctamente.\n");
										}
									}
								} else {
									printf("No se ingresó una fecha válida.\n");
								}
								break;
							case 2:
								if (getText(auxVenta.modeloDeAuto,
										"\nIngrese el nuevo modelo: ", ERROR_MSG, MAX_LEN_MODELO, RETRIES) == 0) {
									confirmar = confirmarAccion(CONFIRM_MSG,CONFIRM_MSG_ERROR);
									if (confirmar == 0) {
										if (!setModeloVenta(pVenta, auxVenta.modeloDeAuto)) {
											printf("Nombre ingresado correctamente.\n");
										}
									}
								} else {
									printf("No se ingresó un modelo válido.\n");
								}
								break;
							case 3:
								if (getNumber(&auxVenta.cantidad,
										"\nIngrese la nueva cantidad: ", ERROR_MSG,
										MIN_CANTIDAD, MAX_CANTIDAD,
										RETRIES) == 0) {
									confirmar = confirmarAccion(CONFIRM_MSG,CONFIRM_MSG_ERROR);
									if (confirmar == 0) {
										if (!setCantidadVenta(pVenta,auxVenta.cantidad)) {
											printf("Cantidad ingresada correctamente.\n");
										}
									}
								} else {
									printf("No se ingresó una cantidad válida.\n");
								}
								break;
							case 4:
								if (getFloatNumber(&auxVenta.precioUnitario,
										"\nIngrese el nuevo precio: ", ERROR_MSG,
										MIN_PRECIO, MAX_PRECIO, RETRIES) == 0) {
									confirmar = confirmarAccion(CONFIRM_MSG,CONFIRM_MSG_ERROR);
									if (confirmar == 0) {
										if (setPrecioVenta(pVenta, auxVenta.precioUnitario) == 0) {
											printf("Precio ingresado correctamente.\n");
										}
									}
								} else {
									printf("No se ingresó un precio válido.\n");
								}
								break;
						case 5:
							if (getTarjeta(auxVenta.tarjetaDeCredito,
									"\nIngrese la nueva tarjeta: ", ERROR_MSG,
									MAX_LEN_TARJETA, RETRIES) == 0) {
								confirmar = confirmarAccion(CONFIRM_MSG,
										CONFIRM_MSG_ERROR);
								if (confirmar == 0) {
									if (!setTarjetaVenta(pVenta,
											auxVenta.tarjetaDeCredito)) {
										printf("Tarjeta ingresada correctamente.\n");
									}
								}
							} else {
								printf("No se ingresó una tarjeta válida.\n");
							}
							break;
							case 6:
								printf("Saliste exitosamente del menu de modificacion.\n");
							}
					} while (opcion != 6);
				}

			}
		}
	}
	return noError;
}

/** \brief Baja del jugador
 *
 * \param path char*
 * \param pArrayListVenta LinkedList*
 * \return int
 *
 */
int controller_borrarVenta(LinkedList* pArrayListVenta)
{
	int retorno = -1;
	    eVenta* pVenta = NULL;
		int indice;
		int auxId;
		int confirmar;

		if(pArrayListVenta != NULL){

			if(!controller_listarVentas(pArrayListVenta)){

				if(getNumber(&auxId, "\nIngrese el ID del jugador que desea eliminar: ", ERROR_MSG, 1, ultimoId, RETRIES) == 0) {

					indice = controller_buscarId(pArrayListVenta, auxId);

		    		if(indice != -1) {

		    			pVenta = (eVenta*)ll_get(pArrayListVenta, indice);
						if(pVenta != NULL) {
								printf("Está seguro que quiere eliminar al jugador de ID %d?\n", auxId);
								confirmar = confirmarAccion(CONFIRM_MSG,CONFIRM_MSG_ERROR);
								if (confirmar == 0) {
									free(pVenta);
									printf("El jugador fue eliminado exitosamente.\n");
									ll_remove(pArrayListVenta, indice);
									retorno = 0;
								} else {
									printf("No se eliminó a ningún pasajero.\n");
								}
						}
		    		}
				}
			}
		}
		return retorno;
}

int controller_listarVentas(LinkedList* pArrayListVenta)
{
	int noError = -1;
	int longitud = ll_len(pArrayListVenta);
	eVenta *auxVenta = NULL;

	if (pArrayListVenta != NULL && longitud > 0)
	{
		printf(" ___________________________________________________________________________________________________\n");
		printf("|        |            |                      |            |                   |                     |\n");
		printf("|   ID   |   Fecha    |        Modelo        |  Cantidad  |  Precio Unitario  | Tarjeta de Credito  |\n");
		printf("|________|____________|______________________|____________|___________________|_____________________|\n");
		printf("|        |            |                      |            |                   |                     |\n");
		noError = 0;
		for (int i = 0; i < longitud; i++)
		{
			auxVenta = (eVenta*) ll_get(pArrayListVenta, i);
			mostrarVenta(auxVenta);
		}
		printf("|________|____________|______________________|____________|___________________|_____________________|\n");
	}
	else {
		printf("\nNo hay ventas para listar.\n");
		free(auxVenta);
	}
    return noError;
}

/** \brief Guarda los datos de los jugadores en el archivo binario.
 *
 * \param path char*
 * \param pArrayListVenta LinkedList*
 * \return int
 *
 */
int controller_guardarVentasModoBinario(char* path , LinkedList* pArrayListVenta)
{
    int retorno = 0;
    FILE* pArchivo;
    int longitud;
    eVenta* auxVenta = NULL;

    if(path != NULL && pArrayListVenta != NULL)
    {
        pArchivo = fopen(path,"wb");

        if(pArchivo != NULL)
        {
            longitud = ll_len(pArrayListVenta);

            for(int i = 0; i < longitud ; i++){

            	auxVenta = ll_get(pArrayListVenta, i);

                if(auxVenta != NULL){

                    fwrite(auxVenta, sizeof(eVenta), 1, pArchivo);
                }
            }
        }
        fclose(pArchivo);
        retorno = 1;
    }
    return retorno;
}

int controller_generarInforme(char* path, LinkedList* pArrayListVenta) {

    int retorno = 0;
    FILE* pArchivo;

    int cantUnidadesTotales = ll_count(pArrayListVenta, cantidadUnidadesTotales);
    int cantVentasSobre10000 = ll_count(pArrayListVenta, preciosSobreDiezMil);
    int cantVentasSobre20000 = ll_count(pArrayListVenta, preciosSobreVeinteMil);
    int cantModelosEclipse = ll_count(pArrayListVenta, cantidadModelosEclipseTotales);

    if(path != NULL && pArrayListVenta != NULL)
    {
        pArchivo = fopen(path,"w");

        if(pArchivo != NULL) {
                fprintf(pArchivo, "Listado de informes.\n-> Cantidad de unidades vendidas totales: %d\n-> Cantidad de ventas por un monto mayor a $10.000: %d\n-> Cantidad de ventas por un monto mayor a $20.000: %d\n-> Cantidad de Eclipses vendidos: %d",cantUnidadesTotales, cantVentasSobre10000, cantVentasSobre20000, cantModelosEclipse);
            }
        fclose(pArchivo);
        retorno = 1;
    }
    return retorno;
}
