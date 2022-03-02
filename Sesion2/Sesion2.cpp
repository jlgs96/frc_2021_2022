//============================================================================
// ----------- PRACTICAS DE FUNDAMENTOS DE REDES DE COMUNICACIONES -----------
// ---------------------------- CURSO 2021/22 --------------------------------
// ----------------------------- SESION2.CPP ---------------------------------
//============================================================================
//AUTORES: Jose Miguel Bermejo Gonzalez y Jose Luis Garcia Salas
//GRUPO 10: Viernes 12:00 - 13:30

#include <stdio.h>
#include <iostream>
#include "linkLayer.h"
/*
###### BUCLE PRINCIPAL ######

Hacemos comprobación kbhit y hacemos getch y si es !esc no entramos.
Mientras no sea !esc
  si kbhit == 0: recibo
  sino: envío con getch() y envias.
*/

using namespace std;

int main()
{
  char car = 'A';
  unsigned char mac_src[6]={0x00, 0x00, 0x00, 0x00,0x00, 0x00};
  unsigned char mac_dst[6]={0x00, 0x01, 0x02, 0x03,0x04, 0x05};
  unsigned char type[2]={0x30,0x00};
 
  interface_t iface;

  //Elegimos el puerto
  setDeviceName(&iface, "lo");

  //Abrimos el puerto
  int Puerto=OpenAdapter(&iface);

  //Enviamos un carácter
  EnviarCaracter(iface,car,mac_src,mac_dst,type);
  //Cerramos el puerto:
  CloseAdapter(&iface);

  return 0;
}
