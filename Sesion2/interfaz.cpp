#include "interfaz.h"

void mostrarInterfacesDisponibles(pcap_if_t *interfaces_disponibles)
{
    int index = 0;
    while (interfaces_disponibles != NULL)
    {
    cout<< "["<< index << "] ";
    printf(interfaces_disponibles->name);
    printf("\n" );
    index++;
    interfaces_disponibles = interfaces_disponibles->next;
    }

}
int pedirInterfaz()
{
    int interfaz;
    printf("Seleccione interfaz : ");
    cin >> interfaz;
    return interfaz;
}

void seleccionIntefaz(pcap_if_t *interfaces_disponibles, interface_t &interfaz)
{
    int index = 0;
    while (interfaces_disponibles != NULL)
    {

        if (pedirInterfaz() == index)
        {
            printf("Interfaz elegida: ");
            printf(interfaces_disponibles->name);
            setDeviceName(&interfaz, interfaces_disponibles->name);
            GetMACAdapter(&interfaz);
            printf("\nLa dirección MAC es: \n");
            PrintMACAdapter(&interfaz);
        }else
            interfaces_disponibles = interfaces_disponibles->next;
            index++;
        
    }
}

void mostrarInterfaz()