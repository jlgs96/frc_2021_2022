#include <stdio.h>
#include <iostream>
#include "linkLayer.h"


using namespace std; 

/**
 * @brief Muestra las interfaces de la lista que hay disponibles para conectarnos
 * 
 * @param interfaces_disponibles 
 */
void mostrarInterfacesDisponibles(pcap_if_t *interfaces_disponibles);

/**
 * @brief Seleccionamos la interfaz a utilizar
 * 
 * @return int 
 */
int pedirInterfaz();

/**
 * @brief Recorre las interfaces disponibles y selecciona una en concreto
 * 
 * @param interfaces_disponibles 
 * @param interfaz 
 */
void seleccionInterfaz(pcap_if_t *interfaces_disponibles, interface_t *interfaz);

/**
 * @brief Muestra por pantalla la dirección de la MAC de la interfaz elegida
 * 
 * @param interfaz 
 */
void mostrarInterfaz(interface_t *interfaz);


/**
 * @brief Devuelve el grupo al que vamos a conectarnos, en char type[0]
 * 
 * @return char 
 */
char elegirGrupo();


/**
 * @brief Selecionamos le rol que tomara nuestra estación
 * 
 * @return int 
 */
int seleccionarRol();


//METODO PARA MOSTRAR POR PANTALLA LOS MODOS DE EJECUCIÓN SEGÚN SEA MAESTRO O ESCLAVO
void seleccionModo(int rol);