#include <stdio.h>
#include <iostream>
#include <fstream>
#include "envio.h"
#include "recepcion.h"
#include "interfaz.h"
#include "linkLayer.h"
using namespace std;

bool enviarTramaControl(interface_t *interfaz, unsigned char *mac_destino, char tipo[],char direccion, char control,char ntrama);

bool recibirTramaControl(interface_t *interfaz,char direccion, char control, char ntrama);

int calcularBCE(char datos[],int longitud);

bool enviarTramaDatos(interface_t *interfaz, unsigned char *mac_destino, char tipo[], unsigned char *datos,int longitud, char direccion, char control, char ntrama,int bce);