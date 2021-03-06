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

 
 printf("\n----------------------------\n");
 printf("------ SESION 1 - FRC ------\n");
 printf("----------------------------\n");
    
 avail_ifaces=GetAvailAdapters(); 

int index = 0;

int iseleccionada;
printf("Interfaces disponibles: \n");


//BUCLE PARA MOSTRAR LAS INTERFACES

while (avail_ifaces != NULL)
{
  
    cout<< "["<< index << "] ";
    printf(avail_ifaces->name);
    printf("\n" );
    index++;
    avail_ifaces = avail_ifaces->next;
    

}

//PEDIMOS INTERFAZ (MODULARIZAR)
printf("Seleccione interfaz : ");
cin >> iseleccionada;


//BUCLE RECORRE Y ELIGE LA INTERFAZ DESEADA
index = 0;
while (avail_ifaces != NULL)
{
   
    if (iseleccionada == index)
    {
        printf("Interfaz elegida: ");
        printf(avail_ifaces->name);
        setDeviceName(&iface, avail_ifaces->name);
        GetMACAdapter(&iface);
        printf("\nLa dirección MAC es: \n");
        PrintMACAdapter(&iface);
    }else
        avail_ifaces = avail_ifaces->next;
        index++;
    
}

/*printf("Interfaz elegida: ");
printf(iface.deviceName);
cout<<iface.deviceName<<endl;
GetMACAdapter(&iface);
printf("La MAC es: ");
cout << std::hex << (int) iface.MACaddr << endl;
 */

 return 0;
}
