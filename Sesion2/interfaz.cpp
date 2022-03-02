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

void seleccionInterfaz(pcap_if_t *interfaces_disponibles, interface_t &interfaz)
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
            mostrarInterfaz(interfaz);
        }else
            interfaces_disponibles = interfaces_disponibles->next;
            index++;
        
    }
}

void mostrarInterfaz(interface_t interfaz){
    printf("\nLa dirección MAC es: \n");
    PrintMACAdapter(&interfaz)
}

void EnviarCaracter (interface_t *interfaz, unsigned char datos, unsigned char *mac_origen, unsigned char *mac_destino,unsigned char tipo){
    //ReservarMemoriaDatos;
    unsigned char *caracter = new unsigned char;
    unsigned char *protocolo = new unsigned char;
    //AlmacenarDatos;
    *caracter = datos;
    *protocolo = tipo;
    //ConstruirTrama;
    BuildFrame(&mac_origen, &mac_destino, protocolo, unsigned char *payload);
    //EnviarTrama;
    SendFrame(&interfaz, caracter, int payloadSize)
    //LiberarMemoriaDatos;
    delete caracter;
    delete protocolo;
  }

//char RecibirCaracter (interface_t interfaz){
    //Trama=RecibirTrama;
    //QuedarseCampoCompletoDatosTrama;
    //Acordaos, el campo datos contiene la mac destino, mac origen, tipo y los
    //datos propiamente dichos (caracteres) en este orden.
    //Si (hay algo en el campo datos)
    //QuedarseDatosRecibidos; //Quedarse con los caracteres recibidos.
    //DevolverDato;
    //Sino
    //DevolverValor0;
}