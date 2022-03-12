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

void seleccionInterfaz(pcap_if_t *interfaces_disponibles, interface_t *interfaz)
{
    int index = 0;
    int ielegida = pedirInterfaz();
    while (interfaces_disponibles != NULL)
    {
        if (ielegida == index)
        {
            printf("Interfaz elegida: ");
            printf(interfaces_disponibles->name);
            setDeviceName(interfaz, interfaces_disponibles->name);
            GetMACAdapter(interfaz);
            printf("\nLa interfaz es...\n");
            mostrarInterfaz(interfaz);

            break;
        }else
            interfaces_disponibles = interfaces_disponibles->next;
            index++;
        
    }
}

void mostrarInterfaz(interface_t *interfaz){
   // printf("\nLa dirección MAC es: \n");
    PrintMACAdapter(interfaz);
}

char elegirGrupo(){
    int codGrupo = 48;
    char grupo;
    int nGrupo = 0;
    while( 0 >= nGrupo || nGrupo > 10){
        printf("Introduzca el número de grupo: ");
        cin >> nGrupo;
    }
    grupo = codGrupo + nGrupo;
    return grupo;
}

int seleccionarRol(){
    int rol = 0;
    while (rol < 1 || rol > 2)
    {
        printf("Selecciona el modo de la estación: ");
        cin >> rol;
    }
    return rol;
}