#include <stdio.h>
#include <iostream>
#include "linkLayer.h"
using namespace std;

/**
 * @brief Recibe carácteres individuales del emisor
 * 
 * @param interfaz 
 * @return char 
 */
char RecibirCaracter (interface_t *interfaz);

char *RecibirCadena (interface_t *interfaz);