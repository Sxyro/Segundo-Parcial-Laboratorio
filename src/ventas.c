#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ventas.h"
#include "entrada_de_datos.h"

eVenta* nuevaVenta() {

	eVenta *auxVenta = NULL;
	auxVenta = (eVenta*) malloc(sizeof(eVenta));

	if (auxVenta != NULL) {
		auxVenta->idVenta = 0;
		auxVenta->fecha.dia = 0;
		auxVenta->fecha.mes = 0;
		auxVenta->fecha.anio = 0;
		strcpy(auxVenta->modeloDeAuto, " ");
		auxVenta->cantidad = 0;
		auxVenta->precioUnitario = 0;
		strcpy(auxVenta->tarjetaDeCredito, " ");
	}
	return auxVenta;
}

eVenta* nuevaVentaParam(char *idStr, char *diaStr, char *mesStr, char *anioStr, char *modeloStr, char *cantidadStr, char *precioStr, char *tarjetaStr) {

	eVenta *auxVenta = NULL;
	auxVenta = nuevaVenta();

	if (auxVenta != NULL) {
		if ((setIdVenta(auxVenta, atoi(idStr))) != 0
				|| (setDiaVenta(auxVenta, atoi(diaStr))) != 0
				|| (setMesVenta(auxVenta, atoi(mesStr))) != 0
				|| (setAnioVenta(auxVenta, atoi(anioStr))) != 0
				|| (setModeloVenta(auxVenta, modeloStr)) != 0
				|| (setCantidadVenta(auxVenta, atoi(cantidadStr))) != 0
				|| (setPrecioVenta(auxVenta, atof(precioStr))) != 0
				|| (setTarjetaVenta(auxVenta, tarjetaStr)) != 0) {
			free(auxVenta);
			auxVenta = NULL;
			printf("%s,%s/%s/%s,%s,%s,%s,%s", idStr, diaStr, mesStr, anioStr, modeloStr, cantidadStr,precioStr, tarjetaStr);
		}
	}

	return auxVenta;
}

// ID --------------------------------------
int setIdVenta(eVenta *this, int id) {

	int noError = -1;

	if (this != NULL && id >= 0) {
		this->idVenta = id;
		noError = 0;
	}
	return noError;
}
int getIdVenta(eVenta *this, int *id) {

	int noError = -1;

	if (this != NULL && id != NULL) {
		*id = this->idVenta;
		noError = 0;
	}
	return noError;
}
// Dia -------------------------------------
int setDiaVenta(eVenta *this, int dia) {

	int noError = -1;

	if (this != NULL && dia >= 0) {
		this->fecha.dia = dia;
		noError = 0;
	}
	return noError;
}
int getDiaVenta(eVenta *this, int *dia) {

	int noError = -1;

	if (this != NULL && dia != NULL) {
		*dia = this->fecha.dia;
		noError = 0;
	}
	return noError;
}
// Mes -------------------------------------
int setMesVenta(eVenta *this, int mes) {

	int noError = -1;

	if (this != NULL && mes >= 0) {
		this->fecha.mes = mes;
		noError = 0;
	}
	return noError;
}
int getMesVenta(eVenta *this, int *mes) {

	int noError = -1;

	if (this != NULL && mes != NULL) {
		*mes = this->fecha.mes;
		noError = 0;
	}
	return noError;
}
// Año -------------------------------------
int setAnioVenta(eVenta *this, int anio) {

	int noError = -1;

	if (this != NULL && anio >= 0) {
		this->fecha.anio = anio;
		noError = 0;
	}
	return noError;
}
int getAnioVenta(eVenta *this, int *anio) {

	int noError = -1;

	if (this != NULL && anio != NULL) {
		*anio = this->fecha.anio;
		noError = 0;
	}
	return noError;
}
// Modelo Auto -----------------------------
int setModeloVenta(eVenta *this, char *modelo) {

	int noError = -1;

	if (this != NULL && modelo != NULL) {
		strcpy(this->modeloDeAuto, modelo);
		noError = 0;
	}
	return noError;
}
int getModeloVenta(eVenta *this, char *modelo) {

	int noError = -1;

	if (this != NULL && modelo != NULL) {
		strcpy(modelo, this->modeloDeAuto);
		noError = 0;
	}
	return noError;
}
// Cantidad --------------------------------
int setCantidadVenta(eVenta *this, int cantidadVenta) {

	int noError = -1;

	if (this != NULL && cantidadVenta >= 0) {
		this->cantidad = cantidadVenta;
		noError = 0;
	}
	return noError;
}
int getCantidadVenta(eVenta *this, int *cantidadVenta) {

	int noError = -1;

	if (this != NULL && cantidadVenta != NULL) {
		*cantidadVenta = this->cantidad;
		noError = 0;
	}
	return noError;
}
// Precio Unitario --------------------------
int setPrecioVenta(eVenta *this, float precio) {

	int noError = -1;

	if (this != NULL && precio >= 0) {
		this->precioUnitario = precio;
		noError = 0;
	}
	return noError;
}
int getPrecioVenta(eVenta *this, float *precio) {

	int noError = -1;

	if (this != NULL && precio != NULL) {
		*precio = this->precioUnitario;
		noError = 0;
	}
	return noError;
}
// Tarjeta  ----------------------------------
int setTarjetaVenta(eVenta *this, char *tarjeta) {

	int noError = -1;

	if (this != NULL && tarjeta != NULL) {
		strcpy(this->tarjetaDeCredito, tarjeta);
		noError = 0;
	}
	return noError;
}
int getTarjetaVenta(eVenta *this, char *tarjeta) {

	int noError = -1;

	if (this != NULL && tarjeta != NULL) {
		strcpy(tarjeta, this->tarjetaDeCredito);
		noError = 0;
	}
	return noError;
}

