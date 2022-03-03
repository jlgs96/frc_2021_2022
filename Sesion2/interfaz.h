#include <stdio.h>
#include <iostream>
#include "linkLayer.h"


using namespace std; 

/*
    METODO QUE RECORRE LA LISTA Y MUESTRA LAS INTERFACES DE RED DISPONIBLES
*/
void mostrarInterfacesDisponibles(pcap_if_t *interfaces_disponibles);

/*
    METODO QUE NOS PIDE SELCCIONAR INTERFAZ
*/
int pedirInterfaz();

 
/*
    METODO QUE RECORRE LAS INTERFACES DISPONIBLES Y SELECCIONA UNA EN CONCRETO
*/
void seleccionInterfaz(pcap_if_t *interfaces_disponibles, interface_t &interfaz);

/*
    METODO QUE MUESTRA POR PANTALLA LA DIRECCION MAC DE LA INTERFAZ ELEGIDA
*/

void mostrarInterfaz(interface_t interfaz);

/*
    MÉTODO QUE ENVÍA CARACTERES
*/

void EnviarCaracter (interface_t &interfaz, unsigned char datos, unsigned char *mac_destino,char *tipo);
/*
    MÉTODO QUE RECIBE CARACTERES
*/


//char RecibirCaracter (interface_t interfaz);
