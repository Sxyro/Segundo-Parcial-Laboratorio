#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "controller.h"
#include "entrada_de_datos.h"
#include "salida_de_datos.h"
#include "ventas.h"
#define VENTAS_CSV "ventas.csv"
#define VENTAS_BIN "ventas.bin"
#define INFORMES_CSV "informes.txt"
#define PAUSE_MESSAGE "Presione ENTER para continuar."

int main()
{
	setbuf(stdout,NULL);
    int option = 0;
    LinkedList* listaVentas = ll_newLinkedList();

    controller_cargarVentasDesdeTexto(VENTAS_CSV, listaVentas);

    do{
    		option = menuPrincipal();
			switch(option)
			{
				case 1:
					controller_agregarVenta(listaVentas);
					systemPause(PAUSE_MESSAGE);
					break;
				case 2:
					if (ll_len(listaVentas) > 0) {
					controller_editarVenta(listaVentas);
					} else {
						printf("No existen ventas para modificar.");
					}
					systemPause(PAUSE_MESSAGE);
					break;
				case 3:
					if (ll_len(listaVentas) > 0) {
					controller_borrarVenta(listaVentas);
					} else {
						printf("No existen ventas para borrar.");
					}
					systemPause(PAUSE_MESSAGE);
					break;
				case 4:
					if (ll_len(listaVentas) > 0) {
					controller_listarVentas(listaVentas);
					} else {
						printf("Para listar las ventas debe haberse ingresado al menos una.");
					}
					systemPause(PAUSE_MESSAGE);
					break;
				case 5:
					controller_guardarVentasModoTexto(VENTAS_CSV, listaVentas);
					systemPause(PAUSE_MESSAGE);
					break;
				case 6:
					controller_guardarVentasModoBinario(VENTAS_BIN, listaVentas);
					systemPause(PAUSE_MESSAGE);
					break;
				case 7:
					controller_generarInforme(INFORMES_CSV, listaVentas);
					systemPause(PAUSE_MESSAGE);
					break;
				case 8:
					printf("Saliste exitosamente del programa.");
					break;
			}
    }while(option != 8);

    ll_deleteLinkedList(listaVentas);

    return 0;
}
