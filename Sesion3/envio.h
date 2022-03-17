#include <stdio.h>
#include <iostream>
#include "linkLayer.h"
using namespace std;

/**
 * @brief Envía carácteres individuales al receptor 
 * 
 * @param interfaz 
 * @param datos 
 * @param mac_destino 
 * @param tipo 
 */
void EnviarCaracter (interface_t *interfaz, unsigned char datos, unsigned char *mac_destino,char tipo[]);

/**
 * @brief Envía un mensaje en broadcast
 * 
 */
void EnviarBroadCast(interface_t *interfaz,char tipo[]);