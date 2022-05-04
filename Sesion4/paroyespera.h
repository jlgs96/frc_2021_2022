#include <stdio.h>
#include <iostream>
#include <fstream>
#include "envio.h"
#include "recepcion.h"
#include "interfaz.h"
#include "linkLayer.h"
using namespace std;

void enviarTramaControl(interface_t *interfaz, unsigned char *mac_destino, char tipo[]);

bool recibirTramaControl(interface_t *interfaz, char direccion, char control, char ntrama);