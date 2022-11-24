#ifndef VENTAS_H_
#define VENTAS_H_

#define ERROR_MSG "Error. reingrese.\n"
#define RETRIES 2
#define CONFIRM_MSG "¿Esta seguro que desea realizar el cambio?\n0: Si.\n1: No.\n-> Ingrese: "
#define CONFIRM_MSG_ERROR "Por favor seleccione una opcion valida.\n0: Si.\n1: No.\n-> Ingrese: "
#define MAX_LEN_MODELO 16
#define MIN_CANTIDAD 1
#define MAX_CANTIDAD 100
#define MIN_DIA_O_MES 1
#define MAX_DIA 31
#define MAX_MES 12
#define MIN_ANIO 2021
#define MAX_ANIO 2022
#define MAX_LEN_TARJETA 15
#define MIN_PRECIO 100000
#define MAX_PRECIO 10000000

typedef struct {
	int dia;
	int mes;
	int anio;
}eFecha;

typedef struct
{
	int idVenta;
	eFecha fecha;
	char modeloDeAuto[30];
	int cantidad;
	float precioUnitario;
	char tarjetaDeCredito[30];
}eVenta;

eVenta* nuevaVenta();

eVenta* nuevaVentaParam(char *idStr, char *diaStr, char *mesStr, char *anioStr, char *modeloStr, char *cantidadStr, char *precioStr, char *tarjetaStr);

// ID --------------------------------------

int setIdVenta(eVenta *this, int id);

int getIdVenta(eVenta *this, int *id);

// Dia -------------------------------------

int setDiaVenta(eVenta *this, int dia);

int getDiaVenta(eVenta *this, int *dia);

// Mes -------------------------------------

int setMesVenta(eVenta *this, int mes);

int getMesVenta(eVenta *this, int *mes);

// Año -------------------------------------

int setAnioVenta(eVenta *this, int anio);

int getAnioVenta(eVenta *this, int *anio);

// Modelo Auto -----------------------------

int setModeloVenta(eVenta *this, char *modelo);

int getModeloVenta(eVenta *this, char *modelo);

// Cantidad --------------------------------

int setCantidadVenta(eVenta *this, int cantidadVenta);

int getCantidadVenta(eVenta *this, int *cantidadVenta);

// Precio Unitario --------------------------

int setPrecioVenta(eVenta *this, float precio);

int getPrecioVenta(eVenta *this, float *precio);

// Tarjeta  ----------------------------------

int setTarjetaVenta(eVenta *this, char *tarjeta);

int getTarjetaVenta(eVenta *this, char *tarjeta);

int mostrarVenta(eVenta *this);

int cargarDatosVenta(eVenta* this);

int cantidadUnidadesTotales(void *this);

int preciosSobreDiezMil(void *this);

int preciosSobreVeinteMil(void *this);

int cantidadModelosEclipseTotales(void *this);

#endif /* VENTAS_H_ */
