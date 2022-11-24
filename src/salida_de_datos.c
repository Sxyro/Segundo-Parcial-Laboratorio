#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "salida_de_datos.h"
#include "entrada_de_datos.h"

int menuPrincipal() {

	int option = -1;
	int auxOption;

	printf("  _________________________________\n");
	printf(" |                                 |\n");
	printf(" |          Menu Principal         |\n");
	printf(" |_________________________________|\n");
	printf(" |                                 |\n");
	printf(" | 1- Dar de alta una venta.       |\n");
	printf(" |_________________________________|\n");
	printf(" |                                 |\n");
	printf(" | 2- Modificar a una venta.       |\n");
	printf(" |_________________________________|\n");
	printf(" |                                 |\n");
	printf(" | 3- Dar de baja a una venta.     |\n");
	printf(" |_________________________________|\n");
	printf(" |                                 |\n");
	printf(" | 4- Listar ventas.               |\n");
	printf(" |_________________________________|\n");
	printf(" |                                 |\n");
	printf(" | 5- Guardar archivo texto.       |\n");
	printf(" |_________________________________|\n");
	printf(" |                                 |\n");
	printf(" | 6- Guardar archivo binario.     |\n");
	printf(" |_________________________________|\n");
	printf(" |                                 |\n");
	printf(" | 7- Guardar informe de ventas.   |\n");
	printf(" |_________________________________|\n");
	printf(" |                                 |\n");
	printf(" | 8- Salir.                       |\n");
	printf(" |_________________________________|\n");

	if (!(getNumber(&auxOption, MSG_INGRESO_MENU, MSG_ERROR_MENU, 1, 8, RETRIES))) {
		option = auxOption;
	}
	return option;
}

int menuEditarJugador() {

	int option = -1;
	int auxOption;

	printf("  ____________________________\n");
	printf(" |                            |\n");
	printf(" |        Menu Edición        |\n");
	printf(" |____________________________|\n");
	printf(" |                            |\n");
	printf(" | 1- Modificar fecha.        |\n");
	printf(" |----------------------------|\n");
	printf(" | 2- Modificar modelo.       |\n");
	printf(" |----------------------------|\n");
	printf(" | 3- Modificar cantidad.     |\n");
	printf(" |----------------------------|\n");
	printf(" | 4- Modificar precio.       |\n");
	printf(" |----------------------------|\n");
	printf(" | 5- Modificar tarjeta.      |\n");
	printf(" |----------------------------|\n");
	printf(" | 6- Salir.                  |\n");
	printf(" |____________________________|\n");

	if (getNumber(&auxOption, MSG_INGRESO_MENU, MSG_ERROR_MENU, 1,6,RETRIES) == 0)
	{
		option = auxOption;
	}
	return option;
}

int systemPause(char* message)
{
    int retorno = -1;
    if(message!=NULL)
    {
        fflush(stdin);
        printf("\n%s",message);
        getchar();
        retorno = 0;
    }
    return retorno;
}