int cargarDatosVenta(eVenta* this){
	int retorno = -1;
	eVenta auxVenta;

	if(this != NULL){
		if(getNumber(&auxVenta.fecha.dia, "Estas por ingresar la fecha de la venta...\n\nIngrese el dia: ", ERROR_MSG, MIN_DIA_O_MES, MAX_DIA, RETRIES) == 0 &&
			getNumber(&auxVenta.fecha.mes, "Ingrese el mes: ", ERROR_MSG, MIN_DIA_O_MES, MAX_MES, RETRIES) == 0 &&
			getNumber(&auxVenta.fecha.anio, "Ingrese el año: ", ERROR_MSG, MIN_ANIO, MAX_ANIO, RETRIES) == 0 &&
			getText(auxVenta.modeloDeAuto, "Ingrese el modelo del auto: ", ERROR_MSG, 25, RETRIES) == 0 &&
			getNumber(&auxVenta.cantidad, "Ingrese la cantidad de autos comprados: ", ERROR_MSG, 1, 100, RETRIES) == 0 &&
			getFloatNumber(&auxVenta.precioUnitario, "Ingrese el precio por unidad: ", ERROR_MSG, 100000, 10000000, RETRIES) == 0 &&
			getTarjeta(auxVenta.tarjetaDeCredito, "Ingrese la tarjeta de credito utilizada para la compra: ", ERROR_MSG, 15, RETRIES) == 0) {
			retorno = 0;
			*this = auxVenta;
		}
	}
	return retorno;
}

int mostrarVenta(eVenta *this)
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

	if (this != NULL)
	{
		if (getIdVenta(this, &auxIdVenta) == 0
		&& getDiaVenta(this, &auxDiaVenta) == 0
		&& getMesVenta(this, &auxMesVenta) == 0
		&& getAnioVenta(this, &auxAnioVenta) == 0
		&& getModeloVenta(this, auxModeloVenta) == 0
		&& getCantidadVenta(this, &auxCantidadVenta) == 0
		&& getPrecioVenta(this, &auxPrecioVenta) == 0
		&& getTarjetaVenta(this, auxTarjetaVenta) == 0) {

		printf("|   %-5d| %2d/%2d/%4d | %-20s |     %-3d    |    %-11.2f    |   %-15s   |\n", auxIdVenta, auxDiaVenta, auxMesVenta, auxAnioVenta, auxModeloVenta, auxCantidadVenta, auxPrecioVenta, auxTarjetaVenta);
		noError = 0;
		}
	}
	return noError;

}

int cantidadUnidadesTotales(void *this)
{
    eVenta* auxVenta;
    int acumulador = 0;
    int auxCantidad;

    if(this != NULL)
    {
    	auxVenta = (eVenta*) this;
    	getCantidadVenta(auxVenta, &auxCantidad);
    	acumulador = auxCantidad;
    }
    return acumulador;
}

int preciosSobreDiezMil(void *this)
{
    eVenta* auxVenta;
    int retorno = 0;
    float auxPrecio;
    int auxCantidad;
    float total;

    if(this != NULL)
    {

    	auxVenta = (eVenta*) this;
    	getPrecioVenta(auxVenta, &auxPrecio);
    	getCantidadVenta(auxVenta, &auxCantidad);
    	total = (float) auxCantidad * auxPrecio;
        if(total > 10000) {
            retorno = 1;
        }
    }
    return retorno;
}

int preciosSobreVeinteMil(void *this)
{
    eVenta* auxVenta;
    int retorno = 0;
    float auxPrecio;
    int auxCantidad;
    float total;

    if(this != NULL)
    {

    	auxVenta = (eVenta*) this;
    	getPrecioVenta(auxVenta, &auxPrecio);
    	getCantidadVenta(auxVenta, &auxCantidad);
    	total = (float) auxCantidad * auxPrecio;
        if(total > 20000) {
            retorno = 1;
        }
    }
    return retorno;
}

int cantidadModelosEclipseTotales(void *this) {
	eVenta *auxVenta;
	int acumulador = 0;
	char *modeloEclipse = "Eclipse";
	char auxModelo[20];
	int auxCantidad;

	if (this != NULL) {

		auxVenta = (eVenta*) this;
		getModeloVenta(auxVenta, auxModelo);

		if (strcmp(auxModelo, modeloEclipse) == 0) {

			getCantidadVenta(auxVenta, &auxCantidad);
			acumulador = auxCantidad;
		}
	}
	return acumulador;
}
