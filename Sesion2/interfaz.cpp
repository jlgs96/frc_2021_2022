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
    int ielegida = pedirInterfaz();
    while (interfaces_disponibles != NULL)
    {
        if (ielegida == index)
        {
            printf("Interfaz elegida: ");
            printf(interfaces_disponibles->name);
            setDeviceName(&interfaz, interfaces_disponibles->name);
            GetMACAdapter(&interfaz);
            mostrarInterfaz(interfaz);
            break;
        }else
            interfaces_disponibles = interfaces_disponibles->next;
            index++;
        
    }
}

void mostrarInterfaz(interface_t interfaz){
    printf("\nLa dirección MAC es: \n");
    PrintMACAdapter(&interfaz);
}

void EnviarCaracter (interface_t &interfaz, unsigned char datos, unsigned char *mac_destino, char *tipo){
    //ReservarMemoriaDatos;
    unsigned char *caracter = new unsigned char;
    unsigned char *protocolo = new unsigned char;
    unsigned char *trama = new unsigned char;
    //AlmacenarDatos;
    *caracter = datos;
    *protocolo = *tipo;
    //ConstruirTrama;
    trama = BuildFrame(interfaz.MACaddr, mac_destino, protocolo, caracter); //devuelve un char, guardar
    //EnviarTrama;
    SendFrame(&interfaz, trama, sizeof(char)); // envia la trama creada antes
    //LiberarMemoriaDatos;
    delete caracter;
    delete protocolo;
    delete trama;
  }

/*
char RecibirCaracter (interface_t interfaz){
    //Trama=RecibirTrama;
    apacket_t trama = ReceiveFrame(&interfaz);
    //QuedarseCampoCompletoDatosTrama;
    unsigned char *datos = new unsigned char;
    *datos = trama.packet;
    //Acordaos, el campo datos contiene la mac destino, mac origen, tipo y los

    //datos propiamente dichos (caracteres) en este orden.

    //Si (hay algo en el campo datos)
    if(){
    //QuedarseDatosRecibidos; //Quedarse con los caracteres recibidos.

    //DevolverDato;
        return 
    //Sino
    }else {
    //DevolverValor0;
        return 0;
    }
    
}
*/