//============================================================================
// ----------- PRACTICAS DE FUNDAMENTOS DE REDES DE COMUNICACIONES -----------
// ---------------------------- CURSO 2021/22 --------------------------------
// ----------------------------- SESION1.CPP ---------------------------------
//============================================================================


#include <stdio.h>
#include <iostream>
#include "linkLayer.h"




using namespace std;


int main()
{
 interface_t iface;
 pcap_if_t *avail_ifaces=NULL;
 
 
 printf("\n holaaajochemiiiii");
 printf("\n----------------------------\n");
 printf("------ SESION 1 - FRC ------\n");
 printf("----------------------------\n");
    
 avail_ifaces=GetAvailAdapters(); 
 printf("----------------\n");
 setDeviceName(&iface, "lo");
 printf("----------------\n");
 GetMACAdapter(&iface);
 printf("----------------\n");

 return 0;
}
