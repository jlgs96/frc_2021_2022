#include <stdio.h>
#include <iostream>
#include <fstream>
#include "envio.h"
#include "recepcion.h"
#include "interfaz.h"
#include "linkLayer.h"
using namespace std;


void f1EnvioCaracteres(interface_t *iface, unsigned char *mac_dst,char type[], char modo);

void f2EnvioFichero();

/**
 * @brief Establecemos la conexión entre el Maestro y el Esclavo
 * 
 * @param interfaz 
 * @param tipo 
 * @param rol 
 * @return unsigned char* 
 */
unsigned char *establecerConexionME(interface_t *interfaz, char tipo[], int rol);


void ejecutarFunciones(int rol, interface_t *iface, unsigned char *mac_dst,char type[], char modo);