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
//CAMBIAR ESTOS POR INCLUDE "FUNCIONESESPECIALES.H"
#include "funcionesesp.h"

using namespace std;


int main(){
    interface_t iface;
    pcap_if_t *avail_ifaces=NULL;
    avail_ifaces=GetAvailAdapters(); 

   
    unsigned char mac_dst[6]={0x00, 0x01, 0x02, 0x03,0x04, 0x05};
    char type[2]={0x30,0x00};
    
    char character = 'ª';
    char datos[255];

    //BUCLE PARA MOSTRAR LAS INTERFACES
    printf("Interfaces disponibles: \n");
    mostrarInterfacesDisponibles(avail_ifaces);

    //BUCLE RECORRE Y ELIGE LA INTERFAZ DESEADA
    seleccionInterfaz(avail_ifaces, &iface);




    type[0] = elegirGrupo();

    //ABRIR PUERTO
    int Puerto = OpenAdapter(&iface);
    if(Puerto==1)
    {
        printf("Error en el puerto, se debe ejecutar como superusuario\n");
        return 0;
    } else {
        printf("Puerto   abierto correctamente\n");
    }

    //SELECCION DE PUERTO.
    int rol = seleccionarRol();
    

    //ESTABLECIMIENTO DE LA CONEXIÓN ENTRE EL MAESTRO Y EL ESCLAVO
    unsigned char *destino = establecerConexionME(&iface,type,rol);
    type[1]=0x00;
    
    
    seleccionModo(rol,character,&iface,destino,type,datos);



    //CERRAR PUERTO
    CloseAdapter(&iface);

    return 0;
}