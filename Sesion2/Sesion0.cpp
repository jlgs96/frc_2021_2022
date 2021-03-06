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
    avail_ifaces=GetAvailAdapters(); 

    unsigned char mac_dst[6]={0x00, 0x01, 0x02, 0x03,0x04, 0x05};
    char type[2]={0x30,0x00};
    
    char character = 'ª';

    //BUCLE PARA MOSTRAR LAS INTERFACES
    printf("Interfaces disponibles: \n");
    mostrarInterfacesDisponibles(avail_ifaces);

    //BUCLE RECORRE Y ELIGE LA INTERFAZ DESEADA
    seleccionInterfaz(avail_ifaces, &iface);

    //ABRIR PUERTO

    int Puerto = OpenAdapter(&iface);
    if(Puerto==1)
    {
        printf("Error en el puerto, se debe ejecutar como superusuario\n");
        return 0;
    }

    //ELEGIR GRUPO
    

    //BUCLE PRINCIPAL:
    while (character != 27)
    {
        //SI SE HA PULSADO TECLA: ENVIAMOS EL CARACTER
        if(kbhit()==1)
        {
            character = getch();
            EnviarCaracter(&iface,character,mac_dst,type); 
        }else
        //SI NO, RECIBIMOS EL CARÁCTER
        {
            character = RecibirCaracter(&iface);
           if(character != 0)
                printf("\n Recibido: %c",character);
        }
    }
    //CERRAR PUERTO
    CloseAdapter(&iface);
    
    return 0;   
}
