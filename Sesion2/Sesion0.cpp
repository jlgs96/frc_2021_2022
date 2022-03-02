//============================================================================
// ----------- PRACTICAS DE FUNDAMENTOS DE REDES DE COMUNICACIONES -----------
// ---------------------------- CURSO 2021/22 --------------------------------
// ----------------------------- SESION1.CPP ---------------------------------
//============================================================================

//AUTORES: Jose Miguel Bermejo Gonzalez y Jose Luis Garcia Salas
//GRUPO: Viernes 12:00 - 13:30


#include <stdio.h>
#include <iostream>
#include "linkLayer.h"
#include "interfaz.h"



using namespace std; 


int main(){
    interface_t iface;
    pcap_if_t *avail_ifaces=NULL;
    int iseleccionada;
    avail_ifaces=GetAvailAdapters(); 

    char car = 'A';
    unsigned char mac_src[6]={0x00, 0x00, 0x00, 0x00,0x00, 0x00};
    unsigned char mac_dst[6]={0x00, 0x01, 0x02, 0x03,0x04, 0x05};
    char type[2]={0x30,0x00};
    

    //BUCLE PARA MOSTRAR LAS INTERFACES
    printf("Interfaces disponibles: \n");
    mostrarInterfacesDisponibles(avail_ifaces);

    //PEDIMOS INTERFAZ (MODULARIZAR)
    iseleccionada = pedirInterfaz();


    //BUCLE RECORRE Y ELIGE LA INTERFAZ DESEADA
    seleccionInterfaz(avail_ifaces, iface);

    //ENVIAR CARACTER
    EnviarCaracter(iface,car,mac_src,mac_dst,type);

    //CERRAR PUERTO
    CloseAdapter(&iface);

    return 0;
}
