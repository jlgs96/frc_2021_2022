#include <stdio.h>
#include <iostream>
#include "envio.h"
#include "recepcion.h"
#include "linkLayer.h"
using namespace std;


bool f1EnvioCaracteres(char character, interface_t *iface, unsigned char *mac_dst,char type[]);

/**
 * @brief Obtenemos la dirección de Origen de la trama recibida
 * 
 * @param trama 
 * @return unsigned char* 
 */
unsigned char *ObtenerDirOrigen(const unsigned char *trama);

/**
 * @brief Establecemos la conexión entre el Maestro y el Esclavo
 * 
 * @param interfaz 
 * @param tipo 
 * @param rol 
 * @return unsigned char* 
 */
unsigned char *establecerConexionME(interface_t *interfaz, char tipo[], int rol);