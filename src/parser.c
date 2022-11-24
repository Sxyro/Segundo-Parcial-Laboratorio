#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "ventas.h"

/** \brief Parsea los datos de los jugadores desde el archivo jugadores.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListVenta LinkedList*
 * \return int
 */

int parser_VentaFromText(FILE* pFile , LinkedList* pArrayListVenta)
{
    int noError = -1;
    char auxLecturaFantasma[2000];
    char auxIdVenta[100];
    char auxDiaVenta[100];
    char auxMesVenta[100];
    char auxAnioVenta[100];
    char auxModeloVenta[100];
    char auxCantidadVenta[100];
    char auxPrecioVenta[100];
    char auxTarjetaVenta[100];

    eVenta* pVenta = NULL;
    int retornoVariable;

    if(pFile != NULL && pArrayListVenta != NULL)
    {
        fscanf(pFile,"%[^\n]\n", auxLecturaFantasma);
        do{
            retornoVariable = fscanf(pFile,"%[^,],%[^/]/%[^/]/%[^,],%[^,],%[^,],%[^,],%[^\n]\n",auxIdVenta, auxDiaVenta, auxMesVenta, auxAnioVenta, auxModeloVenta,auxCantidadVenta, auxPrecioVenta, auxTarjetaVenta);
            if(retornoVariable == 8)
            {
                pVenta = nuevaVentaParam(auxIdVenta, auxDiaVenta, auxMesVenta, auxAnioVenta, auxModeloVenta, auxCantidadVenta, auxPrecioVenta, auxTarjetaVenta);
               if(pVenta != NULL){

                   ll_add(pArrayListVenta, pVenta);
                   noError = 0;
               } else {
               	printf("entro aca otra vez\n");
               }
            }else{
            	noError = -1;
                break;
            }

        }while(!feof(pFile));
    }

    return noError;
}

/** \brief Parsea los datos de los jugadores desde el archivo binario.
 *
 * \param path char*
 * \param pArrayListVenta LinkedList*
 * \return int
 *
 */
int parser_VentaFromBinary(FILE* pFile , LinkedList* pArrayListVenta)
{

    int noError = -1;
    int auxIdVenta;
    int auxDiaVenta;
    int auxMesVenta;
    int auxAnioVenta;
    char auxModeloVenta[100];
    int auxCantidadVenta;
    float auxPrecioVenta;
    char auxTarjetaVenta[100];
    eVenta* pVenta = NULL;
    int retornoVariable;

    if(pFile != NULL && pArrayListVenta != NULL)
    {
        do{
            retornoVariable = fread(pVenta, sizeof(eVenta), 1, pFile);

            if(retornoVariable == 1)
            {
                if(getIdVenta(pVenta, &auxIdVenta) == 0
                		&& getDiaVenta(pVenta, &auxDiaVenta) == 0
						&& getIdVenta(pVenta, &auxMesVenta) == 0
						&& getIdVenta(pVenta, &auxAnioVenta) == 0
						&& getModeloVenta(pVenta, auxModeloVenta) == 0
						&& getCantidadVenta(pVenta, &auxCantidadVenta) == 0
						&& getPrecioVenta(pVenta, &auxPrecioVenta) == 0
						&& getTarjetaVenta(pVenta, auxTarjetaVenta) == 0) {

                    ll_add(pArrayListVenta, pVenta);
                    noError = 0;
                }

                noError = 0;
            }else{

            	noError = -1;
                break;
            }

        }while(!feof(pFile));
    }

    return noError;
}

